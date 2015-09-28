#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cpu.h"
#include "pqueue.h"
#include "proctab.h"

int GetRand(int min, int max);

#define STK_GARBAGE 0xAA /* Garbage value so stack sections are easy to see;
                            not using the stacks in this simulation */
#define N_SIM_ITER 5 /* Number of simulation iterations */
#define MAX_TIME 8 /* Max time-slice value */

/* Copy program into memory and allocate a stack; then create a process table
 * entry with random priority and state */
void load_program(uint32_t* program, size_t prog_size, const char* name,
  memory* mem, size_t* start_offset, proc_entry* proc_table, uint32_t pid) {
  /* Copy the program into memory */
  memcpy(mem->data + *start_offset, program, prog_size);

  /* 'Allocate'/init stack space */
  memset(mem->data + *start_offset + prog_size, STK_GARBAGE, STK_MAX);
  
  /* Initialize process entry and put it in the table (zero out regs) */  
  proc_table[pid].state = PR_READY;
  proc_table[pid].priority = PROC_TAB_SIZE, /* Highest priority by default */
  proc_table[pid].stack_ptr =  *start_offset + prog_size;
  proc_table[pid].stack_len =  STK_MAX;
  strcpy(proc_table[pid].name, name);
  memset(&(proc_table[pid].regs), 0, sizeof(registers));

  /* Update offset */
  *start_offset += prog_size + STK_MAX;
}

/* Set up the ready queue with processes in the given process table */
void init_ready_queue(priority_queue* ready_queue, proc_entry* proc_table, size_t n) {
  int i; /* Iteration index */
  
  /* Insert each process with ready status into the queue */
  for (i = 0; i < n; i++) {
    if (proc_table[i].state == PR_READY) {
      add_pq(ready_queue, proc_table + i);
    } 
  }
}

/* Assign random priorities and states to all processes except the null process */
void assign_priorities_states(proc_entry* proc_table, size_t n) {
  int i; /* Processes in process table*/
  int j; /* Number of values*/
  int r; /* Random value*/

  /* For every process in process table, determine 2 random values
	 (1 for priority and 1 for process state*/
  for (i = 1; i < n; i++) {
	  for (j = 0; j < 2; j++)
	  {
		  r = GetRand(0, 6);
		  if (j == 0)
		  {
			  /* Determine Priority based on random value*/
				 proc_table[i].priority = r;
		  }

		  /* Determine process state based on random value*/
		  if (j == 1)
		  {
			  switch (r)
			  {
			  case 0:
				  proc_table[i].state = PR_CURR;
				  break;
			  case 1:
				  proc_table[i].state = PR_CURR;
				  break;
			  case 2:
				  proc_table[i].state = PR_READY;
				  break;
			  case 3:
				  proc_table[i].state = PR_WAIT;
				  break;
			  case 4:
				  proc_table[i].state = PR_RECV;
				  break;
			  case 5:
				  proc_table[i].state = PR_SLEEP;
				  break;
			  case 6:
				  proc_table[i].state = PR_SUSP;
				  break;
			  }
		  }
	  }
  } 
}

/* The scheduler */
void resched(proc_entry* proc_table, priority_queue* ready_queue, registers* regs) {
  /* TODO */
}

uint32_t null_program[] = {
  SETC(0xDEAD, 0),
  JMP(-1),
};

uint32_t foo_program[] = {
  SETC(0xC0DE, 0),
  SET(0, 4),
  SETC(0x0100, 1),
  MUL(1, 0, 0),
  MUL(1, 0, 0),
  ADD(0, 4, 0),
  JMP(-1)
};

uint32_t bar_program[] = {
  SETC(0xBAAA, 0),
  SET(0, 4),
};

uint32_t baz_program[] = {
  SETC(0x1CEE, 0),
  SET(0, 4),
  SETC(0x0100, 1),
  MUL(1, 0, 0),
  MUL(1, 0, 0),
  ADD(0, 4, 0),
  JMP(-1)
};

uint32_t quux_program[] = {
  SETC(0xDEAD, 0),
  MUL(1, 0, 0),
  ADD(0, 4, 0),
  JMP(-1)
};

uint32_t fubar_program[] = {
  SETC(0xBEEF, 0),
  ADD(0, 5, 0),
  JMP(-1)
};

uint32_t grok_program[] = {
  SETC(0xBABE, 0),
  SET(0, 4),
  SETC(0x0100, 1),
  MUL(1, 0, 0),
  MUL(1, 0, 0),
  ADD(0, 4, 0),
  JMP(-1)
};

int main() {
  registers regs; /* Registers */
  memory mem; /* Main memory */
  proc_entry proc_table[PROC_TAB_SIZE]; /* Process table */
  priority_queue* ready_queue; /* Priority queue of processes w/state PR_READY */
  size_t offset; /* For keep track of occupied memory when loading programs */
  uint32_t current_pid; /* Process id of the current process */
  uint32_t time_slice; /* Number of instructions to run before calling resched() */
  int i; /* Iteration index */

  /* 
   * 'Initialize the state to begin from, i.e. several processes in the table
   *  already, and null process is currently running
   */

  /* Initialize memory/registers to zero */
  memset(mem.data, 0, MEMSIZE);
  memset(&regs, 0, sizeof(registers));

  /* Initialize process table to zero throughout (implicitly setting state
   * equal to PR_EMPTY in the process) FIXME */
  memset(proc_table, 0, sizeof(proc_table));

  /* 'Load' programs into memory and initialize process table */
  offset = 0;
  load_program(null_program, sizeof(null_program), "NULL", &mem, &offset, proc_table, 0);
  load_program(foo_program, sizeof(foo_program), "foo", &mem, &offset, proc_table, 1);
  load_program(bar_program, sizeof(bar_program), "bar", &mem, &offset, proc_table, 2);
  load_program(baz_program, sizeof(baz_program), "baz", &mem, &offset, proc_table, 3);
  load_program(quux_program, sizeof(quux_program), "quux", &mem, &offset, proc_table, 4);
  load_program(fubar_program, sizeof(fubar_program), "fubar", &mem, &offset, proc_table, 5);
  load_program(grok_program, sizeof(grok_program), "grok", &mem, &offset, proc_table, 6);

  /* Dump initial state */
  dump_registers(&regs);
  dump_memory(&mem);
  dump_proc_table(proc_table, sizeof(proc_table)/sizeof(proc_entry));

  /* TODO: main loop of reassignig priorities, scheduling, etc. */
  current_pid = 0;
  ready_queue = NULL;

  for (i = 0; i < N_SIM_ITER; i++) {
    /* Execute for a random number of cycles */
    time_slice = rand() % MAX_TIME + 1;

    while (time_slice > 0) {
      /* XXX: program counter is updated in execute() */
      execute(&regs, &mem);
      time_slice--;
    }

    /* Randomly assign priorities to the processes */
    assign_priorities_states(proc_table, PROC_TAB_SIZE);

    /* Set up the ready queue */
    if (ready_queue != NULL) {
      delete_pq(&ready_queue);
    } 

    ready_queue = new_pq(PROC_TAB_SIZE, cmp_proc_entry);
    init_ready_queue(ready_queue, proc_table, sizeof(proc_table)/sizeof(proc_entry));

    /* Run the scheduler */
    resched(proc_table, ready_queue, &regs);
  }

  return EXIT_SUCCESS;
}

int GetRand(int min, int max)
{
	static int Init = 0;
	int rc;

	/* Makes sure everytime this is run, provides different values*/
	if (Init == 0)
	{
		srand(time(NULL));
		Init = 1;
	}

	/* Gives a random value between the min and max values*/
	rc = (rand() % (max - min + 1) + min);

	return (rc);
}

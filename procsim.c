#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#include "proctab.h"

#define STK_GARBAGE 0xAA /* Garbage value so stack sections are easy to see;
                            not using the stacks in this simulation */

/* Copy program into memory and allocate a stack; then create a process table
 * entry with random priority and state */
void load_program(uint32_t* program, size_t prog_size, const char* name,
  memory* mem, size_t* start_offset, proc_entry* proc_table, uint32_t pid) {
  /* Copy the program into memory */
  memcpy(mem->data + *start_offset, program, prog_size);

  /* 'Allocate'/init stack space */
  memset(mem->data + *start_offset + prog_size, STK_GARBAGE, STK_MAX);
  
  /* Initialize process entry and put it in the table */  
  proc_table[pid] = (proc_entry) {
    PR_READY,
    PROC_TAB_SIZE, /* Highest priority by default */
    *start_offset + prog_size, /* Again, the stack pointer 
                                 holds the virtual address*/ 
    STK_MAX,
    "noname"
  };

  strcpy(proc_table[pid].name, name);

  /* Update offset */
  *start_offset += prog_size + STK_MAX;
}

uint32_t foo_program[] = {
  SETC(0xC0DE, 0),
  SET(0, 4),
  SETC(0x0100, 1),
  MUL(1, 0, 0),
  MUL(1, 0, 0),
  ADD(0, 4, 0)
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
  ADD(0, 4, 0)
};

uint32_t quux_program[] = {
  SETC(0xDEAD, 0),
  MUL(1, 0, 0),
  ADD(0, 4, 0)
};

uint32_t fubar_program[] = {
  SETC(0xBEEF, 0),
  ADD(0, 5, 0)
};

uint32_t grok_program[] = {
  SETC(0xBABE, 0),
  SET(0, 4),
  SETC(0x0100, 1),
  MUL(1, 0, 0),
  MUL(1, 0, 0),
  ADD(0, 4, 0)
};

int main() {
  registers regs; /* Registers */
  memory mem; /* Main memory */
  proc_entry proc_table[PROC_TAB_SIZE]; /* Process table */
  size_t offset; /* For keep track of occupied memory when loading programs */
  int i; /* Iteration index */

  /* 
   * 'Initialize the state to begin from, i.e. several processes in the table
   *  already, and null process is currently running
   */

  /* Initialize memory/registers to zero */
  memset(mem.data, 0, MEMSIZE);
  memset(&regs, 0, sizeof(registers));

  /* 'Load' programs into memory and initialize process table */
  offset = 0;
  load_program(foo_program, sizeof(foo_program), "foo", &mem, &offset, proc_table, 0);
  load_program(bar_program, sizeof(bar_program), "bar", &mem, &offset, proc_table, 0);
  load_program(baz_program, sizeof(baz_program), "baz", &mem, &offset, proc_table, 0);
  load_program(quux_program, sizeof(quux_program), "quux", &mem, &offset, proc_table, 0);
  load_program(fubar_program, sizeof(fubar_program), "fubar", &mem, &offset, proc_table, 0);
  load_program(grok_program, sizeof(grok_program), "grok", &mem, &offset, proc_table, 0);

  /* Dump initial state */
  dump_registers(&regs);
  dump_memory(&mem);

  return EXIT_SUCCESS;
}

#ifndef PROC_TAB
#define PROC_TAB

#include <stdint.h>
#include "cpu.h"

#define PROC_NAME_LEN 6

#ifndef PROC_TAB_SIZE
#define PROC_TAB_SIZE 8 /* Max number of processes; also max priority
                           (priorities range from 1 to this) */
#endif

#ifndef STK_MAX
#define STK_MAX 8
#endif

/* Process states  */
#define PR_EMPTY 0
#define PR_CURR  1 
#define PR_READY 2
#define PR_WAIT  3
#define PR_RECV  4
#define PR_SLEEP 5
#define PR_SUSP  6

/* Info for a process */
typedef struct proc_entry {
  uint8_t state; /* Process state */
  uint32_t priority; /* Priority, used by scheduler */
  uint32_t stack_ptr; /* Unsigned 32-bit int since this corresponds to an
                         address in our virtual machine */
  uint32_t stack_len; /* Max limit for stack size */
  registers regs; /* Registers associated with the context */
  char name[PROC_NAME_LEN + 1];  /* User-given name of the process */ 
  uint32_t pid; /* Process id; redundant but including it here since it makes
                   working with my priority queue easier */
} proc_entry;

/* Print out the contents of a process table, nonempty entries only */
void dump_proc_table(proc_entry* proc_table, size_t n);

/* Comparison function to use when inserting in priority queues */
int cmp_proc_entry(void* pe1, void* pe2);

#endif /* PROC_TAB */

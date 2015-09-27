#ifndef PROC_TAB
#define PROC_TAB

#include <stdint.h>

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
#define PR_SUSP  3

/* Info for a process */
typedef struct proc_entry {
  uint8_t state; /* Process state */
  uint32_t priority; /* Priority, used by scheduler */
  uint32_t stack_ptr; /* Unsigned 32-bit int since this corresponds to an
                         address in our virtual machine */
  uint32_t stack_len; /* Max limit for stack size */
  char name[PROC_NAME_LEN + 1]; 
} proc_entry;

/* Initialize a process table entry */
/* FIXME: needed?? */
void init_proc_entry(proc_entry* prentry);

/* Print out the contents of a process table, nonempty entries only */
void dump_proc_table(proc_entry* proc_table, size_t n);

#endif /* PROC_TAB */
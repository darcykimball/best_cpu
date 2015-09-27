#include <stdio.h>
#include "proctab.h"

void dump_proc_table(proc_entry* proc_table, size_t n) {
  int i; /* Iteration index */

  /* Print out contents of each nonempty process entry */
  for (i = 0; i < n; i++) {
    printf("process id = %d\n", i);
    printf("  state = %u\n", proc_table[i].state);
    printf("  priority = %u\n", proc_table[i].priority);
    printf("  stack_ptr = %08x\n", proc_table[i].stack_ptr);
    printf("  stack_len = %u\n", proc_table[i].stack_len);
    printf("  name = %s\n", proc_table[i].name);
  }
}

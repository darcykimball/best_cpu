#ifndef RESCHED_H
#define RESCHED_H

#include "cpu.h"
#include "proctab.h"
#include "pqueue.h"

/* A scheduler */
void resched(proc_entry* proc_table, priority_queue* ready_queue, registers* regs, 
  uint32_t* current_pid);

/* Context switcher */
void context_switch(proc_entry* curr_proc, proc_entry* next_proc, registers* regs);

#endif /* RESCHED_H */

#include "resched.h"

void resched(proc_entry* proc_table, priority_queue* ready_queue, registers* regs,
  uint32_t* current_pid) {
  proc_entry* next_ready; /* Next process on ready queue */
  proc_entry* curr_proc; /* 'Current' process that was just running before this */
    
  /* Sanity check: are there any processes on the ready queue? */
  if (ready_queue->n_elems == 0) {
    /* No; continue with 'current' process.
     * XXX: there's no context switch because the way we're simulating it, the
     * scheduler itself is *not* another process */
    return;
  }
 
  /* Check the highest-priority process on the ready queue and switch to it if 
     it has greater or equal priority */
  next_ready = (proc_entry*)remove_pq(ready_queue);
  curr_proc = &(proc_table[*current_pid]);

  if (next_ready->priority >= curr_proc->priority) {
    /* Update the states of the two processes */
    next_ready->state = PR_CURR;
    curr_proc->state = PR_READY;

    /* Context switch with the next ready process */
    context_switch(curr_proc, next_ready, regs);

    /* Update current pid */
    *current_pid = next_ready->pid;
  }

  /* Implicit return: if we got here, there was no eligible process to run,
   * so continue with the 'current' process */
}

void context_switch(proc_entry* curr_proc, proc_entry* next_ready, 
  registers* regs) {
  /* Save the registers for the current process */
  curr_proc->regs = *regs;

  /* Load the saved context for the next process */
  *regs = next_ready->regs;
}


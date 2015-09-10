#include <stdio.h>
#include "cpu.h"

/* Dump contents of registers */
void dump_registers(registers* regs) {
  int i; /* to iterate through general-purpose registers */

  if (regs == NULL) {
    fprintf(stderr, "dump_registers: null pointer!!");
    return;
  }

  /* Dump general-purpose registers */
  fprintf(stderr, "General purpose:\n");
  for (i = 0; i < N_REGIS; i++) {
    DUMPINT(stderr, regs->general[i]);
  }

  /* Dump various special-purpose registers */
  fprintf(stderr, "Program counter:\n");
  DUMPINT(stderr, regs->eip);
  fprintf(stderr, "Memory address:\n");
  DUMPINT(stderr, regs->madd);
  fprintf(stderr, "Memory data:\n");
  DUMPINT(stderr, regs->mdat);
  fprintf(stderr, "Flags:\n");
  DUMPINT(stderr, regs->flags);
}

/* Dump contents of memory */
void dump_memory(memory* mem) {
  int i; /* to iterate over 32-bit words */
  uint32_t* word; /* temp word to print */

  /* Print out word-by-word */
  fprintf(stderr, "Main memory:\n");

  word = (uint32_t*) mem->data;
  for (i = 0; i < MEMSIZE/32; i++) {
    fprintf(stderr, "%x\n", *word++); 
  }
}

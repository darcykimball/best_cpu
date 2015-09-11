#include <stdio.h>
#include "cpu.h"

/* Instruction table */
typedef void (*instr_ptr) (reg*, reg*);
instr_ptr instr_table[] = {
  fetch,
  store
};

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
    fprintf(stderr, "%08x\n", *word++); 
  }
}

void execute(registers* regs, memory* mem) {
  int instr; /* Instruction index (for table) */
  int nreg1; /* Index of first register in instruction */
  int nreg2; /* Index of second register in instruction */

  /* 'Decode' instruction */
  instr = GETOP(regs->eip);

  /* FIXME; removre */
  fprintf(stderr, "Executing instruction %u", instr);

  /* Get register args */
  nreg1 = GETR1(regs->eip);
  nreg2 = GETR2(regs->eip);

  /* FIXME: remove */
  fprintf(stderr, "nreg1 = %u, reg1 = %08x\n", nreg1, regs->general[nreg1]);
  fprintf(stderr, "nreg2 = %u, reg2 = %08x\n", nreg2, regs->general[nreg2]);
}

void fetch(reg* addr, reg* dest) {
}

void store(reg* src, reg* addr) {
}

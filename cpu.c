#include <stdio.h>
#include "cpu.h"

/* Instruction table */
typedef void (*instr_ptr) (memory*, reg*, reg*);
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
  fprintf(stdout, "General purpose:\n");
  for (i = 0; i < N_REGIS; i++) {
    DUMPINT(stdout, regs->general[i]);
  }

  /* Dump various special-purpose registers */
  printf("Program counter:\n");
  DUMPINT(stdout, regs->eip);
  printf("Memory address:\n");
  DUMPINT(stdout, regs->madd);
  printf("Memory data:\n");
  DUMPINT(stdout, regs->mdat);
  printf("Flags:\n");
  DUMPINT(stdout, regs->flags);
}

/* Dump contents of memory */
void dump_memory(memory* mem) {
  int i; /* to iterate over 32-bit words */
  uint32_t* word; /* temp word to print */

  /* Print out word-by-word */
  printf("Main memory:\n");

  word = (uint32_t*) mem->data;
  for (i = 0; i < MEMSIZE/32; i++) {
    printf("%08x\n", *word++); 
  }
}

void execute(registers* regs, memory* mem) {
  int instr_index; /* Instruction index (for table) */
  int nreg1; /* Index of first register in instruction */
  int nreg2; /* Index of second register in instruction */

  /* 'Decode' instruction */
  instr_index = GETOP(regs->eip);

  /* FIXME; removre */
  fprintf(stderr, "eip = %08x\n", regs->eip);
  fprintf(stderr, "Executing instruction # %u\n", instr_index);

  /* Get register args */
  nreg1 = GETR1(regs->eip);
  nreg2 = GETR2(regs->eip);

  /* FIXME: remove */
  fprintf(stderr, "nreg1 = %u, reg1 = %08x\n", nreg1, regs->general[nreg1]);
  fprintf(stderr, "nreg2 = %u, reg2 = %08x\n", nreg2, regs->general[nreg2]);

  /* 'Execute' the instruction */
  instr_table[instr_index](mem, regs->general + nreg1, regs->general + nreg2);
}

void fetch(memory* mem, reg* addr, reg* dest) {
  /* Set the value using the 'real' location in memory; the address stored in
   * 'addr' is the simulated value, i.e. relative to the beginning of the
   * simulated memory */
  *dest = *(mem->data + *addr); 
}

void store(memory* mem, reg* src, reg* addr) {
  uint32_t* dest_addr = (uint32_t*)(mem->data) + *addr;

  /* FIXME: remove!! */
  fprintf(stderr, "store: mem = %016x, addr = %08x, dest_addr = %016x\n",
    mem, addr, dest_addr);

  *dest_addr = *src;
}

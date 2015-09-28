#include <stdio.h>
#include "cpu.h"

#define DEBUG

const char* reg_names[] = { "A", "B", "C", "D", "E", "F", "G", "H" };

/* Instruction table */
typedef void (*instr_ptr) (void*, void*, void*);
instr_ptr instr_table[] = {
  fetch,
  store,
  set,
  add,
  sub,
  mul,
  divide,
  setc,
  jmp
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
    if (i < sizeof(reg_names)) {
      printf("Register %s: ", reg_names[i]);
    }    
    DUMPINT(stdout, regs->general[i]);
  }

  /* Dump various special-purpose registers */
  printf("Program counter:\n");
  DUMPINT(stdout, regs->prog_counter);
  printf("Memory address:\n");
  DUMPINT(stdout, regs->mem_addr);
  printf("Memory data:\n");
  DUMPINT(stdout, regs->mem_data);
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
  uint32_t instr; /* The raw instruction */
  int nreg1; /* Index of first register in instruction */
  int nreg2; /* Index of second register in instruction */
  int nreg3; /* Index of second register in instruction */

  /* 'Decode' instruction */
  instr = *(uint32_t*)(mem->data + regs->prog_counter);
  instr_index = GETINSTR(instr);

#ifdef DEBUG
  fprintf(stderr, "instr = %08x\n", instr);
  fprintf(stderr, "prog_counter = %08x\n", regs->prog_counter);
  fprintf(stderr, "Executing instruction # %u\n", instr_index);
#endif

  /* Get register args */
  nreg1 = GETOP1(instr);
  nreg2 = GETOP2(instr);
  nreg3 = GETOP3(instr);

#ifdef DEBUG
  fprintf(stderr, "nreg1 = %u, reg1 = %08x\n", nreg1, regs->general[nreg1]);
  fprintf(stderr, "nreg2 = %u, reg2 = %08x\n", nreg2, regs->general[nreg2]);
  fprintf(stderr, "nreg3 = %u, reg3 = %08x\n", nreg3, regs->general[nreg3]);
#endif

  /* 'Execute' the instruction */
  if (instr_index == GETINSTR(FE_OP) || instr_index == GETINSTR(ST_OP)) {
    /* This is a fetch/store instruction; need to pass in the memory */
    instr_table[instr_index](mem, regs->general + nreg1, regs->general + nreg2);
  } else if (instr_index == GETINSTR(SETC_OP)) {
    /* This is a set constant instruction; have to pass the constant value */
    instr_table[instr_index]((void*)GETCONST(instr),
      regs->general + nreg1, NULL);
  } else if (instr_index == GETINSTR(JMP_OP)) {
    /* This is a jump; have to pass constant and program counter */
    instr_table[instr_index]((void*)GETCONST(instr),
      &(regs->prog_counter), NULL);

    /* We don't want to increment program counter after a jump */
    return; 
  } else {
    instr_table[instr_index](regs->general + nreg1, regs->general + nreg2,
      regs->general + nreg3);
  }

  /* Increment program counter */
  regs->prog_counter += sizeof(uint32_t);
}

void fetch(void* mem, void* addr, void* dest) {
  /* Set the value using the 'real' location in memory; the address stored in
   * 'addr' is the simulated value, i.e. relative to the beginning of the
   * simulated memory */
  *(uint32_t*)dest =
    *((uint32_t*)(((memory*)mem)->data + *(uint32_t*)addr)); 
}

void store(void* mem, void* src, void* addr) {
  /* The offset calculation must be done in bytes here */
  uint32_t* dest_addr = (uint32_t*)(((memory*)mem)->data + *(uint32_t*)addr);

#ifdef DEBUG
  fprintf(stderr, "store: mem = %016x, addr = %08x, dest_addr = %016x\n",
    mem, addr, dest_addr);
#endif

  *dest_addr = *(uint32_t*)src;
}

void set(void* src, void* dest, void* unused) {
  *(uint32_t*)dest = *(uint32_t*)src;
}

/* FIXME: add code for setting condition bits in flags register after each
 * arithmetic operation */

void add(void* op1, void* op2, void* dest) {
  *(int32_t*)dest = *(int32_t*)op1 + *(int32_t*)op2;
}

void sub(void* op1, void* op2, void* dest) {
  *(int32_t*)dest = *(int32_t*)op1 - *(int32_t*)op2;
}

void mul(void* op1, void* op2, void* dest) {
  *(int32_t*)dest = *(int32_t*)op1 * (*(int32_t*)op2);
}

void divide(void* op1, void* op2, void* dest) {
  *(int32_t*)dest = *(int32_t*)op1 / *(int32_t*)op2;
}

void setc(void* num, void* dest, void* unused) {
#ifdef DEBUG
  fprintf(stderr, "store: constant = %08x\n", (uint32_t)num);
#endif

  *(uint32_t*)dest = (uint32_t)num;
}

/* TODO */
void sll(void* num, void* src, void* dest) {
}

/* TODO */
void srl(void* num, void* src, void* dest) {
}

/* TODO */
void andb(void* op1, void* op2, void* dest) {
}

/* TODO */
void orb(void* op1, void* op2, void* dest) {
}

/* TODO */
void xorb(void* op1, void* op2, void* dest) {
}

void jmp(void* num, void* pc, void* unused) {
  *(int32_t*)pc = *(int32_t*)pc + (int16_t)num * sizeof(uint32_t);
}

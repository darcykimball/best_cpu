#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdint.h>

#define N_REGIS 8 /* Number of general-purpose registers */
#define MEMSIZE 512 /* Size of main memory in bytes 
                       XXX: mult. of 4 or bad shit will happen */

#define DUMPINT(f,n) fprintf((f), "%x\n", n)

/* Registers */
typedef uint32_t reg;

typedef struct registers {
  reg general[N_REGIS]; /* General-purpose registers */
  reg eip; /* Program counter */
  reg madd; /* Memory address */
  reg mdat; /* Memory data */
  reg flags; /* Flags (for various states) */
} registers;

/* Main memory */
typedef struct memory {
  unsigned char data[MEMSIZE];
} memory;

/* Dump contents of registers */
void dump_registers(registers* regs);

/* Dump contents of memory */
void dump_memory(memory* mem);

/* Fetch a word from memory */
void fetch(uint32_t addr, reg* dest); 

/* Store a word from a register to memory */
void store(uint32_t addr, reg* src);

#endif /* CPU_H */

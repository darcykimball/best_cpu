#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdint.h>

#define N_REGIS 8 /* Number of general-purpose registers */
#define MEMSIZE 512 /* Size of main memory in bytes 
                       XXX: mult. of 4 or bad shit will happen */

#define DUMPINT(f,n) fprintf((f), "%08x\n", n)

/* Instruction opcodes/layout 
 * 
 * (in hex:)
 * opcode reg1 reg2
 * 0A     001  00F
 *
 */
#define FE_OP 0x01000000
#define ST_OP 0x02000000

#define FE(r1,r2) (FE_OP | ((r1) << 3*4) | (r2))
#define ST(r1,r2) (ST_OP | ((r1) << 3*4) | (r2))

#define GETOP(instr) ((instr) >> 3*8)
#define GETR1(instr) (((instr) & 0x00FFF000) >> 3*4)
#define GETR2(instr) ((instr) & 0x00000FFF)

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

/* Execute an instruction (using current program counter) */
void execute(registers* regs, memory* mem);

/* Fetch a word from memory */
void fetch(reg* addr, reg* dest); 

/* Store a word from a register to memory */
void store(reg* src, reg* addr);

#endif /* CPU_H */

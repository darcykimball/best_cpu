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
#define FE_OP 0x00000000
#define ST_OP 0x01000000

#define FE(r1,r2) (FE_OP | ((r1) << 2*8) | (r2 << 8))
#define ST(r1,r2) (ST_OP | ((r1) << 2*8) | (r2 << 8))
#define SET(r1,r2,r3) (SET_OP | ((r1) << 2*8) | (r2 << 8) | (r3))
#define ADD(r1,r2,r3) (ADD_OP | ((r1) << 2*8) | (r2 << 8) | (r3))
#define SUB(r1,r2,r3) (SUB_OP | ((r1) << 2*8) | (r2 << 8) | (r3))
#define MUL(r1,r2,r3) (MUL_OP | ((r1) << 2*8) | (r2 << 8) | (r3))
#define DIV(r1,r2,r3) (DIV_OP | ((r1) << 2*8) | (r2 << 8) | (r3))

/* Macro for getting instruction opcode */
#define GETINSTR(instr) ((instr) >> 3*8)

/* Macros for extracting operands from an instruction */
#define GETOP1(instr) (((instr) & 0x00FF0000) >> 2*8)
#define GETOP2(instr) (((instr) & 0x0000FF00) >> 8)
#define GETOP3(instr) ((instr) & 0x000000FF)

/* Registers */
typedef uint32_t reg;

typedef struct registers {
  reg general[N_REGIS]; /* General-purpose registers */
  reg prog_counter; /* Program counter */
  reg mem_addr; /* Memory address */
  reg mem_data; /* Memory data */
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
void fetch(void* mem, void* addr, void* dest); 

/* Store a word from a register to memory */
void store(void* mem, void* src, void* addr);

#endif /* CPU_H */

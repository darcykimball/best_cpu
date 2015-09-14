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
#define FE_OP   0x00000000
#define ST_OP   0x01000000
#define SET_OP  0x02000000
#define ADD_OP  0x03000000
#define SUB_OP  0x04000000
#define MUL_OP  0x05000000
#define DIV_OP  0x06000000
#define SETC_OP 0x07000000 /* Set an immediate constant */

#define FE(r1,r2) (FE_OP | ((r1) << 2*8) | (r2 << 8))
#define ST(r1,r2) (ST_OP | ((r1) << 2*8) | (r2 << 8))
#define SET(r1,r2) (SET_OP | ((r1) << 2*8) | (r2 << 8))
#define ADD(r1,r2,r3) (ADD_OP | ((r1) << 2*8) | (r2 << 8) | (r3))
#define SUB(r1,r2,r3) (SUB_OP | ((r1) << 2*8) | (r2 << 8) | (r3))
#define MUL(r1,r2,r3) (MUL_OP | ((r1) << 2*8) | (r2 << 8) | (r3))
#define DIV(r1,r2,r3) (DIV_OP | ((r1) << 2*8) | (r2 << 8) | (r3))
#define SETC(c,r) (SETC_OP | ((r) << 2*8) | (0x0000FFFF & (c)))

/* Macro for getting instruction opcode */
#define GETINSTR(instr) ((instr) >> 3*8)

/* Macros for extracting operands from an instruction */
#define GETOP1(instr) (((instr) & 0x00FF0000) >> 2*8)
#define GETOP2(instr) (((instr) & 0x0000FF00) >> 8)
#define GETOP3(instr) ((instr) & 0x000000FF)
#define GETCONST(instr) ((instr) & 0x0000FFFF) /* Only for SETC */

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

/* Set the contents of the 2nd operand register to that of the 1st*/
void set(void* src, void* dest, void* unused);

/*
 * XXX: Arithmetic operations are signed
 */

/* Add the contents of two registers and store in a third */
void add(void* op1, void* op2, void* dest);

/* Subtract the second operand from the first and store in a third */
void sub(void* op1, void* op2, void* dest);

/* Multiply the contents of two registers and store in a third */
void mul(void* op1, void* op2, void* dest);

/* Divide the first operand by the 2nd and store in a third */
void divide(void* op1, void* op2, void* dest);

/* Set an immediate constant; TODO: allowable range? */
void setc(void* num, void* dest, void* unused);

#endif /* CPU_H */

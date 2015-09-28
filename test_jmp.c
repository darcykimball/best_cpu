#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"

#define OS_SIZE 8 /* Just some arbitrary number for now */

uint32_t test_program[] = {
  SETC(0x0001, 0), 
  SETC(0x0002, 1),
  MUL(0, 1, 0),
  JMP(-1)
};

int main() {
  registers regs; /* Registers */
  memory mem; /* Main memory */
  int i; /* Instruction count */

  /* 
   * 'Boot up'??
   */

  /* Initialize memory/registers to zero */
  memset(mem.data, 0, MEMSIZE);
  memset(&regs, 0, sizeof(registers));

  /* 'Load' sample program into memory */
  memcpy(mem.data + OS_SIZE, test_program, sizeof(test_program));

  /* Initialize some register and memory values 
   * (hard-coded for the purposes of testing)
   */
  printf("Initial state:\n");
  dump_registers(&regs);
  dump_memory(&mem);

  /* Execute program */

  /* Initialize program counter */
  regs.prog_counter = OS_SIZE;

  for (i = 0; i < 2*sizeof(test_program)/sizeof(uint32_t) + 2; i++) {
    printf("Executing instruction %u in test_program\n", i);

    /* Execute instruction */
    execute(&regs, &mem);

    /* Dump */
    dump_registers(&regs);
    dump_memory(&mem);
  }

  return EXIT_SUCCESS;
}

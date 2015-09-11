#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"

#define OS_SIZE 8 /* Just some arbitrary number for now */

uint32_t test_program[] = {
  ST(0, 1), /* Store value from reg0 into address in reg1*/ 
  FE(1, 2), /* Fetch value from address in reg1 into reg2 */
  FE(1, 7), /* Fetch value from address in reg1 into reg7 */
  ST(3, 1)  /* Store value from reg3 into address in reg1 */
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
  const uint32_t sample_value_addr = OS_SIZE + sizeof(test_program);

  regs.general[0] = 0xDEADBEEF;
  regs.general[1] = sample_value_addr; 
  regs.general[3] = 0xCAFEBABE;

  printf("Initial state:\n");
  dump_registers(&regs);
  dump_memory(&mem);

  /* Execute program */
  for (i = 0; i < sizeof(test_program)/sizeof(uint32_t); i++) {
    printf("Executing instruction %u in test_program\n", i);

    /* Set program counter */
    regs.eip = test_program[i];

    /* Execute instruction */
    execute(&regs, &mem);

    /* Dump */
    dump_registers(&regs);
    dump_memory(&mem);
  }

  return EXIT_SUCCESS;
}

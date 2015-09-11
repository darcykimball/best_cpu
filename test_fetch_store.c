#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"

#define OS_SIZE 8 /* Just some arbitrary number for now */

uint32_t test_program[] = {
  ST(0, 1), /* Store value from reg0 into address held in reg1*/ 
  FE(1, 2) /* Store value from reg1 into reg2 */
};

int main() {
  registers regs; /* Registers */
  memory mem; /* Main memory */
  int i; /* Instruction count */
  uint32_t pstrt; /* User program starting address */

  /* 
   * 'Boot up'??
   */

  /* Initialize memory/registers to zero */
  memset(mem.data, 0, MEMSIZE);
  memset(&regs, 0, sizeof(registers));
  memcpy(mem.data + 1, &pstrt, sizeof(pstrt));

  /* 'Load' sample program into memory */
  memcpy(mem.data + OS_SIZE, test_program, sizeof(test_program));

  /* Initialize some register and memory values 
   * (hard-coded for the purposes of testing)
   */
  const uint32_t sample_value_addr = OS_SIZE + sizeof(test_program);

  regs.general[0] = 0xDEADBEEF;
  regs.general[1] = sample_value_addr; 

  /* Execute program */
  for (i = 0; i < sizeof(test_program)/sizeof(uint32_t); i++) {
    /* Set program counter */
    regs.eip = test_program[i];

    /* Execute instruction */
    execute(&regs, &mem);

    /* Dump */
    dump_registers(&regs);
    dump_memory(&mem);
  }

  /* FIXME: remove!! try dumping for now */
  dump_registers(&regs);
  dump_memory(&mem);

  return EXIT_SUCCESS;
}

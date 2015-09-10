#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"

int main() {
  registers regs; /* Registers */
  memory mem; /* Main memory */

  /* 
   * 'Boot up'??
   */

  /* Initialize memory/registers to zero */
  memset(mem.data, 0, MEMSIZE);
  memset(&regs, 0, sizeof(registers));

  /* TODO: Execute stuff */

  /* FIXME: remove!! try dumping for now */
  dump_registers(&regs);
  dump_memory(&mem);

  return EXIT_SUCCESS;
}

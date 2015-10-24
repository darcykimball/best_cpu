#include <string.h>
#include <stdlib.h>
#include "randmem.h"

void memset_rand(void* dest, size_t n) {
  unsigned char* curr_byte; /* Ptr to current byte to be written */

  /* Write 'random' bytes, one-by-one */
  curr_byte = dest;
  while (n > 0) {
    *curr_byte++ = rand();
    n--;
  }
}

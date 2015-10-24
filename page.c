#ifndef PAGE_H
#define PAGE_H

#include <stdlib.h>

bool is_resident(uint32_t addr) {
  /* XXX: addr is a dummy parameter, but this is a simulation after all */
  /* Return true half the time */
  return rand() % 2 == 0;
}

/* FIXME: double check the range */
uint32_t get_page_number(uint32_t addr) {
  return (rand() % N_PAGES) + 1;
}

/* FIXME: triple check the computation */
uint32_t get_page_offset(uint32_t page_number) {
  /* Ensure word-alignment; our fetch/store only do so on word boundaries;
   * get the offset in 4-byte words, then multiply by word size to get the
   * offset in bytes */
  return (rand() % (PAGE_SIZE/4) + 1) * 4;
}

#endif /* PAGE_H */

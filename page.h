#ifndef PAGE_H
#define PAGE_H

/* Simulate checking if a (virtual) address's contents is resident in memory. 
 * This yield true/false 50/50 of the time. */
bool is_resident(uint32_t addr);

/* Simulate translating a virtual address; returns the page number */
uint32_t get_page_number(uint32_t addr);

/* Simulate inspection of the page table. Returns a random offset into the
 * given page */
uint32_t get_page_offset(uint32_t page_number);

#endif /* PAGE_H */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pqueue.h"
#include "test.h"

int cmp_int(void* x, void* y) {
  return *(int*)x - *(int*)y;
}

void dump_int_heap(priority_queue* pq) {
  size_t i;

  fprintf(stderr, "heap:\n");
  for (i = 0; i < pq->n_elems; i++) {
    fprintf(stderr, "%d\n", *((int*)pq->heap[i]));
  }
}

int main() {
  int nums[] = { 4, 1, 6, 32, 6, 20, 9, 3, -19, 12 };
  size_t i; /* For loops */
  int* max_elem; /* Temporary; to hold retrieved maximum elements */
  int* prev; /* Temporary; to hold last retrieved element */

  priority_queue* pq = new_pq(10, cmp_int);

  TEST(pq != NULL);
  
  /* Add in some numbers */
  for (i = 0; i < sizeof(nums)/sizeof(int); i++) {
    add_pq(pq, &nums[i]);
  }

  /* Dump fields */
  printf("n_elems = %u\n", pq->n_elems);  
  printf("capacity = %u\n", pq->capacity);  

  TEST(pq->n_elems == sizeof(nums)/sizeof(int));
  TEST(pq->capacity == 10);

  /* Dump the heap */
  dump_int_heap(pq);

  /* Try removing elements and check for correct ordering */
  prev = NULL;
  for (i = 0; i < sizeof(nums)/sizeof(int); i++) {
    max_elem = (int*)remove_pq(pq);    

    fprintf(stderr, "max_elem = %d\n", *max_elem);
    dump_int_heap(pq);

    if (prev != NULL) {
      fprintf(stderr, "prev, max_elem (current) = %d, %d\n", *prev, *max_elem);
      TEST(*prev >= *max_elem);
    }

    prev = max_elem;
  }

  delete_pq(&pq);

  TEST(pq == NULL);

  return 0;
}

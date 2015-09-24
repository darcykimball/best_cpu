#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"

int cmp_int(void* x, void* y) {
  return *(int*)x - *(int*)y;
}

int main() {
  int nums[] = { 4, 1, 6, 32, 6, 20, 9, 3, -19, 12 };
  size_t i; /* For loops */

  priority_queue* pq = new_pq(10, cmp_int);
  
  /* Add in some numbers */
  for (i = 0; i < sizeof(nums)/sizeof(int); i++) {
    add_pq(pq, &nums[i]);
  }

  /* Dump fields */
  printf("n_elems = %u\n", pq->n_elems);  
  printf("capacity = %u\n", pq->capacity);  

  /* Dump the heap */
  printf("heap =\n");
  for (i = 0; i < pq->n_elems; i++) {
    printf("%d\n", *(int*)pq->heap[i]);            
  }

  delete_pq(&pq);

  return 0;
}

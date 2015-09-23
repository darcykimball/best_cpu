#ifndef PQUEUE_H
#define PQUEUE_H

#include <stdio.h>

#define PQ_SIZE 128

/* A min-heap priority queue */
typedef int (*cmp_fn_ptr) (void*, void*); /* Comparison function used to 
                                             determine ordering */
typedef struct priority_queue {
  void* heap[PQ_SIZE]; /* Array of elements */
  cmp_fn_ptr cmp_fn; /* Comparison function */
  uint32_t n_elems; /* Number of elements currently inside */
} priority_queue;

/* Add an element to the queue; returns whether the add was successful or not */
bool add_pq(priority_queue* pq, void* elem);

/* Remove and return the minimum element in the queue; returns NULL for
 * exceptional cases or if the queue is empty */
void* remove_pq(priority_queue* pq);

/* Return the minimum element in the queue; returns NULL for exceptiona l cases
 * or if the queue is empty */
void* min_pq(priority_queue* pq);

#endif /* PQUEUE_H */

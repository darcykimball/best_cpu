#ifndef PQUEUE_H
#define PQUEUE_H

#include <stdio.h>
#include <stdbool.h>

/* A max-heap priority queue */
typedef int (*cmp_fn_ptr) (void*, void*); /* Comparison function used to 
                                             determine ordering */
typedef struct priority_queue {
  void** heap; /* Array of elements */
  cmp_fn_ptr cmp_fn; /* Comparison function */
  size_t n_elems; /* Number of elements currently inside */
  size_t capacity; /* Number of elements this can hold */
} priority_queue;

/* Constructor */
priority_queue* new_pq(size_t n, cmp_fn_ptr f);

/* Add an element to the queue; returns whether the add was successful or not */
bool add_pq(priority_queue* pq, void* elem);

/* Remove and return the minimum element in the queue; returns NULL for
 * exceptional cases or if the queue is empty */
void* remove_pq(priority_queue* pq);

/* Return the maximum element in the queue; returns NULL for exceptiona l cases
 * or if the queue is empty */
void* top_pq(priority_queue* pq);

/* Destructor */
void delete_pq(priority_queue** pq_ptr);
        
#endif /* PQUEUE_H */

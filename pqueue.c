#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"

#define PARENT(i) (((i) - 1)/2) /* Get the index of the parent of a node */

/* Helper functions for maintaining heap order */
static void reheap_up(priority_queue* pq, size_t index);
static void reheap_down(priority_queue* pq, size_t index);
static void swap(void** x, void** y);

priority_queue* new_pq(size_t n, cmp_fn_ptr f) {
  /* Allocate for the queue and data */
  priority_queue* pq = (priority_queue*)malloc(sizeof(priority_queue));
  if (pq == NULL) {
    fprintf(stderr, "new_pq: malloc failed\n");
    return NULL;
  }

  pq->heap = (void**)malloc(n);
  if (pq == NULL) {
    fprintf(stderr, "new_pq: malloc failed\n");
    return NULL;
  }

  /* Initialize */
  pq->cmp_fn = f;
  pq->n_elems = 0;
  pq->capacity = n;

  return pq;
}

bool add_pq(priority_queue* pq, void* elem) {
  /* Sanity checks */
  if (pq == NULL) {
    fprintf(stderr, "add_pq: null priority_queue pointer!!\n");
    return false;
  }

  if (elem == NULL) {
    fprintf(stderr, "add_pq: null elem pointer!!\n");
    return false;
  }

  if (pq->n_elems == pq->capacity) {
    fprintf(stderr, "add_pq: no space in queue!!\n");
    return false;
  }

  /* Add the element */
  pq->heap[pq->n_elems] = elem;
  pq->n_elems++; 

  /* Re-establish order */
  reheap_up(pq, pq->n_elems - 1);
}

void* remove_pq(priority_queue* pq) {
  void* min_elem; /* The minimum element; return value */

  /* Sanity checks */
  if (pq == NULL) {
    fprintf(stderr, "remove_pq: null pq!!\n");
    return NULL;
  }

  if (pq->n_elems == 0) {
    fprintf(stderr, "remove_pq: empty pq!!\n");
    return NULL;
  }

  /* Retreive the minimum */
  min_elem = pq->heap[0];

  /* Re-establish order */
  reheap_down(pq, 0);
}

/* TODO */
void* min_pq(priority_queue* pq) {

}

void delete_pq(priority_queue** pq_ptr) {
  priority_queue* pq; /* The actual priority queue */

  /* Sanity checks */
  if (pq_ptr == NULL) {
    fprintf(stderr, "delete_pq: null pq_ptr!!\n");
  }

  pq = *pq_ptr;
  if (pq == NULL) {
    fprintf(stderr, "delete_pq: null pq!!\n");
  }

  /* Free data */
  free(pq->heap);
  free(pq);

  /* Invalidate the pq pointer */
  *pq_ptr = NULL;
}

/* Helper functions for maintaining heap order */
static void reheap_up(priority_queue* pq, size_t index) {
  /* Sanity check */
  if (pq == NULL) {
    fprintf(stderr, "reheap_up: null pq!!\n");
    return;
  }

  /* Move the element up as long as it's 'greater-than' its parent */
  while (index > 0 && pq->cmp_fn(pq->heap[index], pq->heap[PARENT(index)]) > 0) {
    /* Swap the current element with its parent */
    swap(pq->heap[index], pq->heap[PARENT(index)]);

    /* Update current elem's index */
    index = PARENT(index);
  }
}

/* TODO */
static void reheap_down(priority_queue* pq, size_t index) {
  /* Sanity check */
  if (pq == NULL) {
    fprintf(stderr, "reheap_down: null pq!!\n");
    return;
  }
}

static void swap(void** x, void** y) {
  void* tmp = *x;
  *x = *y;
  *y = tmp;
}

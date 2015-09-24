#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"

#define PARENT(i) (((i) - 1)/2) /* Get the index of the parent of a node */
#define LCHILD(i) (2*(i) + 1) /* Get the index of the left child */
#define RCHILD(i) (2*(i) + 2) /* Get the index of the left child */

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
  pq->heap[pq->n_elems++] = elem;

  /* Re-establish order */
  reheap_up(pq, pq->n_elems - 1);
}

void* remove_pq(priority_queue* pq) {
  void* max_elem; /* The maximum element; return value */

  /* Sanity checks */
  if (pq == NULL) {
    fprintf(stderr, "remove_pq: null pq!!\n");
    return NULL;
  }

  if (pq->n_elems == 0) {
    fprintf(stderr, "remove_pq: empty pq!!\n");
    return NULL;
  }

  /* Retreive the maximum */
  max_elem = pq->heap[0];
  pq->n_elems--;

  /* Re-establish order */
  pq->heap[0] = pq->heap[pq->n_elems - 1];
  reheap_down(pq, 0);

  return max_elem;
}

/* TODO */
void* top_pq(priority_queue* pq) {
  /* Sanity checks */
  if (pq == NULL) {
    fprintf(stderr, "min_pq: null pq!!\n");
    return NULL;
  }

  if (pq->n_elems == 0) {
    fprintf(stderr, "min_pq: empty pq!!\n");
    return NULL;
  }

  /* Retreive the minimum */
  return pq->heap[0];
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
  while (index > 0) {
    if (pq->cmp_fn(pq->heap[index], pq->heap[PARENT(index)]) > 0) {
      /* Swap the current element with its parent */
      swap(pq->heap + index, pq->heap + PARENT(index));

      /* Update current elem's index */
      index = PARENT(index);
    } else {
      /* The element is 'less' than its parent; done */
      return;
    }
  }
}

/* TODO */
static void reheap_down(priority_queue* pq, size_t index) {
  void* current; /* Temporary; current node */
  void* left_child; /* Temporary */
  void* right_child; /* Temporary */

  /* Sanity check */
  if (pq == NULL) {
    fprintf(stderr, "reheap_down: null pq!!\n");
    return;
  }

  /* Examine the current element's children and restructure accordingly */
  while (index < pq->n_elems) {
    current = pq->heap[index];
    left_child = pq->heap[LCHILD(index)]; 
    right_child = pq->heap[RCHILD(index)]; 

    /* Compare with left child */
    if (pq->cmp_fn(current, left_child) < 0) {
      /* This is 'smaller' than the left; check the right */ 
      if (pq->cmp_fn(current, right_child) < 0) {
        /* This is smaller than both; check and choose the larger of the two
         * children to replace itself */
        if (pq->cmp_fn(left_child, right_child) < 0) {
          /* Left is the smaller; replace using right */
          swap(pq->heap + RCHILD(index), pq->heap + index);
          index = RCHILD(index);
        } else {
          /* Right is the smaller; replace using left */
          swap(pq->heap + LCHILD(index), pq->heap + index);
          index = LCHILD(index);
        }
      }
    } else {
      /* This is bigger the left; check the right */
      if (pq->cmp_fn(current, right_child) < 0) {
        /* This one's smaller than the right; swap with it */ 
        swap(pq->heap + RCHILD(index), pq->heap + index);
        index = RCHILD(index);
      } else {
        /* This one's 'greater' than or equal to the right; we're done */
        return;
      }
    }
  }
}

static void swap(void** x, void** y) {
  void* tmp = *x;
  *x = *y;
  *y = tmp;
}

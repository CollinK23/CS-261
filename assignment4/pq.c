/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdio.h>
#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"


/*
 * This is the structure that represents the priority queue nodes.
 * They contain the value and priority for each node
 */
struct pq_node {
	int priority;
	void* value;
};

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{
	struct dynarray* dynarray;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	/*
	 * FIXME: 
	 */
	struct pq* newPq = malloc(sizeof(struct pq)); //Allocate memory for new pq struct
	newPq->dynarray = dynarray_create(); //Allocate memory for new dynamic array
	return newPq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
	/*
	 * FIXME: 
	 */
	dynarray_free(pq->dynarray); //Frees memory from dynamic array
	free(pq); //Frees memory from priority queue
	return;
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
	/*
	 * FIXME: 
	 */
	if (dynarray_size(pq->dynarray) == 0){
		return 1;
	}
	return 0;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
	/*
	 * FIXME: 
	 */
	struct pq_node* node = malloc(sizeof(struct pq_node)); //Allocates memory for new pq node
	node->value = value; //Sets value of node
	node->priority = priority; //Sets priority of node

	dynarray_insert(pq->dynarray, node); //Inserts the node into the dynamic array
	int idx = dynarray_size(pq->dynarray) - 1; //Index of inserted node
	int parentIdx = ((idx) / 2); //Index of parent node
	struct pq_node* parent = dynarray_get(pq->dynarray, parentIdx); //parent node

	//Swaps the inserted node with its parent until the parent priority is smaller
	while (parent->priority > priority){
		dynarray_swap(pq->dynarray, idx, parentIdx); //Swaps parent and inserted node
		idx = parentIdx; //Updates inserted node index
		parentIdx = ((idx) / 2); //Updates parent index
		parent = dynarray_get(pq->dynarray, parentIdx); //Updates parent node
	}

	return;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
	/*
	 * FIXME: 
	 */
	struct pq_node* node = dynarray_get(pq->dynarray, 0);
	return node->value;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
	/*
	 * FIXME: 
	 */
	struct pq_node* node = dynarray_get(pq->dynarray, 0); //lowest priority is first index because its min-heap
	return node->priority;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
	/*
	 * FIXME: 
	 */
	struct pq_node* temp = dynarray_get(pq->dynarray, 0); //Stores value being removed

	dynarray_swap(pq->dynarray, 0, dynarray_size(pq->dynarray) - 1); //Swaps node being removed with last node in pq
	dynarray_remove_tail(pq->dynarray); //Removes last node
	int size = dynarray_size(pq->dynarray); //Resizes the dynamic array

	int curr = 0;
	int min = curr; //min is node that the current node will be swapped with
	//Sorts the new root into correct position
	while(curr < size){
		int left = 2 * curr + 1; // left child of parent node index
		int right = 2 * curr + 2; //Right child of parent node index
		if (left < size && 
		((struct pq_node*)dynarray_get(pq->dynarray, left))->priority < 
		((struct pq_node*)dynarray_get(pq->dynarray, min))->priority){
			min = left; //Sets min equal to left child if it has higher priority than current node
		}
		if (right < size && 
		((struct pq_node*)dynarray_get(pq->dynarray, right))->priority < 
		((struct pq_node*)dynarray_get(pq->dynarray, min))->priority){
			min = right; //Sets min equal to right child if it has higher priority than left child or current node
		}
		if (min != curr){
			dynarray_swap(pq->dynarray, min, curr); //Swaps current node with child node
			curr = min; //Updates current node
		}else{
			break; //If no swaps need to be done, the node is in correct position
		}
	}

	void* value = temp->value;
	free(temp); //Frees memory allocated to the pq node
	return value;
}

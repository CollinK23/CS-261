/*
 * This file is where you should implement your queue-from-stacks.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name:
 * Email:
 */

#include <stdlib.h>

#include "stack.h"
#include "queue_from_stacks.h"

/*
 * This is the structure that will be used to represent a queue using two
 * stacks.  It specifically contains two fields, each representing a stack.
 * These two stacks should be used together as the underlying data storage for
 * the queue.
 *
 * You should not modify this structure.
 */
struct queue_from_stacks {
  struct stack* s1;
  struct stack* s2;
};

/*
 * This function should allocate and initialize a new, empty queue-from-stacks
 * and return a pointer to it.
 */
struct queue_from_stacks* queue_from_stacks_create() {
  	/*
	 * FIXME:
	 */
	struct queue_from_stacks* newQueue = malloc(sizeof(struct queue_from_stacks)); //Allocates memory for struct
	newQueue->s1 = stack_create(); //Allocates memory for stack 1
	newQueue->s2 = stack_create(); //Allocates memory for stack 2
  	return newQueue;
}

/*
 * This function should free the memory associated with a queue-from-stacks.
 * While this function should up all memory used in the queue-from-stacks
 * itself, it should not free any memory allocated to the pointer values stored
 * in the queue.  This is the responsibility of the caller.
 *
 * Params:
 *   qfs - the queue-from-stacks to be destroyed.  May not be NULL.
 */
void queue_from_stacks_free(struct queue_from_stacks* qfs) {
  	/*
	 * FIXME:
	 */
	stack_free(qfs->s1); //Frees memory from stack 1
	stack_free(qfs->s2); //Frees memory from stack 2
	free(qfs); //Frees memory from queue
  	return;
}

/*
 * This function should indicate whether a given queue-from-stacks is currently
 * empty.  Specifically, it should return 1 if the specified queue-from-stacks
 * is empty (i.e. contains no elements) and 0 otherwise.
 *
 * Params:
 *   qfs - the queue-from-stacks whose emptiness is being questioned.  May not
 *     be NULL.
 */
int queue_from_stacks_isempty(struct queue_from_stacks* qfs) {
  	/*
	 * FIXME:
	 */
  	return stack_isempty(qfs->s1);
}

/*
 * This function should enqueue a new value into a given queue-from-stacks.
 * The value to be enqueued is specified as a void pointer.
 *
 * Params:
 *   qfs - the queue-from-stacks into which a value is to be enqueued.  May not
 *     be NULL.
 *   val - the value to be enqueued.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void queue_from_stacks_enqueue(struct queue_from_stacks* qfs, void* val) {
  	/*
	 * FIXME:
	 */
	stack_push(qfs->s1, val); //Pushed new values into the first stack
  	return;
}

/*
 * This function should return the value stored at the front of a given
 * queue-from-stacks *without* removing that value.
 *
 * Params:
 *   qfs - the queue-from-stacks from which to query the front value.  May not be NULL.
 */
void* queue_from_stacks_front(struct queue_from_stacks* qfs) {
  	/*
	 * FIXME:
	 */

	//Pushes values from stack one into stack 2 until the first stack is empty
	while (stack_isempty(qfs->s1) == 0){
		stack_push(qfs->s2, stack_pop(qfs->s1)); //The values will be added in reverse order to stack 2
	}

	void** val = stack_top(qfs->s2); //Will show the first value in the stack

	//Moves all of the values back into the first stack
	while (stack_isempty(qfs->s2) == 0){
		stack_push(qfs->s1, stack_pop(qfs->s2));
	}

  	return val;
}

/*
 * This function should dequeue a value from a given queue-from-stacks and
 * return the dequeued value.
 *
 * Params:
 *   qfs - the queue-from-stacks from which a value is to be dequeued.  May not
 *     be NULL.
 *
 * Return:
 *   This function should return the value that was dequeued.
 */
void* queue_from_stacks_dequeue(struct queue_from_stacks* qfs) {
  	/*
	 * FIXME:
	 */
	//Pushes values from stack one into stack 2 until the first stack is empty
	while (stack_isempty(qfs->s1) == 0){
		stack_push(qfs->s2, stack_pop(qfs->s1));
	}

	void** val = stack_pop(qfs->s2); //Removes the first node from the second stack

	//Moves all of the remaining values back into the first stack until stack 2 is empty
	while (stack_isempty(qfs->s2) == 0){
		stack_push(qfs->s1, stack_pop(qfs->s2));
	}

  	return val;
}

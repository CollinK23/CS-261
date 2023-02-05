/*
 * This file contains the definition of the interface for the queue-from-stacks
 * you'll implement.  You can find descriptions of the queue-from-stacks
 * functions, including their parameters and their return values, in
 * queue_from_stacks.c.  You should not modify anything in this file.
 */

#ifndef __QUEUE_FROM_STACKS_H
#define __QUEUE_FROM_STACKS_H

/*
 * Structure used to represent a queue.
 */
struct queue_from_stacks;

/*
 * Queue-from-stacks interface function prototypes.  Refer to
 * queue_from_stacks.c for documentation about each of these functions.
 */
struct queue_from_stacks* queue_from_stacks_create();
void queue_from_stacks_free(struct queue_from_stacks* qfs);
int queue_from_stacks_isempty(struct queue_from_stacks* qfs);
void queue_from_stacks_enqueue(struct queue_from_stacks* qfs, void* val);
void* queue_from_stacks_front(struct queue_from_stacks* qfs);
void* queue_from_stacks_dequeue(struct queue_from_stacks* qfs);

#endif

/*
 * This file contains the definition of the interface for a linked list.  You
 * can find descriptions of the linked list functions, including their
 * parameters and their return values, in list.c.
 */

#ifndef __LIST_H
#define __LIST_H

/*
 * Structure used to represent a singly-linked list.  You may not change the
 * fact that only a forward declaration of the list structure is included
 * here.  In other words, you can't define the fields of the struct here.
 */
struct list;

/*
 * Linked list interface function prototypes.  Refer to list.c for
 * documentation about each of these functions.
 */
struct list* list_create();
void list_free(struct list* list);
void list_insert(struct list* list, void* val);
void list_remove(struct list* list, void* val, int (*cmp)(void* a, void* b));
int list_position(struct list* list, void* val, int (*cmp)(void* a, void* b));
void list_reverse(struct list* list);
void* list_return(struct list* list);
void list_remove_one(struct list* list);
void* list_empty(struct list* list);
#endif

/*
 * This file contains the definition of the interface for the linked list
 * you'll implement.  You can find descriptions of the linked list functions,
 * including their parameters and their return values, in list.c. You should
 * not modify anything in this file.
 */

#ifndef __LIST_H
#define __LIST_H

/*
 * Structure used to represent a singly-linked list.
 */
struct node;
struct list;

/*
 * Linked list interface function prototypes.  Refer to list.c for
 * documentation about each of these functions.
 */
struct list* list_create();
void list_free(struct list* list);
void list_insert(struct list* list, void* val);
void list_insert_end(struct list* list, void* val);
void list_remove(struct list* list, void* val, int (*cmp)(void* a, void* b));
void list_remove_end(struct list* list);
int list_position(struct list* list, void* val, int (*cmp)(void* a, void* b));
void list_reverse(struct list* list);

#endif

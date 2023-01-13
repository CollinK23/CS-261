/** EXTRA CREDITS **/

/*
 * This file contains the definition of the interface for the doubly-linked list.
 * You can find descriptions of the doubly-linked list functions,
 * including their parameters and their return values, in db_list.c. You should
 * not modify anything in this file.
 */

#ifndef __DB_LIST_H
#define __DB_LIST_H

/*
 * Structure used to represent a doubly-linked list.
 */
struct db_node;
struct db_list;

/*
 * Doubly-linked list interface function prototypes. Refer to db_list.c for
 * documentation about each of these functions.
 */
struct db_list* db_list_create();
void db_list_free(struct db_list* db_list);

void db_list_insert(struct db_list* db_list, void* val);
void db_list_insert_end(struct db_list* db_list, void* val);
void db_list_remove_end(struct db_list* db_list);

void db_list_display_forward(struct db_list* db_list, void (*p)(void* a));
void db_list_display_backward(struct db_list* db_list, void (*p)(void* a));


#endif

 /*
 * This file is where you should implement your linked list. It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name:
 * Email:
 */

#include <stdlib.h>
#include <assert.h>
#include "list.h"

/*
 * This structure is used to represent a single node in a singly-linked list.
 * It is not defined in list.h, so it is not visible to the user.  You should not
 * modify this structure.
 */
struct node
{
    void* val;
    struct node* next;
};

/*
 * This structure is used to represent an entire singly-linked list. Note that
 * we're keeping track of just the head of the list here, for simplicity.
 */
struct list
{
    struct node* head;
};

/*
 * This function should allocate and initialize a new, empty linked list and
 * return a pointer to it.
 */
struct list* list_create()
{
    /*
     * FIXED ME: 
     */
    
    return NULL;
}

/*
 * This function should free the memory associated with a linked list.  In
 * particular, while this function should up all memory used in the list
 * itself (i.e. the space allocated for all of the individual nodes), it should
 * not free any memory allocated to the pointer values stored in the list.  In
 * other words, this function does not need to free the `val` fields of the
 * list's nodes.
 *
 * Params:
 * list - the linked list to be destroyed.  May not be NULL.
 */

void list_free(struct list* list)
{
    /*
     * FIXED ME: 
     */
    return;
}

/*
 * This function should insert a new value into a given linked list.
 * Importantly, this function will need to allocate a new `struct node` in
 * which to store the new value and add that node at the head of the list. 
 * This function should only insert elements at the *beginning* of
 * the list. In other words, it should always insert the new element as the
 * head of the list.
 *
 * Params:
 * list - the linked list into which to insert an element. May not be NULL.
 * val - the value to be inserted. Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */

void list_insert(struct list* list, void* val)
{
    /*
     * FIXED ME: 
     */
    return;
}

/*
 * This function should insert a new value into a given linked list.
 * Importantly, this function will need to allocate a new `struct node` in
 * which to store the new value and add that node at the tail of the list.  
 * This function should only insert elements at the *end* of
 * the list. In other words, it should always insert the new element as the
 * tail of the list.
 *
 * Params:
 * list - the linked list into which to insert an element.  May not be NULL.
 * val - the value to be inserted. Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */

void list_insert_end(struct list* list, void* val)
{
    /*
     * FIXED ME: 
     */
    return;
}

/*
 * This function should remove an element with a specified value from a given
 * linked list. Importantly, if the specified value appears multiple times in
 * the list, the function should only remove the *first* instance of that
 * value (i.e. the one nearest to the head of the list). For example, if a
 * list stores pointers to integers and contains two instances of the value 4,
 * only the first of those values should be removed, and the other one should
 * remain in the list. Importantly, this function will also need to free the
 * memory held by the node being removed (it does not need to free the stored
 * value itself, just the node).
 *
 * This function will be passed a *function pointer* called `cmp` that you
 * should use to compare the value `val` to be removed with the values stored
 * in the list to determine which element (if any) to remove. The cmp function
 * (which will be passed to list_remove() when it's called, so you don't have
 * to worry about writing it yourself) should be passed two void* values,
 * `val` and a value stored in the list against which to compare `val`.  If
 * the two values should be considered as equal, then the function will return
 * 0, and if the two values should be considered as not equal, then the
 * function will return a non-zero value.  For example, part of your code here
 * might look something like this (assuming you're comparing `val` to the `val`
 * field of a specific list node):
 *
 * if (cmp(val, node->val) == 0) {
 *   // Remove node from the list.
 * }
 *
 * For more on function pointers, refer to this tutorial:
 *   https://www.cprogramming.com/tutorial/function-pointers.html
 *
 * Params:
 * list - the linked list from which to remove an element.  May not be NULL.
 * val - the value to be removed.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 * cmp - pointer to a function that can be passed two void* values from
 *     to compare them for equality, as described above.  If the two values
 *     passed are to be considered equal, this function should return 0.
 *     Otherwise, it should return a non-zero value.
 */
void list_remove(struct list* list, void* val, int (*cmp)(void* a, void* b))
{
    /*
     * FIXED ME: 
     */
    return;
}

/*
 * This function should remove the last element from a given
 * linked list. If the list is empty, this function doesn't need to do anything.
 * Importantly, this function will also need to free the
 * memory held by the node being removed (it does not need to free the stored
 * value itself, just the node).

 * Params:
 * list - the linked list from which to remove an element.  May not be NULL.

 */
void list_remove_end(struct list* list)
{
	/*
     * FIXED ME: 
     */
    return;
}


/*
 * This function should return the position (i.e. the 0-based "index") of the
 * first instance of a specified value within a given linked list. For
 * example, if the list contains the specified in the 4th and 8th links
 * starting at the head, then this function should return 3 (the 0-based
 * "index" of the 4th node.). If the value is contained in the head node,
 * then this function should return 0 (the 0-based index of the head node).
 * If the list does not contain the specified value, then this function should
 * return the special value -1.
 *
 * This function will be passed a *function pointer* called `cmp` that you
 * should use to compare the value `val` to be located with the values stored
 * in the list to determine which node (if any) contains `val`. The cmp
 * function (which will be passed to list_position() when it's called, so you
 * don't have to worry about writing it yourself) should be passed two void*
 * values, `val` and a value stored in the list against which to compare `val`.
 * If the two values should be considered as equal, then the cmp function will
 * return 0, and if the two values should be considered as not equal, then the
 * cmp function will return a non-zero value. For example, part of your code
 * here might look something like this (assuming you're comparing `val` to the
 * `val` field of a specific list node):
 *
 * if (cmp(val, node->val) == 0) {
 *   // Return the position of node.
 * }
 *
 * For more on function pointers, refer to this tutorial:
 *   https://www.cprogramming.com/tutorial/function-pointers.html
 *
 * Params:
 * list - the linked list to be searched from. May not be NULL.
 * val - the value to be located. Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 * cmp - pointer to a function that can be passed two void* values from
 *     to compare them for equality, as described above.  If the two values
 *     passed are to be considered equal, this function should return 0.
 *     Otherwise, it should return a non-zero value.
 *
 * Return:
 *   This function should return the 0-based position of the first instance of
 *   `val` within `list`, as determined by the function `cmp` (i.e. the closest
 *    such instance to the head of the list) or -1 if `list` does not contain
 *    the value `val`.
 */
int list_position(struct list* list, void* val, int (*cmp)(void* a, void* b))
{
    /*
     * FIXED ME: 
     */
    return -1;
}

/*
 * This function should reverse the order of the links in a given linked list.
 * The reversal should be done *in place*, i.e. within the existing list, and
 * new memory should not be allocated to accomplish the reversal.  You should
 * be able to accomplish the reversal with a single pass through the list.
 *
 * Params:
 * list - the linked list to be reversed.  May not be NULL.  When this
 *     function returns this should contain the reversed list.
 */
void list_reverse(struct list* list)
{
    /*
     * FIXED ME: 
     */
    return;
}

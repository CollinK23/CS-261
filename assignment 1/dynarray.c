/*
 * This file is where you should implement your dynamic array.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name:
 * Email:
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynarray.h"


/*
 * This is the definition of the dynamic array structure you'll use for your
 * implementation.  Importantly, your dynamic array implementation will store
 * each data element as a void* value.  This will permit data of any type to
 * be stored in your array.  Because each individual element will be stored in
 * your array as type void*, the data array needs to be an array of void*.
 * Hence it is of type void**.
 *
 * You should not modify this structure.
 */
struct dynarray
{
    void** data;
    int size;
    int capacity;
};

/*
 * This function should allocate and initialize a new, empty dynamic array and
 * return a pointer to it.  The array you allocate should have an initial
 * capacity of 2.
 */
struct dynarray* dynarray_create()
{
    /*
     * FIXED ME: 
     */
    struct dynarray* newArray = malloc(sizeof(struct dynarray));
    newArray->data = malloc(2 * sizeof(void**));
    newArray->size = 0;
    newArray->capacity = 2;

    return newArray;
}

/*
 * This function should free the memory associated with a dynamic array.  In
 * particular, while this function should free up all memory used in the array
 * itself (i.e. the underlying `data` array), it should not free any memory
 * allocated to the pointer values stored in the array.  In other words, this
 * function does not need to *traverse* the array and free the individual
 * elements.  This is the responsibility of the caller.
 *
 * Params:
 * da - the dynamic array to be destroyed.  May not be NULL.
 */
void dynarray_free(struct dynarray* da)
{
    /*
     * FIXED ME: 
     */
    free(da->data);
    free(da);
    da = NULL;
    
    return;
}

/*
 * This function should return the size of a given dynamic array (i.e. the
 * number of elements stored in it, not the capacity).
 */
int dynarray_size(struct dynarray* da)
{
    /*
     * FIXED ME: 
     */
    return da->size;
}

/*
 * This function should insert a new value to a given dynamic array.  For
 * simplicity, this function should only insert elements at the *end* of the
 * array.  In other words, it should always insert the new element immediately
 * after the current last element of the array.  If there is not enough space
 * in the dynamic array to store the element being inserted, this function
 * should double the size of the array.
 *
 * Params:
 * da - the dynamic array into which to insert an element.  May not be NULL.
 * val - the value to be inserted.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void dynarray_insert(struct dynarray* da, void* val)
{
    /*
     * FIXED ME: 
     */

    if (da->size == da->capacity){
        da->capacity *= 2;
        da->data = realloc(da->data, da->capacity * sizeof(void*));
    }
    da->data[da->size] = val;
    da->size += 1;
    return;
}

/*
 * This function should remove an element at a specified index from a dynamic
 * array.  All existing elements following the specified index should be moved
 * forward to fill in the gap left by the removed element.  In other words, if
 * the element at index i is removed, then the element at index i+1 should be
 * moved forward to index i, the element at index i+2 should be moved forward
 * to index i+1, the element at index i+3 should be moved forward to index i+2,
 * and so forth.
 *
 * Params:
 * da - the dynamic array from which to remove an element.  May not be NULL.
 * idx - the index of the element to be removed.  The value of `idx` must be
 *     between 0 (inclusive) and n (exclusive), where n is the number of
 *     elements stored in the array.
 */
void dynarray_remove(struct dynarray* da, int idx)
{
    /*
     * FIXED ME: 
     */
    
    if (da->size > 0 && idx < da->size){
        for (int i = idx; i < da->size-1; i++){
            da->data[i] = da->data[i+1];
        }
        da->size -= 1;
    }
    return;

}

/*
 * This function should return the value of an existing element a dynamic
 * array. Note that this value should be returned as type void*.
 *
 * Params:
 * da - the dynamic array from which to get a value.  May not be NULL.
 * idx - the index of the element whose value should be returned.  The value
 *     of `idx` must be between 0 (inclusive) and n (exclusive), where n is the
 *     number of elements stored in the array.
 */
void* dynarray_get(struct dynarray* da, int idx)
{
    /*
     * FIXED ME: 
     */
    return da->data[idx];
}

/*
 * This function should update (i.e. overwrite) the value of an existing
 * element in a dynamic array.
 *
 * Params:
 *   da - the dynamic array in which to set a value.  May not be NULL.
 *   idx - the index of the element whose value should be updated.  The value
 *     of `idx` must be between 0 (inclusive) and n (exclusive), where n is the
 *     number of elements stored in the array.
 *   val - the new value to be set.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void dynarray_set(struct dynarray* da, int idx, void* val)
{
    /*
     * FIXED ME: 
     */

    da->data[idx] = val;
    return; 
}

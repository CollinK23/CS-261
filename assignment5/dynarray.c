/*
 * This file contains a simple implementation of a dynamic array.  See the
 * documentation below for more information on the individual functions in
 * this implementation.
 *
 */

#include <stdlib.h>
#include <assert.h>

#include "dynarray.h"

/*
 * This structure is used to represent a single dynamic array.
 */
struct dynarray {
  void** data;
  int size;
  int capacity;
};

/*
 * You cannot modify the initial capacity 
 */
#define DYNARRAY_INIT_CAPACITY 2

/*
 * This function allocates and initializes a new, empty dynamic array and
 * returns a pointer to it.
 */
struct dynarray* dynarray_create() {
  struct dynarray* da = malloc(sizeof(struct dynarray));
  assert(da);

  da->data = malloc(DYNARRAY_INIT_CAPACITY * sizeof(void*));
  assert(da->data);
  da->size = 0;
  da->capacity = DYNARRAY_INIT_CAPACITY;

  return da;
}

/*
 * This function frees the memory associated with a dynamic array.  Freeing
 * any memory associated with values stored in the array is the responsibility
 * of the caller.
 *
 * Params:
 *   da - the dynamic array to be destroyed.  May not be NULL.
 */
void dynarray_free(struct dynarray* da) {
  assert(da);
  free(da->data);
  free(da);
}

/*
 * This function returns the size of a given dynamic array (i.e. the number of
 * elements stored in it, not the capacity).
 */
int dynarray_size(struct dynarray* da) {
  assert(da);
  return da->size;
}


/*
 * Auxilliary function to perform a resize on a dynamic array's underlying
 * storage array.
 */
void _dynarray_resize(struct dynarray* da, int new_capacity) {
  assert(new_capacity > da->size);

  /*
   * Allocate space for the new array.
   */
  void** new_data = malloc(new_capacity * sizeof(void*));
  assert(new_data);

  /*
   * Copy data from the old array to the new one.
   */
  for (int i = 0; i < da->size; i++) {
    new_data[i] = da->data[i];
  }

  /*
   * Put the new array into the dynarray struct.
   */
  free(da->data);
  da->data = new_data;
  da->capacity = new_capacity;
}

/*
 * This function inserts a new value to a given dynamic array.  The new element
 * is always inserted at the *end* of the array.
 *
 * Params:
 *   da - the dynamic array into which to insert an element.  May not be NULL.
 *   val - the value to be inserted.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void dynarray_insert(struct dynarray* da, void* val) {
  assert(da);

  /*
   * Make sure we have enough space for the new element.  Resize if needed.
   */
  if (da->size == da->capacity) {
    _dynarray_resize(da, 2 * da->capacity);
  }

  /*
   * Put the new element at the end of the array.
   */
  da->data[da->size] = val;
  da->size++;
}

/*
 * This function removes an element at a specified index from a dynamic array.
 * All existing elements following the specified index are moved forward to
 * fill in the gap left by the removed element.
 *
 * Params:
 *   da - the dynamic array from which to remove an element.  May not be NULL.
 *   idx - the index of the element to be removed.  The value of `idx` must be
 *     between 0 (inclusive) and n (exclusive), where n is the number of
 *     elements stored in the array.
 */
void dynarray_remove(struct dynarray* da, int idx) {
  assert(da);
  assert(idx < da->size && idx >= 0);

  /*
   * Move all elements behind the one being removed forward one index,
   * overwriting the element to be removed in the process.
   */
  for (int i = idx; i < da->size - 1; i++) {
    da->data[i] = da->data[i+1];
  }

  da->size--;
}

/*
 * This function returns the value of an existing element in a dynamic array.
 *
 * Params:
 *   da - the dynamic array from which to get a value.  May not be NULL.
 *   idx - the index of the element whose value should be returned.  The value
 *     of `idx` must be between 0 (inclusive) and n (exclusive), where n is the
 *     number of elements stored in the array.
 */
void* dynarray_get(struct dynarray* da, int idx) {
  // assert(da);
  // assert(idx < da->size && idx >= 0);

  return da->data[idx];
}

/*
 * This function updates (i.e. overwrites) the value of an existing element in
 * a dynamic array.
 *
 * Params:
 *   da - the dynamic array in which to set a value.  May not be NULL.
 *   idx - the index of the element whose value should be updated.  The value
 *     of `idx` must be between 0 (inclusive) and n (exclusive), where n is the
 *     number of elements stored in the array.
 *   val - the new value to be set.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void dynarray_set(struct dynarray* da, int idx, void* val) {
  assert(da);
  assert(idx < da->size && idx >= 0);

  da->data[idx] = val;
}

/*
 * This function returns the capacity of the dynamic array
*/
int dynarray_capacity(struct dynarray* da){
  return da->capacity;
}

/*
 * This function updates the value in the dynamic array at the specified index
 *
 * Params:
 *   da - the dynamic array in which to set a value.  May not be NULL.
 *   idx - the index of the element whose value should be updated.  The value
 *     of `idx` must be between 0 (inclusive) and n (exclusive), where n is the
 *     number of elements stored in the array.
 *   val - the new value to be set.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
*/
void dynarray_insert_key(struct dynarray* da, int idx, void* val){
  da->data[idx] = val;
}

/*
 * This function increases the capacity of the dynamic array and returns the old array
 *
 * Params:
 *   da - the dynamic array in which to set a value.  May not be NULL.
 *   new_capacity - capacity of the new array
*/
void* dynarray_increase_capacity(struct dynarray* da, int new_capacity){
  void** new_data = malloc(new_capacity * sizeof(void*)); //Initializes new array

  //Sets all values in new array to NULL
  for (int i = 0; i < new_capacity; i++){
    new_data[i] = NULL;
  }

  void** old_data = da->data; //Copies old data into pointer to array
  da->data = new_data; //Updates the array in the dynarray struct
  da->capacity = new_capacity; //Updates the capacity
  return old_data; //Return old array
}

/*
 * This function updates the value in the dynamic array at the specified index
 *
 * Params:
 *   da - the dynamic array in which to set a value.  May not be NULL.
 *   idx - the index of the element whose value should be updated.  The value
 *     of `idx` must be between 0 (inclusive) and n (exclusive), where n is the
 *     number of elements stored in the array.
 *   newVal - the new value to be set.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
*/
void dynarray_update(struct dynarray* da, int idx, void* newVal){
  free(da->data[idx]); //Frees the current value in the dynarray
  da->data[idx] = newVal; //Updates the value at specified index
}
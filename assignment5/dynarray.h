/*
 * This file contains the definition of the interface for a dynamic array.
 * You can find descriptions of the dynamic array functions, including their
 * parameters and their return values, in dynarray.c.
 *
 * Feel free to add help functions if needed.
 */

#ifndef __DYNARRAY_H
#define __DYNARRAY_H

/*
 * Structure used to represent a dynamic array.
 */
struct dynarray;

/*
 * Dynamic array interface function prototypes.  Refer to dynarray.c for
 * documentation about each of these functions.
 */
struct dynarray* dynarray_create();
void dynarray_free(struct dynarray* da);
int dynarray_size(struct dynarray* da);
void dynarray_insert(struct dynarray* da, void* val);
void dynarray_remove(struct dynarray* da, int idx);
void* dynarray_get(struct dynarray* da, int idx);
void dynarray_set(struct dynarray* da, int idx, void* val);
int dynarray_capacity(struct dynarray* da);
void dynarray_insert_key(struct dynarray* da, int idx, void* val);
void* dynarray_increase_capacity(struct dynarray* da, int new_capacity);
void dynarray_update(struct dynarray* da, int idx, void* newVal);

#endif

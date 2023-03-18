/*
 * In this file, you will write the structures and functions needed to
 * implement a hash table.  Feel free to implement any helper functions
 * you need in this file to implement a hash table.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdlib.h>
#include <stdio.h>

#include "dynarray.h"
#include "list.h"
#include "hash_table.h"


/*
 * This is the structure that represents a hash table.  You must define
 * this struct to contain the data needed to implement a hash table.
 */
struct ht{
    struct dynarray* da;
    int size;
};

struct ht_node{
    void* key;
    void* value;
};


/*
 * This function should allocate and initialize an empty hash table and
 * return a pointer to it.
 */
struct ht* ht_create(){
    /*
     * FIXME: 
     */
    struct ht* ht = malloc(sizeof(struct ht)); //Allocate memory for hash table struct
    ht->da = dynarray_create(); //Initialize new dynamic array
    ht->size = 0;
    for (int i = 0; i < 2; i++){
        dynarray_insert_key(ht->da, i, NULL); //Set all values in dynamic array to NULL
    }
    return ht;
}

/*
 * This function should free the memory allocated to a given hash table.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the hash table.  That is the responsibility of the caller.
 *
 * Params:
 *   ht - the hash table to be destroyed.  May not be NULL.
 */
void ht_free(struct ht* ht){
    /*
     * FIXME: 
     */
    //Frees all nodes in the dynamic array
    for (int i = 0; i < dynarray_capacity(ht->da); i++){
        dynarray_update(ht->da, i, NULL);
    }
    dynarray_free(ht->da); //Frees memory allocated to dynarray struct
    free(ht); //Frees hash table struct
    return;
}

/*
 * This function should return 1 if the specified hash table is empty and
 * 0 otherwise.
 *
 * Params:
 *   ht - the hash table whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if ht is empty and 0 otherwise.
 */
int ht_isempty(struct ht* ht){
    /*
     * FIXME: 
     */
    if (ht->size == 0){
        return 1;
    }
    return 0;
}


/*
 * This function returns the size of a given hash table (i.e. the number of
 * elements stored in it, not the capacity).
 */
int ht_size(struct ht* ht){
    /*
     * FIXME: 
     */
    return ht->size;
}


/*
 * This function takes a key, maps it to an integer index value in the hash table,
 * and returns it. The hash algorithm is totally up to you. Make sure to consider
 * Determinism, Uniformity, and Speed when design the hash algorithm
 *
 * Params:
 *   ht - the hash table into which to store the element.  May not be NULL.
 *   key - the key of the element to be stored
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */
int ht_hash_func(struct ht* ht, void* key, int (*convert)(void*)){
    /*
     * FIXME: 
     */
    int hash;
    hash = convert(key) % dynarray_capacity(ht->da);
    return hash;
}

/*
 * This function rehashes the values in the hashmap when the capacity of the 
 * dynamic array is updated
 *
 * Params:
 *   ht - the hash table into which to store the element.  May not be NULL.
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 *   oldArr - Pointer to the old array values
 *   oldCap - Capacity of the old array
 */
void ht_rehash(struct ht* ht, int (*convert)(void*), void** oldArr, int oldCap){
    //Iterates through old array to rehash values
    for (int i = 0; i < oldCap; i++){
        struct ht_node* curr = oldArr[i];

        //Doesn't rehash if index is empty or index contains a tombstone
        if (curr == NULL || curr->value == NULL){
            continue;
        }
        int idx = ht_hash_func(ht, curr->key, convert); //Rehash key

        //Linear probing
        while (1){
            struct ht_node* newCurr = dynarray_get(ht->da, idx); //Value at specified index in the new array
            
            if (newCurr == NULL){
                dynarray_insert_key(ht->da, idx, curr); //Inserts value from the old array into the new array
                break;
            }

            //Iterates to next index in the hash table
            idx++;

            //Goes back to the beginning of array when index reaches the end
            if (idx == dynarray_capacity(ht->da)){
                idx = 0;
            }
        }
    }
    free(oldArr); //Frees memory allocated to the old array
    return;
}

/*
 * This function should insert a given element into a hash table with a
 * specified key.  Note that you cannot have two same keys in one hash table.
 * If the key already exists, update the value associated with the key.  
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * Resolution of collisions is requried, use either chaining or open addressing.
 * If using chaining, double the number of buckets when the load factor is >= 4
 * If using open addressing, double the array capacity when the load factor is >= 0.75
 * load factor = (number of elements) / (hash table capacity)
 *
 * Params:
 *   ht - the hash table into which to insert an element.  May not be NULL.
 *   key - the key of the element
 *   value - the value to be inserted into ht.
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */

void ht_insert(struct ht* ht, void* key, void* value, int (*convert)(void*)){
    /*
     * FIXME: 
     */

    //Initialize node to be inserted
    struct ht_node* node = malloc(sizeof(struct ht_node));
    node->key = key;
    node->value = value;

    double loadFactor = (double)ht->size / (double)dynarray_capacity(ht->da);
    int capacity = dynarray_capacity(ht->da);

    if (loadFactor >= 0.75){
        void** oldArr = dynarray_increase_capacity(ht->da, 2 * dynarray_capacity(ht->da)); //Increases capacity if load factor is too big
        ht_rehash(ht, convert, oldArr, capacity); //Rehashes values into the hash table
    }

    int idx = ht_hash_func(ht, key, convert); //Index of key to be inserted
    struct ht_node* curr = dynarray_get(ht->da, idx);
    
    //Linear Probing
    while (1){
        curr = dynarray_get(ht->da, idx);
        //Inserts node into the index if the current index is empty or a tombstone value
        if (curr == NULL || curr->key == NULL){
            dynarray_update(ht->da, idx, node); //Inserts new node
            ht->size++; //Increases size
            break;
        }
        //Updates value at specified index instead of inserting
        if (convert(curr->key) == convert(node->key)){
            dynarray_update(ht->da, idx, node); //Update value
            break;
        }

        //Iterates to next index in the hash table if index is already filled
        idx++;

        //Goes back to the beginning of array when index reaches the end
        if (idx == dynarray_capacity(ht->da)){
            idx = 0;
        }
    }
    return;
}


/*
 * This function should search for a given element in a hash table with a
 * specified key provided.   
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * If the key is found, return the corresponding value (void*) of the element,
 * otherwise, return NULL
 *
 * Params:
 *   ht - the hash table into which to loop up for an element.  May not be NULL.
 *   key - the key of the element to search for
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */
void* ht_lookup(struct ht* ht, void* key, int (*convert)(void*)){
    /*
     * FIXME: 
     */
    int idx = ht_hash_func(ht, key, convert); //Index of key to be searched for

    //Linear probing
    while (1){
        struct ht_node* curr = dynarray_get(ht->da, idx); //Gets value at current index
        //element doesn't exist in the array if the index is empty
        if (curr == NULL){
            return NULL;
        }
        //Returns value when the key of the element to search for matches with the key in the array
        if (curr->key && convert(curr->key) == convert(key)){
            return curr->value;
        }

        //Iterates to next index in the hash table if keys don't match
        idx++;

        //Goes back to the beginning of array when index reaches the end
        if (idx == dynarray_capacity(ht->da)){
            idx = 0;
        }
    }
}


/*
 * This function should remove a given element in a hash table with a
 * specified key provided.   
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * If the key is found, remove the element and return, otherwise, do nothing and return 
 *
 * Params:
 *   ht - the hash table into which to remove an element.  May not be NULL.
 *   key - the key of the element to remove
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */
void ht_remove(struct ht* ht, void* key, int (*convert)(void*)){
    /*
     * FIXME: 
     */
    int idx = ht_hash_func(ht, key, convert); //Index of key to be removed

    //Initializes tombstone node to be inserted when the specified element is removed
    struct ht_node* tombstone = malloc(sizeof(struct ht_node));
    tombstone->key = NULL;
    tombstone->value = NULL;

    //Linear probing
    while (1){
        struct ht_node* curr = dynarray_get(ht->da, idx); //Gets element at current index
        //element doesn't exist in the array if the index is empty
        if (curr == NULL){
            break;
        }
        //Removes element when the key being searched for matches with the key in the array
        if (curr->key == key){
            ht->size--;
            dynarray_update(ht->da, idx, tombstone); //Updates the element with the tombstone
            return;
        }
        //Iterates to next index in the hash table if keys don't match
        idx++;

        //Goes back to the beginning of array when index reaches the end
        if (idx == dynarray_capacity(ht->da)){
            idx = 0;
        }
    }
    return;
} 

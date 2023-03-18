/*
 * This is a small program to test your hash table implementation.
 */

#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"

/*
 * This is a convert function to be used to convert the integer key
 */
int convert_int(void* key){
    int *k = key;
    return *k;
}

/*
 * This function returns the number of distinct elements in a given array
 */
int distinct_element (int arr[], int size){
	if (size <= 1) return size;
	int i, j, count = 1;
	for (i = 1; i < size; ++i){
		for (j = 0; j < i; ++j)
			if (arr[i] == arr[j]) break;
		if (i == j) count++;
	}
	return count;
}

int main(void){
    struct ht *ht;
    int *elem_val;
    int i, j, k, key, value, size;
    const int n = 8, m = 8;
    int val1[m+n], val2[m+n];

    /*
     * Seed the random number generator with a constant value, so it produces the
     * same sequence of pseudo-random values every time this program is run.
     */
    srand(0);

    /*
     * Create a hash table and check ht_create()
     */
    ht = ht_create();
    printf("\nChecking that hash table is not NULL... ");
    fflush(stdout);
    if (ht == NULL) 
        printf("FAIL\n");
    else 
        printf("OK\n");

    /*
     * Check if ht is empty, by calling is_empty()
     */
    printf("\nChecking that hash table is empty...\n ");
    printf("is empty? should be 1: %d...", ht_isempty(ht));
    if (ht_isempty(ht) != 1) 
        printf("FAIL\n");
    else 
        printf("OK\n");

    /*
     * Insert an element, and check if ht is empty, by calling is_empty()
     */
    printf("Adding key == 5...\n");
    int e = 5;
    ht_insert(ht, (void*) &e, (void*) &e, convert_int);
    printf("Checking that hash table is empty...\n ");
    printf("is empty? should be 0: %d...", ht_isempty(ht));
    if (ht_isempty(ht) != 0) 
        printf("FAIL\n");
    else 
        printf("OK\n");

    /*
     * Remove the only element, and check if ht is empty, by calling is_empty()
     */
    printf("Remove key == 5...\n");
    ht_remove(ht, (void*) &e, convert_int);
    printf("Checking that hash table is empty...\n ");
    printf("is empty? should be 1: %d...", ht_isempty(ht));
    if (ht_isempty(ht) != 1) 
        printf("FAIL\n");
    else 
        printf("OK\n");


    /*
     * Insert first 8 elements, and look up....
     */
    printf("\nInserting 8 elements...\n ");
    for (i = 0; i < n; ++i){
        val1[i] = rand() % 128;
        val2[i] = val1[i];
        ht_insert(ht, (void*)&val1[i], (void*)&val1[i], convert_int);
    }

    k = 0;
    printf("\n== Lookup Hash Table: Key / Found Value (Expected Value)\n");
    while (k < n){
        elem_val = ht_lookup(ht, (void*) &val2[k], convert_int);
        if (elem_val){
            value = convert_int((void*) elem_val);
            printf("  - %4d / %4d (%4d)\n", val1[k], value, val1[k]);
        }
        else {
            printf("  - %4d / NULL (%4d)\n", val1[k], val1[k]);
        }
        k++;
    }
    printf("== Did we see all values we expected (expect 1)? %d\n", k == n);

    printf("Checking size...\n ");
    size = distinct_element(val1, n);
    printf("size should be %d: %d...", size, ht_size(ht));
    if (ht_size(ht) != size) 
        printf("FAIL\n");
    else 
        printf("OK\n");



    printf("\nLookup for a key that does not exist in the hash table...\n");
    k = 256;
    elem_val = ht_lookup(ht, (void*) &k, convert_int);
    printf(" should return null: %s...", elem_val == NULL ? "null" : "non-null");
    if (elem_val != NULL)
        printf("FAIL\n");
    else 
        printf("OK\n");

    /*
     * Re-Inserting the same 8 elements....
     * Keys already exist, should not insert
     */
    for (i = 0; i < n; ++i){
        ht_insert(ht, (void*)&val2[i], (void*)&val2[i], convert_int);
    }
    printf("\nAfter reinserting the same 8 elements...\nChecking size...\n ");
    printf("size should be %d: %d...", size, ht_size(ht));
    if (ht_size(ht) != size) 
        printf("FAIL\n");
    else 
        printf("OK\n");

    /*
     * Inserting another 8 elements and look up...
     */
    printf("\nInserting next 8 elements ...\n ");
    for (i = n; i < n+m; ++i){
        val1[i] = rand() % 64;
        val2[i] = val1[i];
        ht_insert(ht, (void*)&val2[i], (void*)&val2[i], convert_int);
    }

    k = 0;
    printf("\n== Lookup Hash Table: Key / Found Value (Expected Value)\n");
    while (k < n+m){
        elem_val = ht_lookup(ht, (void*) &val2[k], convert_int);
        if (elem_val){
            value = convert_int((void*) elem_val);
            printf("  - %4d / %4d (%4d)\n", val1[k], value, val1[k]);
        }
        else {
            printf("  - %4d / NULL (%4d)\n", val1[k], val1[k]);
        }
        k++;
    }
    printf("== Did we see all values we expected (expect 1)? %d\n", k == n+m);

    printf("Checking size...\n ");
    size = distinct_element(val1, n+m);
    printf("size should be %d: %d...", size, ht_size(ht));
    if (ht_size(ht) != size) 
        printf("FAIL\n");
    else 
        printf("OK\n");


    /*
     * Remove the first 8 elements inserted...
     */
    printf("Removing first 8 element inserted...\n");
    for (i = 0; i < n; ++i){
        ht_remove(ht, (void*)&val2[i], convert_int);
    }
    printf("Checking size...\n ");
    size = size - distinct_element(val1, n);
    printf("size should be %d: %d...", size, ht_size(ht));
    if (ht_size(ht) != size) 
        printf("FAIL\n");
    else 
        printf("OK\n");

    /*
     * Look up for the next 8 elements inserted...
     */
    printf("\n== Lookup Hash Table: Key / Found Value (Expected Value)\n");
    k = 0;
    while (k < n){
        elem_val = ht_lookup(ht, (void*) &val2[k+n], convert_int);
        if (elem_val){
            value = convert_int((void*) elem_val);
            printf("  - %4d / %4d (%4d)\n", val1[k+n], value, val1[k+n]);
        }
        else {
            printf("  - %4d / NULL (%4d)\n", val1[k+n], val1[k+n]);
        }
        k++;
    }
    printf("== Did we see all values we expected (expect 1)? %d\n", k == n);

    printf("\n\nCheck valgrind for memory leaks...\n");

    ht_free(ht);

    return 0;
}
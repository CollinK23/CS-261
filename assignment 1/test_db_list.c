/** EXTRA CREDITS **/

/*
 * This file contains executable code for testing your doubly-linked list
 * implementation.
 */

#include <stdio.h>
#include <stdlib.h>

#include "db_list.h"
#include "test_data.h"

/*
 * Function to run tests on linked list implementation.
 */
void test_db_list(struct student** students, int n) 
{
    struct db_list* db_list;
    struct student* s;
    int i, p;

    /*
     * Create a list.
     */
    db_list = db_list_create();
    printf("Checking that doubly-linked list is not NULL... ");
    fflush(stdout);
    if (db_list == NULL)
        printf("FAILED\n");
    else
      printf("OK\n");
    

    /*
     * Add students to list (in reverse order, so the list order matches the
     * order of the input array).
     */
    printf("\n");
    for (i = n - 1; i >= 0; i--) {
        printf("Adding students[%d] to the beginning of the doubly-linked list... ", i);
        fflush(stdout);
        db_list_insert(db_list, students[i]);
        printf("OK (check for display below)\n");
    }

    /*
     * Check that we can display the doubly-linked list in both orders.
     */
    printf("\n");
    printf("Display the doubly-linked list forward...\n");

    printf("Expected:\n");
    for (i = 0; i < n; ++i)
    {
        print_student((void*)students[i]);
    }
    
    printf("\n");
    printf("Actual:\n");
    db_list_display_forward(db_list, &print_student);
    

    printf("\n");
    printf("Display the doubly-linked list backward...\n");

    printf("Expected:\n");
    for (i = n-1; i >= 0; --i)
    {
        print_student((void*)students[i]);
    }

    printf("\n");
    printf("Actual:\n");
    db_list_display_backward(db_list, &print_student);  
    


    printf("\nFreeing doubly-linked list... ");
    fflush(stdout);
    db_list_free(db_list);
    printf("OK (check valgrind output to ensure no memory leaks)\n");


    db_list = db_list_create();

    printf("\nAdding more elements back....\n");
    /*
     * Add students to list (the same order as insertion).
     */
    printf("\n");
    for (i = 0; i < n; i++) {
        printf("Adding students[%d] to the end of the doubly-linked list... ", i);
        fflush(stdout);
        db_list_insert_end(db_list, students[i]);
        printf("OK (check for correct positions below)\n");
    }

    /*
     * Check that we can display the doubly-linked list.
     */
    printf("\n");
    printf("Display the doubly-linked list forward...\n");

    printf("Expected:\n");
    for (i = 0; i < n; ++i)
    {
        print_student((void*)students[i]);
    }

    printf("\n");
    printf("Actual:\n");
    db_list_display_forward(db_list, &print_student);
    

    /*
     * Test removing students from the end.
     */
    for (i = n - 1; i > n/2; i--) {
        printf("\nRemoving students[%d]... ", i);
        fflush(stdout);
        db_list_remove_end(db_list);
        printf("OK (check below to make sure removed correctly)\n");
    }

    printf("\n");
    printf("Display the doubly-linked list backward...\n");

    printf("Expected:\n");
    for (i = n/2; i >= 0; --i)
    {
        print_student((void*)students[i]);
    }

    printf("\n");
    printf("Actual:\n");
    db_list_display_backward(db_list, &print_student);
    

    printf("\nFreeing doubly-linked list again... ");
    fflush(stdout);
    db_list_free(db_list);

    printf("OK (check valgrind output to ensure no memory leaks)\n");
}

int main(int argc, char** argv) 
{
    struct student** students;
    int i;

    /*
     * Create and fill an array of student structs.
     */
    students = malloc(NUM_TESTING_STUDENTS * sizeof(struct student*));
    for (i = 0; i < NUM_TESTING_STUDENTS; i++) {
        students[i] = malloc(sizeof(struct student));
        students[i]->name = TESTING_NAMES[i];
        students[i]->id = TESTING_IDS[i];
        students[i]->gpa = TESTING_GPAS[i];
    }

    test_db_list(students, NUM_TESTING_STUDENTS);

    /*
     * Free the array of student structs.
     */
    for (i = 0; i < NUM_TESTING_STUDENTS; i++) {
        free(students[i]);
    }
    free(students);

    return 0;
}

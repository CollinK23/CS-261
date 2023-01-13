/*
 * This file contains data and related structures and functions for testing.
 */

#ifndef __TEST_DATA_H
#define __TEST_DATA_H

/*
 * This is the total number of students in the testing data set.
 */
#define NUM_TESTING_STUDENTS 8


/*
 * These are the names of the students that'll be used for testing.
 */
char* TESTING_NAMES[] = {
    "Luke Skywalker",
    "Leia Organa",
    "Rey",
    "Han Solo",
    "Lando Calrissian",
    "Darth Vader",
    "Finn",
    "R2-D2"
};


/*
 * These are the student IDs for the students in the array above that will be
 * used for testing.
 */
int TESTING_IDS[] = {
    933111111,
    933222222,
    933333333,
    933444444,
    933555555,
    933666666,
    933777777,
    933888888
};


/*
 * These are the GPAs of the students above that will be used for testing.
 */
float TESTING_GPAS[] = {
    3.75,
    4.0,
    3.9,
    2.5,
    3.67,
    1.33,
    3.25,
    3.9
};


/*
 * This structure represents information about a single university student.
 */
struct student 
{
    char* name;
    int id;
    float gpa;
};


/*
 * This function compares two students based on their `id`. Specifically, it
 * returns 0 if their `id` fields are equal and returns a non-zero value
 * otherwise.  It is used to compare students stored in the linked list when
 * calling list_remove() and list_position().
 */
int compare_students(void* a, void* b) 
{
    struct student* s_a = a, * s_b = b;
    return s_a->id - s_b->id;
}

/*
 * This function prints the student info to the console.
 * It is used to print students stored in the doubly-linked list when
 * calling db_list_display_forward() and db_list_display_forward().
 */
void print_student (void* a)
{
    struct student* s = a;
    printf ("Name: %s\n", s->name);
    printf ("ID: %d\t GPA: %f\n", s->id, s->gpa);
}

#endif

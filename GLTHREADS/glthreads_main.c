#include <stdio.h>
#include <string.h>
#include "glthreads.h"

/* Application structure */
typedef struct Employee {
    int id;
    char name[20];
    int salary;
    glthread_node_t node;
} Employee;

int main(){

    /* Step 1: Initialize list */
    glthread_t emp_list;
    init_glthread(&emp_list, offsetof(Employee, node));

    /* Step 2: Create employees */
    Employee e1 = {1, "Alice", 50000};
    Employee e2 = {2, "Bob", 60000};
    Employee e3 = {3, "Charlie", 70000};

    /* Initialize nodes */
    glthread_node_init(&e1.node);
    glthread_node_init(&e2.node);
    glthread_node_init(&e3.node);

    /* Step 3: Add employees */
    glthread_add(&emp_list, &e1.node);
    glthread_add(&emp_list, &e2.node);
    glthread_add(&emp_list, &e3.node);

    printf("After adding employees:\n");

    Employee *emp = NULL;
    ITERATE_GL_THREADS_BEGIN(&emp_list, Employee, emp){
        printf("ID: %d, Name: %s, Salary: %d\n",
               emp->id, emp->name, emp->salary);
    } ITERATE_GL_THREADS_ENDS;

    /* Step 4: Remove Bob */
    printf("\nRemoving Bob...\n");
    glthread_remove(&emp_list, &e2.node);

    printf("\nAfter removal:\n");

    ITERATE_GL_THREADS_BEGIN(&emp_list, Employee, emp){
        printf("ID: %d, Name: %s, Salary: %d\n",
               emp->id, emp->name, emp->salary);
    } ITERATE_GL_THREADS_ENDS;

    return 0;
}

#include<stdio.h>
#include <hello_thread.h>

void* hello_thread_run(void* arg){
    int* id = (int*)arg;

    printf("%s %d\n", HELLO_MESSAGE, *id);

    return NULL;
}
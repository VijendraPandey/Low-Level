#include <stdio.h>
#include <pthread.h>
#include "hello_thread.h"

int main(void)
{
    pthread_t t_id;

    if(pthread_create(&t_id, NULL, hello_thread_run, NULL) != 0){
        perror("Thread creation failed\n");
        return 1;
    }

    if(pthread_join(t_id, NULL) != 0){
        perror("Thread joining failed\n");
        return 1;
    }

    return 0;
}
#include<stdio.h>
#include<pthread.h>
#include "struct_hello_thread.h"

#define SIZE 5

int main(void){
    pthread_t t_ids[SIZE];
    hello_thread_config_t configs[SIZE];

    for(int i=0; i<SIZE; i++){
        configs[i].id = i+1;
        configs[i].repeat = i+1;
        configs[i].message = HELLO_MESSAGE;

        if(pthread_create(&t_ids[i], NULL, hello_thread_run, &configs[i]) != 0){
            perror("Thread creation failed");
            return 1;
        };
    }

    for(int i=0; i<SIZE; i++){
        pthread_join(t_ids[i], NULL);
    }

    return 0;
}
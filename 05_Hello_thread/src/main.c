#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include "struct_hello_thread.h"

#define SIZE 5

int main(void){
    pthread_t t_ids[SIZE];
    hello_thread_config_t* configs[SIZE];

    for(int i=0; i<SIZE; i++){
        hello_thread_config_t* config = malloc(sizeof(hello_thread_config_t));
        config->id = i+1;
        config->repeat = SIZE;
        config->message = HELLO_MESSAGE;
        configs[i]=config;

        if(pthread_create(&t_ids[i], NULL, hello_thread_run, config) != 0){
            perror("Thread creation failed");
            return 1;
        }
    }

    for(int i=0; i<SIZE; i++){
        pthread_join(t_ids[i], NULL);
        free(configs[i]);
    }

    return 0;
}
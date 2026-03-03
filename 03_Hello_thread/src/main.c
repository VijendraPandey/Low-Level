#include <stdio.h>
#include <hello_thread.h>
#include <pthread.h>

#define SIZE 3

int main(void)
{

    pthread_t t_id[SIZE];
    int ids[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        ids[i] = i+1;
        if (pthread_create(&t_id[i], NULL, hello_thread_run, &ids[i]) != 0)
        {
            perror("Thread creation failed");
            return 1;
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        if (pthread_join(t_id[i], NULL) != 0)
        {
            perror("Thread join failed");
            return 1;
        }
    }


    // pthread_t t_id1, t_id2, t_id3;

    // int id1 = 1;
    // int id2 = 2;
    // int id3 = 3;

    // if(pthread_create(&t_id1, NULL, hello_thread_run, &id1) != 0){
    //     perror("Thread 1 creation failed");
    //     return 1;
    // }

    // if(pthread_create(&t_id2, NULL, hello_thread_run, &id2) != 0){
    //     perror("Thread 2 creation failed");
    //     return 1;
    // }

    // if(pthread_create(&t_id3, NULL, hello_thread_run, &id3) != 0){
    //     perror("Thread 3 creation failed");
    //     return 1;
    // }

    // if(pthread_join(t_id1, NULL) != 0){
    //     perror("Thread 1 join failed");
    //     return 1;
    // }

    // if(pthread_join(t_id2, NULL) != 0){
    //     perror("Thread 2 join failed");
    //     return 1;
    // }

    // if(pthread_join(t_id3, NULL) != 0){
    //     perror("Thread 3 join failed");
    //     return 1;
    // }

    return 0;
}
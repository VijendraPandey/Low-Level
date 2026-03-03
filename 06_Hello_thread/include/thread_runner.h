#ifndef THREAD_RUNNER_H
#define THREAD_RUNNER_H

#include <pthread.h>

/* Thread abstraction */
typedef struct
{
    pthread_t tid;
} thread_runner_t;

/* Start thread */
int thread_runner_start(thread_runner_t* runner,
                        void* (*fn)(void*),
                        void* arg);

/* Join thread */
int thread_runner_join(thread_runner_t* runner);

#endif
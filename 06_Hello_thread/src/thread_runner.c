#include "thread_runner.h"

int thread_runner_start(thread_runner_t* runner,
                        void* (*fn)(void*),
                        void* arg)
{
    if (!runner || !fn)
        return -1;

    return pthread_create(&runner->tid, NULL, fn, arg);
}

int thread_runner_join(thread_runner_t* runner)
{
    if (!runner)
        return -1;

    return pthread_join(runner->tid, NULL);
}
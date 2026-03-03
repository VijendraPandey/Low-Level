#include <stdio.h>
#include "thread.h"
#include <unistd.h>

void *hello_thread_run(void *arg)
{
    hello_thread_config_t *config = (hello_thread_config_t *)arg;

    for (int i = 0; i < config->repeat; i++)
    {
        printf("[Thread %d]: %s (%d/%d)\n", config->id, config->message, i + 1, config->repeat);
        sleep(1);
    }

    return NULL;
}
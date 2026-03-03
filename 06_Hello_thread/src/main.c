#include <stdio.h>
#include <stdlib.h>

#include "thread.h"
#include "thread_runner.h"

#define SIZE 5

int main(void)
{
    thread_runner_t runners[SIZE];
    hello_thread_config_t* configs[SIZE];

    for (int i = 0; i < SIZE; i++) {

        hello_thread_config_t* cfg =
            malloc(sizeof(hello_thread_config_t));

        if (!cfg) {
            perror("malloc failed");
            return 1;
        }

        cfg->id = i + 1;
        cfg->repeat = SIZE;
        cfg->message = HELLO_MESSAGE;

        configs[i] = cfg;

        if (thread_runner_start(&runners[i],
                                hello_thread_run,
                                cfg) != 0) {
            perror("thread start failed");
            return 1;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        thread_runner_join(&runners[i]);
        free(configs[i]);
    }

    return 0;
}
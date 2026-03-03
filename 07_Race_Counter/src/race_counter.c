#include <stdio.h>
#include "race_counter.h"

/* Shared global state (intentionally unsafe) */
static int g_counter = 0;

void* counter_thread_run(void* arg)
{
    (void)arg;

    for (int i = 0; i < INCREMENTS; i++) {
        g_counter++;   /* Race condition here */
    }

    return NULL;
}

int get_counter_value(void)
{
    return g_counter;
}
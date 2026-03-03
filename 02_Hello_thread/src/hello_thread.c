#include <stdio.h>
#include "hello_thread.h"

void *hello_thread_run(void *arg)
{
    (void)arg;

    printf("%s", HELLO_MESSAGE);

    return NULL;
}
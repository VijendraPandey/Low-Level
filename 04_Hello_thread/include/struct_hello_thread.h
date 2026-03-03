#ifndef HELLO_THREAD_H
#define HELLO_THREAD_H

#define HELLO_MESSAGE "Hello from thread"

typedef struct
{
    int id;
    int repeat;
    const char* message;
} hello_thread_config_t;

void *hello_thread_run(void *arg);

#endif
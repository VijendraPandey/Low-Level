#ifndef HELLO_THREAD_H
#define HELLO_THREAD_H

#define HELLO_MESSAGE "Hello from thread\n"

/* Thread entry function */
void* hello_thread_run(void* arg);

#endif /* HELLO_THREAD_H */
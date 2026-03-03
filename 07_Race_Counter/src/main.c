#include <stdio.h>
#include <pthread.h>
#include "race_counter.h"

int main(void)
{
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL,
                           counter_thread_run, NULL) != 0) {
            perror("pthread_create failed");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join failed");
            return 1;
        }
    }

    int expected = NUM_THREADS * INCREMENTS;
    int actual = get_counter_value();

    printf("Expected: %d\n", expected);
    printf("Actual  : %d\n", actual);

    return 0;
}
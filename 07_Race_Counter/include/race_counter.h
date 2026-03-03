#ifndef RACE_COUNTER_H
#define RACE_COUNTER_H

#define NUM_THREADS 5
#define INCREMENTS 100000

/* Thread entry function */
void* counter_thread_run(void* arg);

/* Expose getter for global counter */
int get_counter_value(void);

#endif /* RACE_COUNTER_H */
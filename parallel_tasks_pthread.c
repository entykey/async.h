#include <unistd.h> // for usleep

#include "async.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h> // Include pthread library

/* Flag to indicate whose turn it is to execute */
static bool async1_turn;

/**
 * Get current time in microseconds.
 */
static double current_time_us() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000.0 + ts.tv_nsec / 1000.0;
}

/**
 * Get current time in nanoseconds.
 */
static double current_time_ns() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000000.0 + ts.tv_nsec;
}

/**
 * The first async function.
 */
static async
async1(struct async *pt)
{
    async_begin(pt);

    double start_time_us = current_time_us();
    double start_time_ns = current_time_ns();

    printf("async 1 running\n");
    // Simulate some calculation task
    // In this example, we just sleep for a short duration
    usleep(800000); // Sleep for 800ms
    printf("async 1 done\n");

    double end_time_us = current_time_us();
    double end_time_ns = current_time_ns();

    double elapsed_time_us = end_time_us - start_time_us;
    double elapsed_time_ns = end_time_ns - start_time_ns;

    printf("async 1 execution time: %.6f ms (%.6f us) (%.6f ns)\n", elapsed_time_us / 1000.0, elapsed_time_us, elapsed_time_ns);

    async_end;
}

/**
 * The second async function.
 */
static async
async2(struct async *pt)
{
    async_begin(pt);

    double start_time_us = current_time_us();
    double start_time_ns = current_time_ns();

    printf("async 2 running\n");
    // Simulate some calculation task
    // In this example, we just sleep for a short duration
    usleep(300000); // Sleep for 300ms
    printf("async 2 done\n");

    double end_time_us = current_time_us();
    double end_time_ns = current_time_ns();

    double elapsed_time_us = end_time_us - start_time_us;
    double elapsed_time_ns = end_time_ns - start_time_ns;

    printf("async 2 execution time: %.6f ms (%.6f us) (%.6f ns)\n", elapsed_time_us / 1000.0, elapsed_time_us, elapsed_time_ns);

    async_end;
}

/**
 * The main function, serving as the entry point of the program.
 */
int main() {
    struct async pt1, pt2;
    async_init(&pt1);
    async_init(&pt2);

    async1_turn = true;

    double main_start_time_us = current_time_us();
    double main_start_time_ns = current_time_ns();

    // Create pthreads to run async functions concurrently
    pthread_t thread1, thread2;
    // pthread_create(&thread1, NULL, async1, &pt1);
    // pthread_create(&thread2, NULL, async2, &pt2);
    pthread_create(&thread1, NULL, (void *(*)(void *))async1, &pt1);
    pthread_create(&thread2, NULL, (void *(*)(void *))async2, &pt2);


    // Wait for threads to finish execution
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    double main_end_time_us = current_time_us();
    double main_end_time_ns = current_time_ns();

    double main_elapsed_time_us = main_end_time_us - main_start_time_us;
    double main_elapsed_time_ns = main_end_time_ns - main_start_time_ns;

    printf("\n⌛️ Execution time: %.6f ms (%.6f us) (%.6f ns)\n", main_elapsed_time_us / 1000.0, main_elapsed_time_us, main_elapsed_time_ns);

    return 0;
}

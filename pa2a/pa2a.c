// PA2A Nicholas Miller

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"

/* Global variables entered by the user that will be
 * referenced by all threads.
 */
int n;
long thread_count;
// Global variable factorial holds the resulting factorial.
long long int factorial = 1;
// Global mutex that will be used to control updates to factorial.
pthread_mutex_t mutex;
/* Global struct that will contain the arguments for Pth_Factorial;
 * in particular, it contains each thread's start value and rank.
 */
struct factorial_args {
    long rank;
    int start;
};


// Get_Input reads in the user's input from the command line.
void Get_Input(int argc, char **argv) {
        printf("Please enter the number of threads to use: ");
        fflush(stdout);
        scanf("%li", &thread_count);
}

/* Pth_Factorial computes the partial product for each
 * thread for their chunk of the factorial for N!.
 *  Parameters:
 *    args: contains a pointer to a struct factorial_args.
 */
void* Pth_Factorial(void* args) {
    // my_args holds this thread's arguments.
    struct factorial_args *my_args = (struct factorial_args *) args;
    // partial holds the partial product for the thread.
    long long int partial = 1;

    // len holds the number of values this thread should multiply.
    long len = 0;
    if (my_args->start != 0)
        len = n/thread_count +
            // Spread the remainder out over the threads smaller than the remainder.
            (my_args->rank <= (n - (n / thread_count) * thread_count) - 1 ? 1 : 0);


    // Compute the partial product.
    if (len > 0) {
        long i = my_args->start;
        for (; i <= my_args->start + (len - 1); i++)
            partial *= i;
        // Multiply the result to factorial.
        pthread_mutex_lock(&mutex);
        factorial *= partial;
        pthread_mutex_unlock(&mutex);
    }

    // Clean up my_args (was not freed in main).
    free(my_args);
    
    return NULL;
}

void Create_Array(int array[], int size) {
    srand ( time(NULL));

    for (int i = 0; i < size; i++) {
        int num = (rand() % 
            (50 - 1 +1)) + 1;
        array[i] = num;
    }
}

int main(int argc, char** argv) {

    struct timespec start, stop;
    double elapsed;

    // Threads holds references to the Pthreads that will execute Pth_Factorial.
    pthread_t *threads;

    Get_Input(argc, argv);

    int arraySizes[] = { 1000, 2000, 4000, 8000, 16000 };

    for (int loop = 0; loop < 5; loop++){

    int size = arraySizes[loop];
    
        int array[size];

        Create_Array(array, size);
        clock_gettime(CLOCK_MONOTONIC, &start);

        for (int x = 0; x < array[x]; x++) {
            // Initialize mutex.
            pthread_mutex_init(&mutex, NULL);
    
    
            // Create and initialize the threads.
            threads = malloc(sizeof(pthread_t)*thread_count);

            long j;
            int start = 1;
            for (j = 0; j < thread_count; j++) {
                // Declare a new factorial_args to hold the thread's arguments.
                struct factorial_args *args = (struct factorial_args *)malloc(sizeof(struct factorial_args));
                args->start = (j < array[x] ? start : 0); // Set start to zero for threads that equal or exceed n.
                args->rank = j;
        
                // Create the thread and pass in the arguments.
                pthread_create(&threads[j], NULL, Pth_Factorial, (void*) args);
        
                // Increment the start value for the next thread.
                if (j < array[x])
                    start += array[x]/thread_count +
                        // Spread the remainder out over the threads smaller than the remainder.
                        (j <= (array[x] - (array[x] / thread_count) * thread_count) - 1 ? 1 : 0);
            }

            // Destroy the threads.
            for(long h = 0; h < thread_count; h++)
                pthread_join(threads[h], NULL);


            // Free the pthreads_t array, mutex, and exit.
            free(threads);
            pthread_mutex_destroy(&mutex);
        }
        clock_gettime(CLOCK_MONOTONIC, &stop);
        elapsed = stop.tv_sec - start.tv_sec;
        elapsed += (stop.tv_nsec - start.tv_nsec) / 1000000000.0;

        printf("Time for size %d: %f\n", size, elapsed);
    }  
}
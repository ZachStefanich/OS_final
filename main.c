#include <pthread.h>
#include "semaphore.h" 
#include <stdio.h>

// Declare semaphores
sem_t sem1, sem2;


int main() {
    // Initialize semaphores
    sem_init(&sem1, 0,0);  // Start at 0, so Thread B waits
    sem_init(&sem2, 0,0);  // Start at 0, so Thread A waits
    printf("Test");

    return 0;
}
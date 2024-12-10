#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 10
typedef struct{
    int thread_id;
    void(*func)();
}thread_data_t;

void *thread_gen(void *arg) {
	thread_data_t *data = (thread_data_t *)arg;
	printf("Hello from thread %d\n", data->thread_id);
	data->func();  // Call the function passed
	return NULL;
}

void dummy_print(){
    printf("dummy");
    return;
}
int main(int argc, char *argv[]) {
    int num_threads; // Change this to create a different number of threads
    pthread_t threads[MAX_THREADS];
    thread_data_t thread_data[MAX_THREADS];
    int done = 0;
    while (done == 0) {
		printf("Enter a number of threads (10 or fewer): ");
		if (scanf("%d", &num_threads) != 1) {
			// Handle invalid (non-integer) input
			printf("\nInvalid input. Please enter a valid number.\n");
			while (getchar() != '\n');  // Clear the input buffer
			continue;
		}

		if (num_threads <= MAX_THREADS && num_threads > 0) {
			done = 1;
		} else {
			printf("\nBro, I told you 10 or fewer and greater than 0.\n");
		}
	}
    printf("Number of threads selected: %d\n", num_threads);
    if (num_threads > MAX_THREADS) {
        printf("Error: Maximum number of threads exceeded\n");
        return 1;
    }

  for (int i = 0; i < num_threads; i++) {
		thread_data[i].thread_id = i;
		thread_data[i].func = dummy_print;
		if (pthread_create(&threads[i], NULL, thread_gen, &thread_data[i]) != 0) {
			perror("pthread_create failed");
			exit(EXIT_FAILURE);
		}
	}
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    dummy_print();
    return 0;
}
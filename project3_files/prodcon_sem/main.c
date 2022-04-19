#include "buffer_sem.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>
//#include <linux/semaphore.h>

void *producer(void *ptr);
void *consumer(void *ptr);

int main() {

	pthread_t thread1, thread2;
	int p1, p2;
	char* input;
	char* output;
	init_buffer_421();

	for(int i = 0; i < 1000; i++) {
		printf("\tRun %d\n", i+1);
		input = malloc(DATA_LENGTH);
		output = malloc(DATA_LENGTH);

		for(int j = 0; j < DATA_LENGTH; j++) {
			input[j] = (char)(j%10+48);
		}

		p1 = pthread_create(&thread1, NULL, producer, input);
		p2 = pthread_create(&thread2, NULL, consumer, output);

		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);

		printf("Thread 1 returns %d\nThread 2 returns %d\n", p1, p2);
		free(input);
		free(output);
	}

	delete_buffer_421();
//	free(input);
//	free(output);
	return 0;
}

void *producer( void *ptr )
{
	char* input;
	input = (char *) ptr;

	float stime = 0.0010*(rand()%11);
	printf("Producer wait for %f s...\n", stime);
//	wait((int *)1000);
	sleep(stime);

	long i = enqueue_buffer_421(input);
	if (i < 0) {
		printf("Producer unsuccessful\n");
	}
	else {
		printf("Producer successful\n");
	}
	return (void *) i;
}

void *consumer( void *ptr )
{
	char* output;
	output = (char *) ptr;

	float stime = 0.0010*(rand()%11);
	printf("Consumer wait for %f s...\n", stime);
//	wait((int *)1000);
	sleep(stime);

	long i = dequeue_buffer_421(output);
	if (i < 0) {
		printf("Consumer unsuccessful\n");
	}
	else {
		printf("Consumer successful\n");
	}
	return (void *) i;
}

#include "buffer_sem.h"
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
//#include <linux/semaphore.h>

int main() {

	pthread_t thread1, thread2;
	char* m1  = "Thread 1";
	char* m2 = "Thread 2";
	int p1, p2;
	char* hello = malloc(1024);

	enqueue_buffer_421("hi!");
	dequeue_buffer_421(hello);
	init_buffer_421();

	init_buffer_421();
	print_semaphores();
	enqueue_buffer_421("hi!");
	enqueue_buffer_421("Hello!");
	dequeue_buffer_421(hello);
	printf("%s\n", hello);
	dequeue_buffer_421(hello);
	printf("%s\n", hello);

	delete_buffer_421();
	enqueue_buffer_421("Hello!");
	dequeue_buffer_421(hello);
	init_buffer_421();
	print_semaphores();

	free(hello);
	return 0;
}

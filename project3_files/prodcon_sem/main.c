#include "buffer_sem.h"
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
//#include <linux/semaphore.h>

int main() {

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

#include <semaphore.h>
//#include <linux/semaphore.h>
#include "buffer_mon.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

struct ring_buffer_421* buffer;
struct node_421* head = NULL;
struct node_421* pointer = NULL;
pthread_mutex_t mutex;
pthread_cond_t full_buffer;
pthread_cond_t empty_buffer;

long init_buffer_421(void) {

//	if buffer already initialized return -1
	if (buffer != NULL) {
		fprintf(stderr, "Error: Attempting to initalize an already initialized buffer.\n");
		return -1;
	}

//	fprintf(stdout, "init_buffer_421 called\n");

	buffer = malloc(DATA_LENGTH * SIZE_OF_BUFFER);

	head = malloc(sizeof(struct node_421));
	head->next = head;

	buffer->write = head;
	buffer->read = head;
	buffer->length = 0;

// 	let insert_buffer_init_421(int i) handle insertion after head is inserted
	for (int i = 1; i < SIZE_OF_BUFFER; i++) {
		pointer = malloc(sizeof(struct node_421));
		pointer->next = buffer->write->next;

		buffer->write->next = pointer;
		buffer->write = buffer->write->next;
//		print_buffer_421(); //debug print statement
	}

//	link final node->next to head, completing the circle
	buffer->write->next = head;

//	after insertion, set write->next to head
	buffer->write = head;

//	fprintf(stdout, "write is at node %d\n", buffer->write->data);

//	pthread initializations
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&empty_buffer, NULL);
	pthread_cond_init(&full_buffer, NULL);

	return 0;
}

long enqueue_buffer_421(char* data) {
//	if buffer is uninitialized cannot insert, fails
	if (buffer == NULL) {
		printf("Error: Attempting to enqueue into an uninitialized buffer.\n");
		return -1;
	}

	pthread_mutex_lock(&mutex);
	while (buffer->length == SIZE_OF_BUFFER) {
		printf("Enqueue called while buffer is full, waiting...\n");
		pthread_cond_wait(&full_buffer, &mutex);
	}

	memcpy(buffer->write->data, data, DATA_LENGTH);
	buffer->write = buffer->write->next;
	buffer->length++;

	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&empty_buffer);

	return 0;
}

long dequeue_buffer_421(char* data) {
	if(buffer == NULL) {
		printf("Error: Attempting to dequeue into an uninitialized buffer.\n");
		return -1;
	}

	pthread_mutex_lock(&mutex);

	while(buffer->length == 0) {
		printf("Dequeue called while buffer is empty, waiting...\n");
		pthread_cond_wait(&empty_buffer, &mutex);
	}

	memcpy(data, buffer->read->data, DATA_LENGTH);
	pointer = buffer->read->next;
	memcpy(buffer->read->data, "", DATA_LENGTH);
	buffer->read->next = pointer;
	buffer->length--;

	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&full_buffer);

	return 0;
}

long delete_buffer_421(void) {
//	if buffer is uninitialized / already deleted, fails.
	if (buffer == NULL) {
		fprintf(stderr, "Error: Attempting to delete an uninitialized buffer.\n");
		return -1;
	}

	buffer->write = head;

	for (int i = 0; i < SIZE_OF_BUFFER; i++) {
	//while (buffer->write->next != NULL && i < SIZE_OF_BUFFER) {
//		fprintf(stdout, "Attempting to free node [%d, %d]\n", i+1, buffer->write->data);
		pointer = buffer->write->next;
		free(buffer->write);
		buffer->write = pointer;
		buffer->length--;
	}

//	fprintf(stdout, "All nodes freed. Freeing buffer...\n");
	free(buffer);
	buffer = NULL; //assign null in case insert / print are used again
//	fprintf(stdout, "Buffer freed.\n");
	return 0;
}

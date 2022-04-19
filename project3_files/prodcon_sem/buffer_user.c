#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include "buffer_sem.h"

static bb_buffer_421_t buffer;
struct bb_node_421* head = NULL;
struct bb_node_421* pointer = NULL;
static sem_t mutex;
static sem_t fill_count;
static sem_t empty_count;

//TODO WARNING: Using the status of head to check if buffer is empty may lead to shenanigans

long init_buffer_421(void) {

	//	if buffer already initialized return -1
	if (head != NULL) {
		fprintf(stderr, "Error: Attempting to initalize an already initialized buffer.\n");
		return -1;
	}

	//	fprintf(stdout, "init_buffer_421 called\n");
	//printf("value of uninit buffer data = %d\n", buffer.write->data);

//	buffer = malloc(DATA_LENGTH * SIZE_OF_BUFFER);

	head = malloc(sizeof(struct bb_node_421));
	head->next = head;

	buffer.write = head;
	buffer.read = head;
	buffer.length = 0;

	// 	let insert_buffer_init_421(int i) handle insertion after head is inserted
	for (int i = 1; i < SIZE_OF_BUFFER; i++) {
		pointer = malloc(sizeof(struct bb_node_421));
		pointer->next = buffer.write->next;

		buffer.write->next = pointer;
		buffer.write = buffer.write->next;
		//		print_buffer_421(); //debug print statement
	}

	//	link final node->next to head, completing the circle
	buffer.write->next = head;

	//	after insertion, set write->next to head
	buffer.write = head;

	//	fprintf(stdout, "write is at node %d\n", buffer->write->data);

	// Initialize your semaphores here.
	sem_init(&mutex, 0, 1);
	sem_init(&fill_count, 0, SIZE_OF_BUFFER);
	sem_init(&empty_count, 0, SIZE_OF_BUFFER);
	return 0;
}


long enqueue_buffer_421(char * data) {
	//	if buffer is uninitialized cannot insert, fails
	if (head == NULL) {
		printf("Error: Attempting to enqueue into an uninitialized buffer.\n");
		return -1;
	}
	if (buffer.length == SIZE_OF_BUFFER) {//not sure if this is correct- attempting to implement error upon full buffer
		printf("Error: Attempting to enqueue into a full buffer.\n");
		return -1;
	}

	sem_wait(&fill_count);
	sem_wait(&mutex); //global variables buffer.length, buffer.write protected
	memcpy(buffer.write->data, data, DATA_LENGTH);
	//printf("Data copied: %s\n", buffer.write->data);
	buffer.write = buffer.write->next;
	buffer.length++;
	sem_post(&mutex);
	sem_post(&fill_count);

	return 0;
}

long dequeue_buffer_421(char * data) {
	if (head == NULL) {
		printf("Error: Attempting to dequeue into an uninitialized buffer.\n");
		return -1;
	}
	if (buffer.length == 0) {
		printf("Error: Attempting to dequeue into an empty buffer.\n");
		return -1;
	}

	sem_wait(&empty_count);
	sem_wait(&mutex); //global variables buffer.read, buffer.length protected
	memcpy(data, buffer.read->data, DATA_LENGTH);
	pointer = buffer.read->next;
	strcpy(buffer.read->data, "");
	buffer.read->next = pointer;
	buffer.read = buffer.read->next;
	buffer.length--;
	sem_post(&mutex);
	sem_post(&empty_count);

	return 0;
}


long delete_buffer_421(void) {
	//	if buffer is uninitialized / already deleted, fails.
	if (head == NULL) {
		fprintf(stderr, "Error: Attempting to delete an uninitialized buffer.\n");
		return -1;
	}

	buffer.write = head;

	for (int i = 0; i < SIZE_OF_BUFFER; i++) {
	//	fprintf(stdout, "Attempting to free node [%d, %s]\n", i+1, buffer.write->data);
		pointer = buffer.write->next;
		free(buffer.write);
		buffer.write = pointer;
		buffer.length--;
	}

	sem_destroy(&mutex);
	sem_destroy(&fill_count);
	sem_destroy(&empty_count);
	head = NULL; //assign null in case any functions requiring initialized buffer are used again
	return 0;
}

void print_semaphores(void) {
	// You can call this method to check the status of the semaphores.
	// Don't forget to initialize them first!
	// YOU DO NOT NEED TO IMPLEMENT THIS FOR KERNEL SPACE.
	int value;
	sem_getvalue(&mutex, &value);
	printf("sem_t mutex = %d\n", value);
	sem_getvalue(&fill_count, &value);
	printf("sem_t fill_count = %d\n", value);
	sem_getvalue(&empty_count, &value);
	printf("sem_t empty_count = %d\n", value);
	return;
}

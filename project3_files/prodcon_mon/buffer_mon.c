#include <semaphore.h>
//#include <linux/semaphore.h>
#include "buffer_mon.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ring_buffer_421* buffer;
struct node_421* head = NULL;
struct node_421* pointer = NULL;


int insert_initbuffer_421() { //helper function for init_buffer_421
//	if buffer is uninitialized return -1: this should not be reached
	if (buffer == NULL) {
		fprintf(stderr, "Error: Somehow, buffer is uninitialized during init_buffer_421's helper function.\n");
		return -1;
	}

	pointer = malloc(sizeof(struct node_421));
	pointer->next = buffer->write->next;

	buffer->write->next = pointer;
	buffer->write = buffer->write->next;
	return 0;
}

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
		insert_initbuffer_421();
//		print_buffer_421(); //debug print statement
	}

//	link final node->next to head, completing the circle
	buffer->write->next = head;

//	after insertion, set write->next to head
	buffer->write = head;

//	fprintf(stdout, "write is at node %d\n", buffer->write->data);

	return 0;
}

long enqueue_buffer_421(char* data) {
//	if buffer is uninitialized cannot insert, fails
	if (buffer == NULL) {
		printf("Error: Attempting to enqueue into an uninitialized buffer.\n");
		return -1;
	}
	else if (buffer->length == SIZE_OF_BUFFER) {//not sure if this is correct- attempting to implement error upon full buffer
		printf("Error: Attempting to enqueue into a full buffer.\n");
		return -1;
	}

	strcpy(buffer->write->data, data);
	buffer->write = buffer->write->next;
	buffer->length++;
	return 0;
}

long dequeue_buffer_421(char* data) {
	if(buffer == NULL) {
		printf("Error: Attempting to dequeue into an uninitialized buffer.\n");
		return -1;
	}
	else if (buffer->length == 0) {
		printf("Error: Attempting to dequeue into an empty buffer.\n");
		return -1;
	}
	strcpy(data, buffer->read->data);
	pointer = buffer->read->next;
	strcpy(buffer->read->data, "");
	buffer->read->next = pointer;
	buffer->length--;
	return 0;
}

long print_buffer_421(void) {
	//if buffer is uninitialized cannot print, fails
	if (buffer == NULL) {
		printf("Error: Attempting to print an uninitialized buffer.\n");
		return -1;
	}
	int i = 1;

	fprintf(stdout, "{\n");
	do {
		fprintf(stdout, "\t[%d | %s]\n", i, buffer->read->data);
		buffer->read = buffer->read->next;
		i++;
	} while (buffer->read != head);

	fprintf(stdout, "}\n");

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

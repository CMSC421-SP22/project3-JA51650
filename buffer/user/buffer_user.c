//user implementation of buffer.
//make
//./utest

#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

struct ring_buffer_421* buffer;
struct node_421* head = NULL;
struct node_421* pointer = NULL;


int insert_initbuffer_421(int i) { //helper function for init_buffer_421
//	if buffer is uninitialized return -1: this should not be reached
	if (buffer == NULL) {
		fprintf(stderr, "Error: Somehow, buffer is uninitialized during init_buffer_421's helper function.\n");
		return -1;
	}

	pointer = malloc(sizeof(struct node_421));
	pointer->data = i;
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

	buffer = malloc(sizeof(int) * SIZE_OF_BUFFER);

	head = malloc(sizeof(struct node_421));
	head->next = head;
	head->data = 0;

	buffer->write = head;
	buffer->read = head;
	buffer->length = 0;

// 	let insert_buffer_init_421(int i) handle insertion after head is inserted
	for (int i = 1; i < SIZE_OF_BUFFER; i++) {
		insert_initbuffer_421(0);
//		print_buffer_421(); //debug print statement
	}

//	link final node->next to head, completing the circle
	buffer->write->next = head;

//	after insertion, set write->next to head
	buffer->write = head;

//	fprintf(stdout, "write is at node %d\n", buffer->write->data);

	return 0;
}

long insert_buffer_421(int i) {
//	if buffer is uninitialized cannot insert, fails
	if (buffer == NULL) {
		fprintf(stderr, "Error: Attempting to insert into an uninitialized buffer.\n");
		return -1;
	}
	if (buffer->length == SIZE_OF_BUFFER) {
		fprintf(stderr, "Error: Attempting to insert into full buffer\n");
		return -1;
	}

	buffer->write->data = i;
	buffer->write = buffer->write->next;
	buffer->length++;
	return 0;
}

long print_buffer_421(void) {
	//if buffer is uninitialized cannot print, fails
	if (buffer == NULL) {
		fprintf(stderr, "Error: Attempting to print an uninitialized buffer.\n");
		return -1;
	}
	int i = 1;

	fprintf(stdout, "{\n");
	do {
		fprintf(stdout, "\t[%d | %d]\n", i, buffer->read->data);
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

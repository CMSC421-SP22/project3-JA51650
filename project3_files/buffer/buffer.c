#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

struct ring_buffer_421* buffer;
struct node_421* head = NULL;
struct node_421* pointer = NULL;


long insert_initbuffer_421(int i) { //helper function for init_buffer_421
	//if buffer is empty, insert fails. return 0
	if(buffer == NULL) return -1;

	pointer = malloc(sizeof(struct node_421));
	pointer->data = i;
	pointer->next = buffer->write->next;

	buffer->write = pointer;
	return 0;
}

long init_buffer_421(void) { 
//	fprintf(stdout, "init_buffer_421 called\n");

//	buffer already initialized return -1
	if (buffer != NULL) return -1;

//	fprintf(stdout, "mallocing buffer\n");
	head = malloc(sizeof(struct node_421));
	head->next = head;
	head->data = 0;

	buffer = malloc(sizeof(int) * SIZE_OF_BUFFER);
	buffer->length = 0;
	buffer->write = head;
	buffer->read = head;

// 	let insert_buffer_init_421(int i) handle insertion after head is inserted for every node except the last one
//	fprintf(stdout, "for loop\n");
	for (int i = 1; i < buffer->length-1; i++) {
		insert_initbuffer_421(i);
	}
//	last node needs to be linked to head and thus is handled separately
	pointer = malloc(sizeof(struct node_421));
	pointer->data = 19;
	pointer->next = head;
	buffer->write->next = pointer;
//	after insertion, set write->next to head
	buffer->write = head;

	fprintf(stdout, "write is at node %d\n", buffer->write->data);

	return 0;
}

long insert_buffer_421(int i) {
	if (buffer == NULL) return -1;

	/*buffer->write->data = i;
	buffer->write = buffer->write->next;
	buffer->length++;*/
	return 0;
}

long print_buffer_421(void) {
	//if buffer is empty cannot print, fails
	if (buffer == NULL) return -1;

	do {
		fprintf(stdout, "[%d]\n", buffer->read->data);
		buffer->read = buffer->read->next;
	} while (buffer->read != head);

	fprintf(stdout, "\n");

	return 0;
}

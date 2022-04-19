#include <linux/kernel.h>
#include <linux/syscalls.h>
#include "buffer.h"

struct ring_buffer_421* buffer;
struct node_421* head = NULL;
struct node_421* pointer = NULL;

SYSCALL_DEFINE0(init_buffer_421) {
	int i = 1;

//	if buffer already initialized return -1
	if (buffer != NULL) {
		printk("Error: Attempting to initalize an already initialized buffer.\n");
		return -1;
	}

//	fprintf(stdout, "init_buffer_421 called\n");

	buffer = kmalloc(sizeof(int) * SIZE_OF_BUFFER, GFP_KERNEL);

	head = kmalloc(sizeof(struct node_421), GFP_KERNEL);
	head->next = head;
	head->data = 0;

	buffer->write = head;
	buffer->read = head;
	buffer->length = 0;

// 	let insert_buffer_init_421(int i) handle insertion after head is inserted
	while(i < SIZE_OF_BUFFER) {
		pointer = kmalloc(sizeof(struct node_421), GFP_KERNEL);
		pointer->data = 0;
		pointer->next = buffer->write->next;

		buffer->write->next = pointer;
		buffer->write = buffer->write->next;
//		print_buffer_421(); //debug print statement
		i++;
	}

//	link final node->next to head, completing the circle
	buffer->write->next = head;

//	after insertion, set write->next to head
	buffer->write = head;

//	fprintf(stdout, "write is at node %d\n", buffer->write->data);

	return 0;
}

SYSCALL_DEFINE1(insert_buffer_421, int, i) {
//	if buffer is uninitialized cannot insert, fails
	if (buffer == NULL) {
		printk("Error: Attempting to insert into an uninitialized buffer.\n");
		return -1;
	}

	buffer->write->data = i;
	buffer->write = buffer->write->next;
	buffer->length++;
	return 0;
}

SYSCALL_DEFINE0(print_buffer_421) {
	int i = 1;
	//if buffer is uninitialized cannot print, fails
	if (buffer == NULL) {
		printk("Error: Attempting to print an uninitialized buffer.\n");
		return -1;
	}

	printk("{\n");
	do {
		printk("\t[%d | %d]\n", i, buffer->read->data);
		buffer->read = buffer->read->next;
		i++;
	} while (buffer->read != head);

	printk("}\n");

	return 0;
}

SYSCALL_DEFINE0(delete_buffer_421) {
	int i = 0;

//	if buffer is uninitialized / already deleted, fails.
	if (buffer == NULL) {
		printk("Error: Attempting to delete an uninitialized buffer.\n");
		return -1;
	}

	buffer->write = head;

	while (i < SIZE_OF_BUFFER) {
	//while (buffer->write->next != NULL && i < SIZE_OF_BUFFER) {
//		fprintf(stdout, "Attempting to free node [%d, %d]\n", i+1, buffer->write->data);
		pointer = buffer->write->next;
		kfree(buffer->write);
		buffer->write = pointer;
		buffer->length--;
		i++;
	}

//	fprintf(stdout, "All nodes freed. Freeing buffer...\n");
	kfree(buffer);
	buffer = NULL; //assign null in case insert / print are used again
//	fprintf(stdout, "Buffer freed.\n");
	return 0;
}

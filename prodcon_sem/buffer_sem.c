//kernel space implementation

#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/semaphore.h>
#include "buffer_sem.h"

static bb_buffer_421_t buffer;
struct bb_node_421* shead = NULL;
struct bb_node_421* spointer = NULL;
struct semaphore mutex;
struct semaphore fill_count;
struct semaphore empty_count;

//TODO WARNING: Using the status of head to check if buffer is empty may lead to shenanigans

SYSCALL_DEFINE0(init_buffer_sem_421) {
	int i = 1;

	//	if buffer already initialized return -1
	if (shead != NULL) {
		printk("Error: Attempting to initalize an already initialized buffer.\n");
		return -1;
	}
	shead = kmalloc(sizeof(struct bb_node_421), GFP_KERNEL);
	shead->next = shead;

	buffer.write = shead;
	buffer.read = shead;
	buffer.length = 0;

	// 	let insert_buffer_init_421(int i) handle insertion after head is inserted
	while (i < SIZE_OF_BUFFER) {
		spointer = kmalloc(sizeof(struct bb_node_421), GFP_KERNEL);
		spointer->next = buffer.write->next;

		buffer.write->next = spointer;
		buffer.write = buffer.write->next;
		i++;
	}

	//	link final node->next to head, completing the circle
	buffer.write->next = shead;

	//	after insertion, set write->next to head
	buffer.write = shead;

	// Initialize your semaphores here.
	sema_init(&mutex, 1);
	sema_init(&fill_count, SIZE_OF_BUFFER);
	sema_init(&empty_count, SIZE_OF_BUFFER);
	return 0;
}


SYSCALL_DEFINE1(enqueue_buffer_sem_421, char *, data) {
	int copy;
	//	if buffer is uninitialized cannot insert, fails
	if (shead == NULL) {
		printk("Error: Attempting to enqueue into an uninitialized buffer.\n");
		return -1;
	}

	down(&fill_count);
	down(&mutex); //global variables buffer.length, buffer.write protected

	copy = __copy_from_user(buffer.write->data, data, DATA_LENGTH);
	buffer.write = buffer.write->next;
	buffer.length++;

	up(&mutex);
	up(&fill_count);

	return 0;
}

SYSCALL_DEFINE1(dequeue_buffer_sem_421,char *, data) {
	int copy;
	if (shead == NULL) {
		printk("Error: Attempting to dequeue into an uninitialized buffer.\n");
		return -1;
	}

	down(&empty_count);
	down(&mutex); //global variables buffer.read, buffer.length protected

	copy = __copy_to_user(data, buffer.read->data, DATA_LENGTH);
	spointer = buffer.read->next;
	copy = __copy_from_user(buffer.read->data, "", DATA_LENGTH);
	buffer.read->next = spointer;
	buffer.read = buffer.read->next;
	buffer.length--;

	up(&mutex);
	up(&empty_count);

	return 0;
}


SYSCALL_DEFINE0(delete_buffer_sem_421) {
	int i = 0;

	//	if buffer is uninitialized / already deleted, fails.
	if (shead == NULL) {
		printk("Error: Attempting to delete an uninitialized buffer.\n");
		return -1;
	}

	buffer.write = shead;

	while (i < SIZE_OF_BUFFER) {
		spointer = buffer.write->next;
		kfree(buffer.write);
		buffer.write = spointer;
		buffer.length--;
		i++;
	}

//	no kernel equivalent to sem_destroy
//	sem_destroy(&mutex);
//	sem_destroy(&fill_count);
//	sem_destroy(&empty_count);
	shead = NULL; //assign null in case any functions requiring initialized buffer are used again
	return 0;
}

void print_semaphores(void) {
	// You can call this method to check the status of the semaphores.
	// Don't forget to initialize them first!
	// YOU DO NOT NEED TO IMPLEMENT THIS FOR KERNEL SPACE.
/*	int value;
	sem_getvalue(&mutex, &value);
	printk("sem_t mutex = %d\n", value);
	sem_getvalue(&fill_count, &value);
	printk("sem_t fill_count = %d\n", value);
	sem_getvalue(&empty_count, &value);
	printk("sem_t empty_count = %d\n", value);*/
	return;
}

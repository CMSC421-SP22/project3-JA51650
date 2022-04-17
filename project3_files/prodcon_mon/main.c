#include "buffer_mon.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	init_buffer_421();
	print_buffer_421();
	enqueue_buffer_421("Hello!");
	char* hello = malloc(1024);
	dequeue_buffer_421(hello);
	printf("%s", hello);
	free(hello);
	delete_buffer_421();
	return 0;
}

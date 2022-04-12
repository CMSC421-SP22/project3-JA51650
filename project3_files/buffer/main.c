#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"
int main() {
	fprintf(stdout, "Test start\n");
	init_buffer_421();
	print_buffer_421();
	insert_buffer_421(21);
	print_buffer_421();
	insert_buffer_421(21);
	print_buffer_421();
	return 0;
}

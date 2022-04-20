#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"
int main() {
	fprintf(stdout, "==TEST START==\n");

	fprintf(stdout, "\n==ERROR TEST==\n");
	insert_buffer_421(10);
	print_buffer_421();
	delete_buffer_421();
	init_buffer_421();
	init_buffer_421();

	for (int i = 1; i < 40; i++){
		insert_buffer_421(i);
	}
	delete_buffer_421();

	fprintf(stdout, "==END OF ERROR TEST==\n\n==NORMAL TEST==\n");
	init_buffer_421();
	print_buffer_421();
	delete_buffer_421();

	init_buffer_421();
	for (int i = 1; i < 21; i++){
		insert_buffer_421(i);
	}
	print_buffer_421();

	delete_buffer_421();

	fprintf(stdout, "==END OF NORMAL TEST==\n");
	fprintf(stdout, "\n==TEST END==\n");

	return 0;
}

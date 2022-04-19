#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define __NR_hello 441
long hello_syscall(void){
	return syscall(__NR_hello);
}

#define __NR_init_buffer_421 442
long init_buffer_421_syscall(void){
	return syscall(__NR_init_buffer_421);
}

#define __NR_insert_buffer_421 443
long insert_buffer_421_syscall(int i){
	return syscall(__NR_insert_buffer_421, i);
}

#define __NR_print_buffer_421 444
long print_buffer_421_syscall(void){
	return syscall(__NR_print_buffer_421);
}

#define __NR_delete_buffer_421 445
long delete_buffer_421_syscall(void) {
	return syscall(__NR_delete_buffer_421);
}

void printMenu() {
	printf("0\t\tExit\n1\t\tInitialize\n2\t\tInsert\n3\t\tPrint\n4\t\tDelete\n");
	return;
}

int main (int argc, char *argv[]) {
	long rv;
	char input;
	long ins;
	long random;
	srand(time(0));
	do {
		printMenu();
		printf("Enter a number: ");
		input = getchar();
		getchar(); //consumes \n

		if (input == '1') {
			rv = init_buffer_421_syscall();
		}
		else if (input == '2') { //input implentations fail so I'm just generating a random number
			random = rand()%1001;
			rv = insert_buffer_421_syscall(random);
			if(rv != -1) printf("Inserted random integer %d\n", random);
		}
		else if (input == '3') {
			rv = print_buffer_421_syscall();
		}
		else if (input == '4') {
			rv = delete_buffer_421_syscall();
		}
		else if (input != '0'){
			printf("Invalid input: %c\n", input);
			rv = -2;
		}
		else {
			printf("Exiting...\n");
			rv = -2;
		}
		if (rv == -1) {
			perror("Syscall failed (sudo dmesg for details)");
		}
		else if (rv == 0) {
			if(input == '3')
				printf("Syscall ran successfully (sudo dmesg for details)\n");
			else
				printf("Syscall ran successfully\n");
		}
	} while (input != '0');


	return 0;
}

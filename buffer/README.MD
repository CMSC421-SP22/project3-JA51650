Kernel implementation in buffer/
User implementation in buffer/user/

Implementation for the buffer started with the implementation of init_buffer_421, then print_buffer_421. These were fairly simple to implement- coding a singly-linked list and making the tail's next node point to the head node. Originally, I had a helper function to initialize all nodes within the circular buffer, but out of fear of incompatibility with Kernel code I opted to merge it into the main init function.
After init_buffer_421 was implemented, print_buffer_421 had a fairly trivial implementation and was done first so that debugging insert would be easier.
Insert_buffer_421 provided the majority of the challenge, but help from TAs allowed me to finish it without too much of an issue.
Afterwards, delete_buffer_421 could be implemented. I used valgrind to ensure that no leaks occured. Around this time, I switched from strcpy to memcpy.

Kernel implementation was significantly harder than user implementation. Kernel implementation required me to change fprintf to printk, free to kfree, and malloc to kmalloc. Malloc in particular was hard because I wasn't certain what the second argument should be before reconsulting the project documentation. Furthermore, I required help in compiling the kernel. Help from TAs allowed me to eventually compile the kernel without errors.

All references are listed in the main README.MD.



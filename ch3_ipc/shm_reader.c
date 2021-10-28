#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main(){

	const int SIZE = 4096; 
	const char* name = "OS"; 

	// shared memory file descriptor 
	int shm_fd; 

	// pointer to shared memory object 
	void* ptr; 

	// create the shared memory object 
	shm_fd = shm_open(name, O_RDONLY, 0666); 

	// memory map the shared memory object 
	ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0); 

	// read from the shared memory object to the shared memory object 
	printf("%s\n", (char*)ptr); 

	// sleep(10); 
	shm_unlink(name); // shm_unlink will remove the memory object created by shm_open(), 
						// no matter how many other processes may access to it

	return 0; 
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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


	pid_t pid = fork(); 

	if(pid < 0){
		printf("fork failed\n"); 
		exit(-1); 
	}else if(pid == 0){
		// child process
		printf("child process read %s !\n", (char*)ptr); 
	}else{
		// usleep(1000); // 1000 microseconds, 1 milliseconds  
		sleep(5);
		// parent process 
		printf("parent process read %s !\n", (char*)ptr);
		wait(NULL); // pid 
		shm_unlink(name);
	}

	return 0; 
}


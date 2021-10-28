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

	const char* message_0 = " Hello "; 

	const char* message_1 = " World "; 


	// shared memory file descriptor 
	int shm_fd; 

	// pointer to shared memory object 
	void* ptr;
	void* ptr_backup;  

	// create the shared memory object 
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); 

	// configure the size of the shared memory object 
	ftruncate(shm_fd, SIZE); 

	// memory map the shared memory object 
	ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0); 
	ptr_backup = ptr; 

	// write to the shared memory object 
	sprintf(ptr, "%s ", message_0); 
	ptr += strlen(message_0); 
	sprintf(ptr, "%s ", message_1); 
	ptr += strlen(message_1); 

	printf("after writing to shared memory, gonna to sleep 5 seconds!\n");
	sleep(5);

	printf("try to write data one more time\n"); 
	// ptr = ptr_backup; 
	sprintf(ptr, "%s ", message_1); 
	ptr += strlen(message_1); 
	sprintf(ptr, "%s ", message_0); 

	ptr += strlen(message_0); 

	printf("second time, sleep 5 seconds\n"); 
	sleep(5);



	return 0; 
}


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

// ./fork_zombie&
// ps -ef | grep zom


int main(int argc, char* argv[])
{
	pid_t pid; 
	int status; 
	pid = fork(); // A + B 

	if(pid < 0){
		printf("fork failed\n"); 
		exit(-1); 
	}else if(pid == 0){
		exit(0); 
	}else{
		printf("parent process!\n"); 
		// wait(NULL); 
		sleep(10); 
	}
	return 0; 
}

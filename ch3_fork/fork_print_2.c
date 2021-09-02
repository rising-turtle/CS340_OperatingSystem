#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

// create process tree structure like
//   A 
//  | \ 
// B   C
//  \
//   D

int main(int argc, char* argv[])
{
	// process A 
	pid_t pid; 

	pid = fork(); // A and B
	printf("Hello %d\n", pid);

	fork(); 
	printf("World %d\n", pid); 

	sleep(1);

	return 0; 
}
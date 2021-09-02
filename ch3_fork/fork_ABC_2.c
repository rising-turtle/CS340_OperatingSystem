#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

// create process tree structure like
// 		A 
// 	   / \
//    B  C


int main(int argc, char* argv[])
{
	// process A 
	pid_t pid; 

	pid = fork(); // A and B
	if(pid == 0){
		// B process
		printf("I am process B my pid is %d, my parent pid is %d!\n", getpid(), getppid());

	}else{
		// A
		printf("I am process A: pid of my child is %d, my pid is %d\n", pid, getpid());
		pid = fork(); // A and C 
		if(pid == 0){
			// C process 
			printf("I am process C my pid is %d, my parent pid is %d\n", getpid(), getppid());
		}else{
			// A
			printf("I am process A: pid of my child is %d, my pid is %d\n", pid, getpid());
			wait(NULL);
			wait(NULL);
			printf("child B and C are done! I can exit\n"); 
		}
	}
	return 0; 
}
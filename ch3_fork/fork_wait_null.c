#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

// wait(NULL) waits for any of its child process to terminate not any process 
// create process tree structure like
// A 
// |
// B
// |
// C 

int main(int argc, char* argv[])
{
	// process A 
	pid_t pid; 

	pid = fork(); // A and B
	if(pid == 0){
    sleep(1); // so A is ahead of B  
    
		// B process
		printf("I am process B my pid is %d, my parent pid is %d!\n", getpid(), getppid());

		pid = fork(); // B and C 
		if(pid == 0){
			// C process 
			printf("I am process C my pid is %d, my parent pid is %d\n", getpid(), getppid());
		}else{
			// B process
      sleep(2); // So when C exits, will it wake process A from wait?  
			wait(NULL);
			printf("child C is done! I can exit\n"); 
		}

	}else{
		// A
		printf("I am process A: pid of my child is %d, my pid is %d\n", pid, getpid());
		wait(NULL); 
		printf("child B is done! I can exit\n"); 
	}
   printf("process: %d exits\n", getpid());
	return 0; 
}
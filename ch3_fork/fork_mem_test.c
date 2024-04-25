#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <memory.h>

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

	unsigned int S = 1024*1024*800; 

	char* pTmp = (char*)malloc(S); 

	memset(pTmp, 0, S); 

	sleep(30);

	pid = fork(); // A and B
	if(pid == 0){
		// B process
		printf("I am process B my pid is %d, my parent pid is %d!\n", getpid(), getppid());
		memset(pTmp, 1, S); 
		sleep(60); 
	}else{
		// A
		printf("I am process A: pid of my child is %d, my pid is %d\n", pid, getpid());
		wait(NULL); 
		printf("child B is done! I can exit\n"); 
	}
	return 0; 
}
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
	pid_t pid; 
	printf("before fork\n"); 

	pid = fork(); 
	printf("after fork\n");

	if(pid < 0){
		printf("fork failed\n"); 
		exit(-1); 
	}else if(pid == 0){
		// child process
		printf("child process!\n"); 
		printf("child pid is %d my parent pid is %d\n", getpid(), getppid()); 
	}else{
		// usleep(1000); // 1000 microseconds, 1 milliseconds  
		// parent process 
		printf("parent process: pid of my child is %d, my pid is %d\n", pid, getpid());
		wait(NULL); 
		printf("child is done! I can exit\n"); 
	}
	return 0; 
}
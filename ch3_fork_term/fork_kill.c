#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
	pid_t pid; 
	pid = fork(); 

	if(pid < 0){
		printf("fork failed\n"); 
		exit(-1); 
	}else if(pid == 0){
		// child process
		printf("child process!\n"); 
		printf("child pid is %d my parent pid is %d\n", getpid(), getppid()); 
		sleep(5);
		printf("child Quitting \n"); 
		exit(0); 
		printf("should never print me!\n"); 
	}else{
		printf("parent process!\n"); 
		usleep(1000); 
		printf("parent kill process %d\n", pid);
		if(kill(pid, SIGKILL) == 0) {
			printf("succeed to kill\n"); 
		} 
		wait(NULL); 
		printf("child is gone! I can exit\n"); 
	}
	return 0; 
}
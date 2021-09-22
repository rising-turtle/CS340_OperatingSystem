
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


void* runner(void * param) // thread function 
{
	printf("I am thread %.16lx\n", pthread_self()); 
	
	char* argv[2]; 
	argv[0] = "/bin/ps"; 
	argv[1] = NULL;  

	// pid_t pid = fork();
	// if(pid == 0)
	
	execv(argv[0], argv); 

	pthread_exit(0); 

}

int main(int argc, char* argv[]){

	pthread_t tid; // thread id 
	pthread_attr_t attr; // thread attributions 

	pthread_attr_init(&attr); // set default attribution of the thread 

	pthread_create(&tid, &attr, runner, NULL); // create thread to run the code 

	// sleep(1); 

	printf("Hello world!\n");
	
	pthread_join(tid, NULL); // wait for the thread to exit 
	
	printf("Hello world!\n");

	return 0; 

}



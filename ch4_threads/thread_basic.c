#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int sum;  // shared between threads 

void* runner(void * param) // thread function 
{
	sum = 0; 

	int upper = atoi((char*)param); 
	for(int i=0; i<upper; i++){
		sum += i; 
	}
	pthread_exit(0); 

}

int main(int argc, char* argv[]){

	if(argc < 2){

		printf("usage: ./thread_basic + [number]\n"); 
		return -1; 

	}
	pthread_t tid; // thread id 
	pthread_attr_t attr; // thread attributions 

	pthread_attr_init(&attr); // set default attribution of the thread 
	pthread_create(&tid, &attr, runner, argv[1]); // create thread to run the code 
	// pthread_create(&tid, NULL, runner, argv[1]); // create thread to run the code 

	pthread_join(tid, NULL); // wait for the thread to exit 

	printf("sum = %d\n", sum); 

	return 0; 

}



#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_TICK_SELLER 3
int n_ticket = 100;  // shared between threads 
int n_actual_ticket = 0;

void* seller(void* param) // thread function 
{
	bool quit = false;
	while(!quit){
		if(n_ticket > 0){
			printf("I am thread %.16lx and I am selling the ticket number %d\n", 
				pthread_self(), n_ticket); 
			usleep(5000); 
			n_ticket--;
			n_actual_ticket++;
		}else{
			quit = true;
		}

	}
	pthread_exit(0); 

}

int main(int argc, char* argv[]){

	pthread_t tid[NUM_TICK_SELLER]; // thread id 
	for(int i=0; i<NUM_TICK_SELLER; i++){
		pthread_create(&tid[i], NULL, seller, NULL); 
	}

	for(int i=0; i<NUM_TICK_SELLER; i++){
		pthread_join(tid[i], NULL); // wait for the thread to exit 
	}

	printf("Main: Actually %d tickets have been sold \n", n_actual_ticket); 

	return 0; 

}



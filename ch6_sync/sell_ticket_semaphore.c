#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>

#define NUM_TICK_SELLER 3
int n_ticket = 100;  // shared between threads 
int n_actual_ticket = 0;

sem_t mutex_ticket;

void* seller(void* param) // thread function 
{
	bool quit = false; 
	while(!quit){
		sem_wait(&mutex_ticket); 
		if(n_ticket > 0){
			printf("I am thread %.16lx and I am selling the ticket number %d\n", 
				pthread_self(), n_ticket); 
			usleep(5000); 
			n_ticket--;
			n_actual_ticket++;
		}else{
			quit = true;
		}
		sem_post(&mutex_ticket);
	}
	pthread_exit(0); 

}

int main(int argc, char* argv[]){

	// initialize semaphore 
	/*
		sem_init(*mutex, pshared, ini_value)
       If pshared has the value 0, then the semaphore is shared between
       the threads of a process, and should be located at some address
       that is visible to all threads (e.g., a global variable, or a
       variable allocated dynamically on the heap).

       If pshared is nonzero, then the semaphore is shared between
       processes, and should be located in a region of shared memory
       (see shm_open(3), mmap(2), and shmget(2)).  (Since a child
       created by fork(2) inherits its parents memory mappings, it can
       also access the semaphore.)  Any process that can access the
       shared memory region can operate on the semaphore using
       sem_post(3), sem_wait(3), and so on.*/
	
	sem_init(&mutex_ticket, 0, 1); 

	pthread_t tid[NUM_TICK_SELLER]; // thread id 
	for(int i=0; i<NUM_TICK_SELLER; i++){
		pthread_create(&tid[i], NULL, seller, NULL); 
	}

	for(int i=0; i<NUM_TICK_SELLER; i++){
		pthread_join(tid[i], NULL); // wait for the thread to exit 
	}
	sem_destroy(&mutex_ticket);
	printf("Main: Actually %d tickets have been sold \n", n_actual_ticket); 

	return 0; 

}



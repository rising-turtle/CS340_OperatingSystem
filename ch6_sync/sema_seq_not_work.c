#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>


// control thread sequence B,C -> A 

sem_t semaphore;

void* func1(void* param){

	for(int i=0; i<3; i++){
		printf("I am thread B, I am sleeping %d seconds\n", i+1);
		sleep(1); 
	}
	printf("Thread B exit \n");
	sem_post(&semaphore);  
	pthread_exit(0);
}

void* func2(void* param){

	for(int i=0; i<5; i++){
		printf("I am thread C, I am sleeping %d seconds\n", i+1);
		sleep(1); 
	}
	printf("Thread C exit\n");
	sem_post(&semaphore);
	pthread_exit(0);
}

int main(int argc, char* argv[]){

	// initialize semaphore 
	/*sem_init(*mutex, pshared, ini_value)*/
	
	sem_init(&semaphore, 0, -20);

	pthread_t tid1, tid2;  
	pthread_create(&tid1, NULL, func1, NULL); // thread B
	pthread_create(&tid2, NULL, func2, NULL); // thread C

	// pthread_join(&tid1); 
	// pthread_join(&tid2); 
	// B, C -> A 
	sem_wait(&semaphore); 
	// sem_wait(&semaphore);
	sem_destroy(&semaphore);
	printf("Thread A exit \n"); 

	return 0; 

}



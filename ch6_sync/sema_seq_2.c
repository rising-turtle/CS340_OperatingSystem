#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>

sem_t semaphore_1;
sem_t semaphore_2; 

// control thread sequence C -> B -> A (main)

// Thread B 
void* func1(void* param){

	sem_wait(&semaphore_2);
	for(int i=0; i<3; i++){
		printf("I am thread B, I am sleeping %d seconds\n", i+1);
		sleep(1); 
	}
	printf("Thread B exit \n");
	sem_post(&semaphore_1);  
	pthread_exit(0);
}

// Thread C
void* func2(void* param){

	for(int i=0; i<5; i++){
		printf("I am thread C, I am sleeping %d seconds\n", i+1);
		sleep(1); 
	}
	printf("Thread C exit\n");
	sem_post(&semaphore_2);
	pthread_exit(0);
}

int main(int argc, char* argv[]){

	// initialize semaphore 
	/*sem_init(*mutex, pshared, ini_value)*/
	
	sem_init(&semaphore_1, 0, 0);
	sem_init(&semaphore_2, 0, 0); 

	pthread_t tid1, tid2;  
	pthread_create(&tid1, NULL, func1, NULL); // thread B 
	pthread_create(&tid2, NULL, func2, NULL); // thread C

	// pthread_join(&tid1); 
	// pthread_join(&tid2); 
	sem_wait(&semaphore_1); 
	sem_destroy(&semaphore_1);
	sem_destroy(&semaphore_2);
	printf("Thread A exit \n"); 

	return 0; 

}



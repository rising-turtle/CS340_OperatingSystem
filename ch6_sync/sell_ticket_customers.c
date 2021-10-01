#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>

#define NUM_TICK_SELLER 3 // Number of seller threads 
#define NUM_SEATS 4	// Number of waiting seats 
#define NUM_CUSTOMERS 10 // Number of customers to buy tickets 
#define MAX_SLEEP_SECONDS 2 // Maximum walking (sleeping) seconds 

sem_t waiting_customers;
sem_t ready_sellers;  

pthread_mutex_t ticket_lock; 
pthread_mutex_t seat_lock; 

bool quit = false; 
int n_empty_seats = NUM_SEATS ;
int n_ticket = 100;  // shared between threads 

void random_walk(); // randomly sleep several seconds 

void* seller(void* param) // thread function 
{
	while(!quit){

		// wait here if there is no customer is waiting 
		sem_wait(&waiting_customers); 
		
		// serve a waiting customer and release the seat 
		pthread_mutex_lock(&seat_lock); 
		if(n_empty_seats < NUM_SEATS){
			++n_empty_seats; // release a customer from seat
			sem_post(&ready_sellers); // I am ready to serve 
		}
		pthread_mutex_unlock(&seat_lock); 

		// check ticket 
		pthread_mutex_lock(&ticket_lock); 
		if(n_ticket == 0){
			printf("Ticket has been sold out, need to stop\n"); 
			quit = true; 
		}
		
		pthread_mutex_unlock(&ticket_lock);
	}
	pthread_exit(0); 

}

void* buy_ticket(void* param)
{
	int customer_id = *((int*)(param)); 

	while(!quit){
		// walk out for random time and then go to purchase a ticket 
		random_walk(); 

		// check the seat 
		pthread_mutex_lock(&seat_lock); 
		if(n_empty_seats-- > 0){	// if there is some empty seats 
			sem_post(&waiting_customers); // take the seat and wait 
			pthread_mutex_unlock(&seat_lock); // release the lock to seat 

			// wait for a seller to purchase a ticket 
			sem_wait(&ready_sellers); // wait here if no seller is available 

			// now a seller is available, move forward to purchase a ticket 
			pthread_mutex_lock(&ticket_lock); // access ticket 
			if(n_ticket > 0){
				printf("I am customer %d, I am buying ticket %d\n", customer_id, n_ticket--); 
			}else{
				quit = true;
			}
			pthread_mutex_unlock(&ticket_lock); // release lock 
		}else{
			printf("I am customer %d, there is no empty seats, I am walking out for some time\n", customer_id); 
			pthread_mutex_unlock(&seat_lock); // release the lock to seat 
		}
	}
	pthread_exit(0); 
}


int main(int argc, char* argv[]){

	// initialize semaphore 	
	sem_init(&waiting_customers, 0, 0); 
	sem_init(&ready_sellers, 0, 0); 

	// initialize lock 
	pthread_mutex_init(&ticket_lock, NULL);
	pthread_mutex_init(&seat_lock, NULL);  

	pthread_t seller_tid[NUM_TICK_SELLER]; // thread id 
	for(int i=0; i<NUM_TICK_SELLER; i++){
		pthread_create(&seller_tid[i], NULL, seller, NULL); 
	}

	pthread_t customer_tid[NUM_CUSTOMERS]; 
	for(int i=0; i<NUM_CUSTOMERS; i++){
		pthread_create(&customer_tid[i], NULL, buy_ticket, &i); 
	}

	for(int i=0; i<NUM_TICK_SELLER; i++){
		pthread_join(seller_tid[i], NULL); // wait for the thread to exit 
	}
	for(int i=0; i<NUM_CUSTOMERS; i++){
		pthread_join(customer_tid[i], NULL); 
	}
	
	printf("Main: quit! \n"); 

	return 0; 

}



void random_walk() // randomly sleep several seconds 
{	
	srand(time(NULL)); 
	int ran_v = rand()%MAX_SLEEP_SECONDS + 1;
	sleep(ran_v); 
}
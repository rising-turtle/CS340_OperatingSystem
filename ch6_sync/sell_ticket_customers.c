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
#define NUM_CUSTOMERS 20 // Number of customers to buy tickets 
#define MAX_SLEEP_MILLI_SECONDS 2000 // Maximum walking (sleeping) milliseconds 
#define MAX_REST_MILLI_SECONDS 500 // Maximum resting milliseconds 

sem_t waiting_customers;
sem_t ready_sellers;  

pthread_mutex_t ticket_lock; 
pthread_mutex_t seat_lock; 

bool quit = false; 
int n_empty_seats = NUM_SEATS ;
int n_ticket = 100;  // shared between threads 

void random_walk(); // randomly sleep several milliseconds 
void random_rest(); // randomly rest several milliseconds 

void* seller(void* param) // thread function 
{
	while(1){

		// wait here if there is no waiting customer 
		sem_wait(&waiting_customers); 

		// serve a waiting customer and release the seat 
		pthread_mutex_lock(&seat_lock); 
			++n_empty_seats; // release a customer from seat
			sem_post(&ready_sellers); // I am ready to serve 
		pthread_mutex_unlock(&seat_lock); 

		// take some rest
		random_rest(); 

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
		
		if(!quit && n_empty_seats > 0){	// if there is some empty seats 
			printf("there are %d empty seats. I'm customer %d, and I'll take a seat and wait for a seller\n", n_empty_seats, customer_id);
			n_empty_seats--; // take a seat 
			sem_post(&waiting_customers); // singal sellers with a new waiting customer  
			pthread_mutex_unlock(&seat_lock); // release the lock to seat 
			
			// wait for a seller to purchase a ticket 
			sem_wait(&ready_sellers); // wait here if no seller is ready 

			// now a seller is ready, move forward to purchase a ticket 
			pthread_mutex_lock(&ticket_lock); // access ticket 
			if(n_ticket > 0){
				printf("I am customer %d, I am buying ticket %d\n", customer_id, n_ticket--); 
			}else{
				quit = true;
				printf("Tickets have been sold out, no need to wait, customer %d quit\n", customer_id);
			}
			pthread_mutex_unlock(&ticket_lock); // release lock 
		}else{
			if(quit){
				printf("Tickets have been sold out, no need to wait, customer %d quit\n", customer_id);
			}else{
				printf("I am customer %d, there is no empty seats, I am walking out for some time\n", customer_id); 
			}
			pthread_mutex_unlock(&seat_lock); // release the lock to seat 
		}
	}
	printf("Customer %d quit\n", customer_id);
	pthread_exit(0); 
}


int main(int argc, char* argv[]){

	srand(time(NULL));

	// initialize semaphore 	
	sem_init(&waiting_customers, 0, 0); 
	sem_init(&ready_sellers, 0, 0); 

	// initialize lock 
	pthread_mutex_init(&ticket_lock, NULL);
	pthread_mutex_init(&seat_lock, NULL);  

	// create sellers 
	pthread_t seller_tid[NUM_TICK_SELLER]; // thread id 
	for(int i=0; i<NUM_TICK_SELLER; i++){
		pthread_create(&seller_tid[i], NULL, seller, NULL); 
	}

	// create customers 
	pthread_t customer_tid[NUM_CUSTOMERS]; 
	int customer_id[NUM_CUSTOMERS]; 
	for(int i=0; i<NUM_CUSTOMERS; i++){
		customer_id[i] = i+1;
		pthread_create(&customer_tid[i], NULL, buy_ticket, &customer_id[i]); 
	}

	// wait for customers 
	for(int i=0; i<NUM_CUSTOMERS; i++){
		pthread_join(customer_tid[i], NULL); 
	}

	// cancel the sellers
	for(int i=0; i<NUM_TICK_SELLER; i++){
		pthread_cancel(seller_tid[i]);
	}

	
	printf("Main: quit! \n"); 

	return 0; 

}


void random_walk() // randomly sleep several milliseconds 
{	
	int ran_v = rand()%MAX_SLEEP_MILLI_SECONDS + 1;
	usleep(ran_v*1000); 
}


void random_rest() // randomly rest several milliseconds 
{	
	int ran_v = rand()%MAX_REST_MILLI_SECONDS + 1;
	usleep(ran_v*1000); 
}
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_TICK_SELLER 3
static const int TOTAL_TICKET = 1000000;
int n_ticket = TOTAL_TICKET;  // shared between threads 

void* seller(void* param) // thread function 
{
  int* sold_ticket = (int*)(param); 
  while(n_ticket > 0){
    n_ticket--;
    ++(*sold_ticket);
  }
	pthread_exit(0); 

}

int main(int argc, char* argv[]){

	pthread_t tid[NUM_TICK_SELLER]; // thread id 
  int actual_tickets[NUM_TICK_SELLER] = {0}; 
  
	for(int i=0; i<NUM_TICK_SELLER; i++){
		pthread_create(&tid[i], NULL, seller, &actual_tickets[i]); 
	}

	for(int i=0; i<NUM_TICK_SELLER; i++){
		pthread_join(tid[i], NULL); // wait for the thread to exit 
	}

  int total_tickets = 0; 
  for(int i=0; i<NUM_TICK_SELLER; i++){
    printf("Thread %i sold %d tickets\n", i+1, actual_tickets[i]); 
    total_tickets += actual_tickets[i]; 
  } 
	printf("Main: total tickets %d Actually %d tickets have been sold \n", TOTAL_TICKET, total_tickets); 

	return 0; 

}



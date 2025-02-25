#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static volatile int counter = 0; 

pthread_mutex_t mutex_ticket;

void* mythread(void* arg){
  printf("%s: begin\n", (char*)arg); 
  int i; 
  for(i=0; i<1e5; i++){
    pthread_mutex_lock(&mutex_ticket); 
    counter = counter + 1;
    pthread_mutex_unlock(&mutex_ticket); 
  }
  printf("%s: done\n", (char*) arg); 
  return NULL;

}

int main(){

  pthread_t p1, p2; 
  
 	// initialize lock 
	pthread_mutex_init(&mutex_ticket, NULL); 
  
  printf("main: begin (counter = %d)\n", counter); 
  pthread_create(&p1, NULL, mythread, "A"); 
  pthread_create(&p2, NULL, mythread, "B"); 
  
  pthread_join(p1, NULL); 
  pthread_join(p2, NULL); 
  
  int expected = 2e5;
  
  printf("main: done with both (counter = %d) but counter should be %d\n", counter, expected); 
  pthread_mutex_destroy(&mutex_ticket);
  return 0;

}
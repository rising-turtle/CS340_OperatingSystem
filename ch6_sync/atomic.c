#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static volatile int counter = 0; 

void* mythread(void* arg){
  printf("%s: begin\n", (char*)arg); 
  int i; 
  for(i=0; i<1e5; i++){
    counter = counter + 1;
  }
  printf("%s: done\n", (char*) arg); 
  return NULL;

}

int main(){

  pthread_t p1, p2; 
  
  printf("main: begin (counter = %d)\n", counter); 
  pthread_create(&p1, NULL, mythread, "A"); 
  pthread_create(&p2, NULL, mythread, "B"); 
  
  pthread_join(p1, NULL); 
  pthread_join(p2, NULL); 
  
  int expected = 2e5;
  
  printf("main: done with both (counter = %d) but counter should be %d\n", counter, expected); 
  return 0;

}
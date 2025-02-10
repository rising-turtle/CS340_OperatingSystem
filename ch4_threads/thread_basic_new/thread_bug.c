#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define N 10 
int g_sum[N];  // shared between threads 

void* runner(void * param){ // thread function 
	int sum = 0; 
	int upper = *((int*)param); 
  printf("upper is %d\n", upper);
	for(int i=0; i<upper; i++){
		sum += i; 
	}
  g_sum[upper/10] = sum; 
	pthread_exit(0); 

}

int main(int argc, char* argv[]){

  // 1. basic input 
 	pthread_t tid[N]; // thread id
  int index ;  
  
  // fix 
  int tmp[N]; 
  for(int i=0; i<N; i++) tmp[i] = (i+1)*10; 
  
  // create 10 thread, each thread count the sum(i), i = 10, 20, 30, ..., 100
  for(int i = 10; i<=100; i+= 10){
    index = i/10 - 1;
    pthread_create(&tid[index], NULL, runner, (void*)(&(i))); // create thread to run the code
    // printf("index = %d, tmp[index] = %d\n", index, tmp[index]);
    // pthread_create(&tid[index], NULL, runner, (void*)(&tmp[index]));
  }
  
  // wait for each thread
  for(int i=0;i<N; i++){
    pthread_join(tid[i], NULL); 
  }
  
  // output the result 
  for(int i=0; i<N; i++){
    printf("g_sum[%d] = %d\n", (i+1)*10, g_sum[i]);
  }

	return 0; 

}



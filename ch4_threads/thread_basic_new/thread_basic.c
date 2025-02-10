#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int sum;  // shared between threads 

void* runner(void * param){ // thread function 
	sum = 0; 

	int upper = atoi((char*)param); 
	for(int i=0; i<upper; i++){
		sum += i; 
	}
  // 2. Return value of a thread 
  // int * rvals = (int*)malloc(sizeof(int));
  // *rvals = sum;
  // printf("rvals: %d\n", *rvals);
  // return (void*) rvals; 
	pthread_exit(0); 

}

typedef struct {
  int N; 
  char *ptr; 
}MyParam;



void* test_param(void* param){
  MyParam * myparam = (MyParam*)(param); 
  for(int i=0; i<myparam->N; i++){
    printf("%c ", myparam->ptr[i]); 
  }  
  printf("\n"); 
  pthread_exit(0);
}

int main(int argc, char* argv[]){

	if(argc < 2){

	 	printf("usage: ./thread_basic + [number]\n"); 
	 	return -1; 

  }

  // 1. basic input 
 	pthread_t tid; // thread id 
	pthread_create(&tid, NULL, runner, argv[1]); // create thread to run the code
	pthread_join(tid, NULL); // wait for the thread to exit 
	printf("sum = %d\n", sum); 
  
  // 2. Return value of a thread 
  // int *rvals;
  // pthread_join(tid, (void**)&rvals);
  // printf("sum = %d\n", *rvals);

  // 3. What if pass more than a parameter ? 
  char char_array[4] = {'a', 'b', 'c', 'd'}; 
  MyParam myparam; 
  myparam.N = 4; 
  myparam.ptr = char_array;
  pthread_create(&tid, NULL, test_param, &myparam); 
  pthread_join(tid, NULL);
  

	return 0; 

}



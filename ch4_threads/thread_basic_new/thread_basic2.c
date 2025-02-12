
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum = 0; 

void * runner(void * param){
  int upper = atoi((char*)param);
  for(int i=1; i<=upper; i++){
    sum += i; 
  }
  
  pthread_exit(0);  
}

typedef struct{
  char** ptr; 
  int N; 
} MyStruct; 

void * func1(void * param){
  MyStruct * pdata = (MyStruct*)param; 
  for(int i=0; i<pdata->N; i++){
    printf("%s \n", pdata->ptr[i]);
  }
}

int main(int argc, char* argv[]){

  pthread_t tid; 
  
  char* myarray[4] = {"a", "bb", "cccc", "dog"}; 
  
 // pthread_create(&tid, NULL, runner, argv[1]); 
  MyStruct mystruct; 
  mystruct.ptr = myarray; 
  mystruct.N = 4; 
  pthread_create(&tid, NULL, func1, (void*)&mystruct);  
  pthread_join(tid, NULL); 
  printf("sum = %d\n", sum);
  return 0;
}










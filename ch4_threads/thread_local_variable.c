#define _MULTI_THREADED
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define  NUMTHREADS   2 

/* 
   Use the keyword provided by pthread.h to delcare the following variable
   is thread specific, i.e. it is only visible to a specific thread, 
   not shared/common to all thread.
   These variables are stored in thread local storage (TLS) area.
 */
__thread int TLS_data1;
__thread int TLS_data2;


void update(int); 
void show(int);


void *thread_run(void *param)
{
  int thread_num = *((int*)param);
  printf("thread_num = %d\n", thread_num);
  update(thread_num); 
  for(int i=0; i<3; i++){
      show(thread_num);
      sleep(1); 
  }
   return NULL;
}
 
void update(int thread_num){
   if(thread_num == 1){
      TLS_data1 = 10; 
      TLS_data2 = 11; 
   }else{
      TLS_data1 = 20; 
      TLS_data2 = 21; 
   }
}

void show(int thread_num) {
   printf("Thread %d:, TLS data=%d %d\n", thread_num, TLS_data1, TLS_data2);
}
 

int main(int argc, char **argv)
{
  int i;
  pthread_t             thread[NUMTHREADS];
  int thread_num[NUMTHREADS] = {1, 2}; 
  for (i=0; i < NUMTHREADS; i++) { 
      /* Create per-thread TLS data and pass it to the thread */
      printf("i = %d\n", i);
      pthread_create(&thread[i], NULL, thread_run, &thread_num[i]);
  }
 
  for (i=0; i < NUMTHREADS; i++) {
      pthread_join(thread[i], NULL);
  }

  printf("Main completed\n");
  return 0;
}
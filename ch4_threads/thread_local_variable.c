#define _MULTI_THREADED
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void foo(void);  /* Functions that use the TLS data */
void bar(void);
 
#define checkResults(string, val) {             \
 if (val) {                                     \
   printf("Failed with %d at %s", val, string); \
   exit(1);                                     \
 }                                              \
}
 
/* 
   Use the keyword provided by pthread.h to delcare the following variable
   is thread specific, i.e. it is only visible to a specific thread, 
   not shared/common to all thread.
   These variables are stored in thread local storage (TLS) area.
 */
__thread int TLS_data1;
__thread int TLS_data2;
 
#define  NUMTHREADS   2 

typedef struct {
   int   data1;
   int   data2;
} threadparm_t; 

void *thread_run(void *parm)
{
   int               rc;
   threadparm_t     *gData;

   printf("Thread %.16lx: Entered\n", pthread_self());

   gData = (threadparm_t *)parm;

   /* Assign the value from global variable to thread specific variable*/
   TLS_data1 = gData->data1; // thread 1: 0, thread 2: 1
   TLS_data2 = gData->data2; // thread 1: 2, thread 2: 4

  for(int i=0; i<3; i++){
      foo();
      sleep(1); 
  }
   return NULL;
}
 
void foo() {
   printf("Thread %.16lx:, TLS data=%d %d\n",
          pthread_self(), TLS_data1, TLS_data2);
}
 

int main(int argc, char **argv)
{
  pthread_t             thread[NUMTHREADS];
  int                   rc=0;
  int                   i;
  threadparm_t          gData[NUMTHREADS];
 
  printf("Enter Testcase - %s\n", argv[0]);
 
  printf("Create/start %d threads\n", NUMTHREADS);
  for (i=0; i < NUMTHREADS; i++) { 
     /* Create per-thread TLS data and pass it to the thread */
     gData[i].data1 = i;
     gData[i].data2 = (i+1)*2;
     rc = pthread_create(&thread[i], NULL, thread_run, &gData[i]);
     checkResults("pthread_create()\n", rc);
  }
 
  printf("Wait for all threads to complete, and release their resources\n");
  for (i=0; i < NUMTHREADS; i++) {
     rc = pthread_join(thread[i], NULL);
     checkResults("pthread_join()\n", rc);
  }

  printf("Main completed\n");
  return 0;
}
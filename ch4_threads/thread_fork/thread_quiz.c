#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *runner();

int main(){
   pthread_t tid; 
   pthread_create(&tid,NULL,runner,NULL);
   printf("Hello world %d. \n", getpid());
   pthread_join(tid,NULL);
   printf("Hello world %d. \n", getpid());
}


void *runner(){
   printf("Hello thread.\n");
   char* args[3];
   args[0] ="/bin/ls";
   args[1] = "-a";

   args[2] = NULL;
   execv(args[0],args);
   pthread_exit(0);
}

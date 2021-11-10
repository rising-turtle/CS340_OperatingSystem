// https://stackoverflow.com/questions/30121124/shared-memory-and-posix-semaphores?rq=1


#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "common.h"
#include <sys/shm.h>

int memoryID;
struct wrapper *memory;
int check_prime(int a);
int main(int argc, char **argv) {
    srand(time(NULL));
    key_t sharedMemoryKey = ftok(".",MEMORY_KEY);
    if(sharedMemoryKey==-1)
    {
        perror("ftok():");
        exit(1);
    }

    // attempt to retrieve a existing shared memory object by using the Key
    // return the identifier of the shared memory object 
    memoryID=shmget(sharedMemoryKey,sizeof(struct wrapper),0);

    if(memoryID==-1)
    {
        perror("shmget(): ");
        exit(1);
    }

    // attach the shared memory object to current process space
    memory = shmat(memoryID,NULL,0);
    if(memory== (void*)-1)
    {
        perror("shmat():");
        exit(1);
    }
    int n; 
    int temp; 

    while(1)
    {
        sem_wait(&memory->full);
        sem_wait(&memory->mutex);

        n = memory->n;
        temp = (memory->array)[n];
        printf("Removed item: %d\tNumer of tasks left:%d\n",
             (temp),n);
        memory->n--;

        sem_post(&memory->mutex);
        sem_post(&memory->empty);
        usleep(30000);
    }

}

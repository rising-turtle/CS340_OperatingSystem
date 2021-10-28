// https://stackoverflow.com/questions/30121124/shared-memory-and-posix-semaphores?rq=1


#include <semaphore.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <fcntl.h>
#include "common.h"

int memoryID;
struct wrapper *memory;
int rc;

void atexit_function() {
    rc = shmctl(memoryID, IPC_RMID, NULL);
    rc = shmdt(memory);
    // sem_destroy(&memory->pmutex);
    // sem_destroy(&memory->cmutex);
    sem_destroy(&memory->mutex);
    sem_destroy(&memory->empty);
    sem_destroy(&memory->full);
}

int main(int argc, char **argv) {
    atexit(atexit_function);

    //creating key for shared memory
    srand(time(NULL));
    key_t sharedMemoryKey = ftok(".", MEMORY_KEY);
    if (sharedMemoryKey == -1) {
        perror("ftok():");
        exit(1);
    }


    // generate a shared memory object by using the unique Key
    // return the identifier of the shared memory object 
    memoryID = shmget(sharedMemoryKey, sizeof(struct wrapper), IPC_CREAT | 0600);
    // memoryID = shmget(sharedMemoryKey, sizeof(struct wrapper), IPC_CREAT );

    if (memoryID == -1) {
        perror("shmget():");
        exit(1);
    }

    // attach the shared memory object to current process space
    memory = shmat(memoryID, NULL, 0);  
    if (memory == (void *) -1) {
        perror("shmat():");
        exit(1);
    }

    //initialization

	/* The pshared argument indicates whether this semaphore  is  to  be  shared  between  the
   threads of a process, or between processes.

   If  pshared  has  the  value  0,  then the semaphore is shared between the threads of a
   process, and should be located at some address that is visible to all threads (e.g.,  a
   global variable, or a variable allocated dynamically on the heap).

   If  pshared  is  nonzero, then the semaphore is shared between processes, and should be
   located in a region of shared memory (see shm_open(3), mmap(2), and shmget(2)).  (Since
   a  child  created  by fork(2) inherits its parent's memory mappings, it can also access
   the semaphore.)  Any process that can access the shared memory region  can  operate  on
   the semaphore using sem_post(3), sem_wait(3), etc.*/

    printf("Initializtaion !\n");
    memset(&memory->array, 0, sizeof(memory->array));
    // sem_init(&memory->pmutex, 1, 1);
    // sem_init(&memory->cmutex, 1, 1);
    sem_init(&memory->mutex, 1, 1);
    sem_init(&memory->empty, 1, SIZE_OF_ARRAY);
    sem_init(&memory->full, 1, 0);
    memory->n = -1;

    while(1)
    {
        // int r = rand();
        sem_wait(&memory->empty);
        sem_wait(&memory->mutex);
        memory->n++;
        (memory->array)[memory->n]=memory->n;
        printf("Adding task\t Value:%d\tNumber of tasks waiting:%d \n",memory->n,memory->n);
        sem_post(&memory->mutex);
        sem_post(&memory->full);
        usleep(10000);
    }

}
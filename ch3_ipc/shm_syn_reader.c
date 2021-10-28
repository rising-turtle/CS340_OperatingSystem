
// https://www3.physnet.uni-hamburg.de/physnet/Tru64-Unix/HTML/APS33DTE/DOCU_004.HTM
// 
// https://www3.physnet.uni-hamburg.de/physnet/Tru64-Unix/HTML/APS33DTE/DOCU_010.HTM#sem-shm-ex


/**********  reader.c  ***********/

#include <sys/types.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

char shm_fn[] = "my_shm";
char sem_fn[] = "my_sem";

/**** READER ****/

int main(){
  caddr_t shmptr;
  int shmdes, index;
  sem_t *semdes;
  int SHM_SIZE;

  /* Open the shared memory object */

  SHM_SIZE = 4096; // sysconf();

  if ( (shmdes = shm_open(shm_fn, O_RDWR, 0)) == -1 ) {
     perror("shm_open failure");
     exit(1);
   }

  if((shmptr = mmap(0, SHM_SIZE, PROT_WRITE|PROT_READ, MAP_SHARED,
               shmdes,0)) == (caddr_t) -1){
     perror("mmap failure");
    exit(1);
  }

 /* Open the Semaphore */

 semdes = sem_open(sem_fn, 0, 0644, 0);

 if(semdes == (void*) -1){
   perror("sem_open failure");
   exit(1);
 }


 // sleep for 10 seconds
 printf("reader try to read data\n"); 

 /* Lock the semaphore */

 if(!sem_wait(semdes)){
  // sem_wait(semdes); // should block here if semaphore's value is <= 0
  /* Access to the shared memory area */

   for(index = 0; index < 100; index++)
        printf("The shared memory shmptr[%d] = %d\n", index,shmptr[index]);

  /* Release the semaphore lock */
  // sem_post(semdes);
  }

  printf("reader finished and exit.\n"); 

  munmap(shmptr, SHM_SIZE);

  /* Close the shared memory object */

  close(shmdes);

  /* Close the Semaphore */

  sem_close(semdes);
  sem_unlink(sem_fn);
}

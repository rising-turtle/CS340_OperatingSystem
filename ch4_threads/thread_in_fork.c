/*
    How does fork handle multiple threads in Linux ? 

  */
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#define MAX 10
pthread_t thread[2];
int number=0;
void *thread1(void* param)
{
        printf ("thread1 : I'm thread 1 with id: %lx in process: %d\n", pthread_self(), getpid());
        for (int i = 0; i < MAX; i++)
        {
                printf("thread1 : number = %d\n",number);
                number++;
                sleep(2);
        }
        printf("thread1 : with id %lx exit in process: %d\n", pthread_self(), getpid());
        pthread_exit(NULL);
}
void *thread2(void* param)
{
        printf("thread2 : I'm thread 2 with id: %lx in process: %d\n", pthread_self(), getpid());
        for (int i = 0; i < MAX; i++)
        {
                printf("thread2 : number = %d\n",number);
                number++;
                sleep(3);
        }
        printf("thread2 : with id %lx exit in process: %d\n", pthread_self(), getpid());
        pthread_exit(NULL);
}
void thread_create(void)
{
        int temp;
        memset(&thread, 0, sizeof(thread));          //comment1

        if((temp = pthread_create(&thread[0], NULL, thread1, NULL)) == 0)       //comment2
                printf("successfully create thread 1 \n");
        else
                printf("failed to create thread 1\n");
        if((temp = pthread_create(&thread[1], NULL, thread2, NULL)) == 0)  //comment3
                printf("successfully create thread 2\n");
        else
                printf("failed to create thread 2\n");
}
void thread_wait(void)
{
        if(thread[0] !=0) {                   //comment4
                pthread_join(thread[0],NULL);
                printf("I'm process %d thread 1 exit, move forward \n", getpid());
        }
        if(thread[1] !=0) {                //comment5
                pthread_join(thread[1],NULL);
                printf("I'm process %d thread 2 exit, move forward\n", getpid());
        }
}
int main()
{
        thread_create();

        pid_t pid = fork(); 
        if(pid == 0){
            // child 
            printf("I am child with pid: %d, I'm waiting for thread\n", getpid()); 
            thread_wait();
        }else{
            // parent 
            printf("I am parent with pid: %d, I'm waiting for thread \n", getpid());
            thread_wait();
            wait(NULL); 
        }

        return 0;
}

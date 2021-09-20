/*

    thread_example.c :  c multiple thread programming in linux
    with locks 

  */
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#define MAX 10
pthread_t thread[2];
pthread_mutex_t mut;
int number=0;
void *thread1(void* param)
{
        printf ("thread1 : I'm thread 1 with id: %lx\n", pthread_self());
        for (int i = 0; i < MAX; i++)
        {
                printf("thread1 : number = %d\n",number);
                pthread_mutex_lock(&mut);
                        number++;
                pthread_mutex_unlock(&mut);
                sleep(0.2);
        }
        printf("thread1 : with id %lx exit\n", pthread_self());
        pthread_exit(NULL);
}
void *thread2(void* param)
{
        printf("thread2 : I'm thread 2 with id: %lx\n", pthread_self());
        for (int i = 0; i < MAX; i++)
        {
                printf("thread2 : number = %d\n",number);
                pthread_mutex_lock(&mut);
                        number++;
                pthread_mutex_unlock(&mut);
                sleep(0.3);
        }
        printf("thread2 : with id %lx exit\n", pthread_self());
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
                printf("thread 1 exit, move forward \n");
        }
        if(thread[1] !=0) {                //comment5
                pthread_join(thread[1],NULL);
                printf("thread 2 exit, move forward\n");
        }
}
int main()
{
        pthread_mutex_init(&mut,NULL);
        thread_create();
        thread_wait();
        return 0;
}

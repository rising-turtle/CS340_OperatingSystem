// cond_join_example.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

// Shared state
static int done = 0; // state 

// Synchronization primitives
pthread_mutex_t g_lock;
pthread_cond_t  cv;

// "Child thread exits" signal
void thr_exit(void) {
    pthread_mutex_lock(&g_lock);
    done = 1;
    pthread_cond_signal(&cv);   // wake up one waiting thread
    pthread_mutex_unlock(&g_lock);
}

// "Join" implemented with a condition variable
void thr_join(void) {
    pthread_mutex_lock(&g_lock);
    while (done == 0) {
        // Atomically: release m and sleep; when woken, re-acquire m
        pthread_cond_wait(&cv, &g_lock);
    }
    pthread_mutex_unlock(&g_lock);
}

// Child thread function
void* child(void* arg) {
    printf("child\n");
    sleep(5); // sleep about 5 seconds
    
    thr_exit();
    return NULL;
}

int main(int argc, char* argv[]) {

    printf("parent: begin\n");
    pthread_t p;
    if (pthread_create(&p, NULL, child, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }
    thr_join();
    printf("parent: end\n");

    // Not strictly needed for correctness here because we already waited on `done`,
    // but it's good practice to join the pthread to reclaim resources.
    // pthread_join(p, NULL);

    return 0;
}
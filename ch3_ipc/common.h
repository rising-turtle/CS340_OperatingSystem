
#pragma once 

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>

#define MEMORY_KEY 12
#define SIZE_OF_ARRAY 1024
struct wrapper
{
    int array[SIZE_OF_ARRAY];
    sem_t empty;
    // sem_t pmutex;
    // sem_t cmutex;
    sem_t mutex;
    sem_t full;
    int n;
};
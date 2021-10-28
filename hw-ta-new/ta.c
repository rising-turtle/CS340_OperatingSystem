/**
 * General structure of the teaching assistant.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "ta.h"

/* semaphores and mutex lock */
pthread_mutex_t 	mutex_lock;

/* semaphore declarations */
sem_t			students_sem;
sem_t			ta_sem;

/* the number of waiting students */
int waiting_students;

/* student being served */
int student_number;

/* the numeric id of each student */
int student_id[NUM_OF_STUDENTS];

void *ta_loop(void *param)
{
	int sleep_time;

	/* seed random generator */
	srandom((unsigned)time(NULL));

	while (1) {

	/*
	Missing code
	*/


	}
}


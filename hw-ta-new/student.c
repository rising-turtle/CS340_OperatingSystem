/**
 * General structure of a student.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "ta.h"

void *student_loop(void *param)
{
	int *lnumber = (int *)param;
	int number = *lnumber;
	int sleep_time;
	int times_through_loop = 0;

	srandom((unsigned)time(NULL));

	while (times_through_loop < 2) {
		sleep_time = (int)((random() % MAX_SLEEP_TIME) + 1);
		hang_out(*lnumber,sleep_time);

		/*
		Missing code
		*/
	}
}


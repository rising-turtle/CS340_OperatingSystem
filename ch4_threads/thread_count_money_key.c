#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_BILLS 1000 // 1024; 
#define NUM_COUNTERS 6 // 1, 5, 10, 20, 50, 100
int bill_array[NUM_BILLS];   // shared between threads 

int sum = 0; 
int sum_cnt_g = 0; 
void generate_random(); 

void* count(void * param) // thread function 
{
	int sum_local = 0; // sum of the bills 
	int sum_cnt = 0; // save the number of bills equal to bill value 
	int bill_value = (*(int*)param); // bill value that this thread counts 

	// count the bill and calculate the sum of the bills 
	for(int i=0; i<NUM_BILLS; i++){
		if(bill_array[i] == bill_value){
			sum_cnt++; 
			sum_local += bill_value; 
		}
	}
	usleep(bill_value*100); 
	printf("Thread %.16lx is counting %d dollar bill, and I find %d bills and total is: %d \n", 
							pthread_self(), bill_value, sum_cnt, sum_local); 
	sum += sum_local;
	sum_cnt_g += sum_cnt; 
	pthread_exit(0); 

}

int main(int argc, char* argv[]){

	generate_random(); // randomly generate NUM_CASH cash

	pthread_t counters[NUM_COUNTERS]; // thread id 
	int bill_values[NUM_COUNTERS] = {1, 5, 10, 20, 50, 100}; 

	// Create threads 
	for(int i=0; i<NUM_COUNTERS; i++)
		pthread_create(&counters[i], NULL, count, (void*)(&bill_values[i])); // create thread to run the code 

	// Wait for threads
	for(int i=0; i<NUM_COUNTERS; i++)
		pthread_join(counters[i], NULL); // wait for the thread to exit 

	printf("total: %d bills with sum %d dollars\n", sum_cnt_g, sum); 

	return 0; 
}



void generate_random(){

	// 1 -> 1 dollar 
	// 2 -> 5 dollar 
	// 3 -> 10 dollar 
	// 4 -> 20 dollar 
	// 5 -> 50 dollar
	// 6 -> 100 dollar

	srand(time(NULL)); 
	for(int i=0; i<NUM_BILLS; i++){
		int ran_v = rand()%6 + 1; 
		switch(ran_v){
			case 1:
				bill_array[i] = 1; 
				break; 
			case 2:
				bill_array[i] = 5; 
				break; 
			case 3:
				bill_array[i] = 10; 
				break; 
			case 4:
				bill_array[i] = 20; 
				break; 
			case 5: 
				bill_array[i] = 50; 
				break; 
			case 6: 
				bill_array[i] = 100;
				break; 
			default:
				printf("what? ran_v = %d\n", ran_v);
				break;
		}
	}
	for(int i=0; i<NUM_BILLS; i++){
		printf(" %d ", bill_array[i]);
	}
	printf("\n");
	return ; 
}
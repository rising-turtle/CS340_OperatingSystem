// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <windows.h>

void cpu_usage_half();

void cpu_usage_sin(); 

#define pi 3.141592654

int _tmain(int argc, _TCHAR* argv[])
{

	cpu_usage_sin(); 
	// cpu_usage_half(); 

	return 0;
}

void cpu_usage_sin()
{
	static const int N = 200; 

	int busy_time[N]; 
	int idle_time[N]; 
	double cpu_usage[N]; 

	// sin() curve samples 
	for(int i=0; i<N; i++)
		cpu_usage[i] = sinf((double)(i)/((double)(N-1))*2*pi); 

	// sin() [-1, 1] => [0 1]
	for(int i=0; i<N; i++)
		cpu_usage[i] = (cpu_usage[i]+1)/2.; 
	
	// time_span = 20 ms 
	double time_span = 20; 
	for(int i=0; i<N; i++){
		busy_time[i] = time_span * cpu_usage[i]; 
		idle_time[i] = time_span - busy_time[i]; 
	}
	
	// 
	int j = 0;
	__int64 cur_time ; 
	while(true){
		j = j % N; 
		
		// running for busy time 
		cur_time = GetTickCount(); 
		while((GetTickCount() - cur_time) < busy_time[j]); 

		// sleep for idle time 
		Sleep(idle_time[j]); 
		j++; 
	}

}


void cpu_usage_half(){
	
	int busy_time = 10; // 10 ms
	int idle_time = 10; // 10 ms

	__int64 cur_time; 

	while(1){

		// running 10 ms 
		cur_time = GetTickCount(); 	
		while((GetTickCount() - cur_time) < busy_time); 

		// sleeping 10 ms 
		Sleep(idle_time); 

	}
	return; 
}
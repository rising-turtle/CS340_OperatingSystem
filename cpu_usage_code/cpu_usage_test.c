void cpu_usage_test(){

	int busyTime = 10; // 10ms 
	int idleTime = busyTime; // same ratio will lead to 50% cpu usage 

	__int64 startTime = 0; 

	while(true){
	
		startTime = GetTickCount(); 
		// busy loop 
		while((GetTickCount() - startTime) < busyTime) ; 

		// idle loop 
		Sleep(idleTime); 
	
	}

}


void cpu_usage_test_sin(){
	const double SPLIT = 0.01;
	const int COUNT = 200; // 200*0.01 = 2 PI
	const double PI = 3.141592654; 
	const int INTERVAL = 300; 

	DWORD busySpan[COUNT]; // array of busy times 
	DWORD idleSpan[COUNT]; // array of idle times 
	int half = INTERVAL / 2; 
	
	double radian = 0.0; 
	for(int i=0; i< COUNT; i++){
		busySpan[i] = (DWORD) (half + (sin(PI*radian)*half));
		idleSpan[i] = INTERVAL - busySpan[i]; 
		radian += SPLIT; 
	}
	DWORD startTime = 0; 
	int j = 0; 
	while(true){
		j = j % COUNT; 
		startTime = GetTickCount(); 
		while((GetTickCount() - startTime) <= busySpan[j]) ; 
		Sleep(idleSpan[j]); 
		j++;
	}
}
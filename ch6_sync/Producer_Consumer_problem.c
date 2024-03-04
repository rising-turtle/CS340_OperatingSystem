
int loops = 1e5;  
cond_d cond; 
mutex_t mutex; 

void* producer(void* arg){
	int i; 
	for(i =0; i<loops; i++){
		pthread_mutex_lock(&mutex); 
		if(count == MAX) // buffer is full  
			pthread_cond_wait(&cond, &mutex);
		put(i); 
		pthread_cond_signal(&cond); 
		pthread_mutex_unlock(&mutex); 	
	}
}

void* consumer(void* arg){
	int i; 
	for(i=0; i<loops; i++){
		
		pthread_mutex_lock(&mutex); 
		if(count == 0) // buffer is empty 
			pthread_cond_wait(&cond, &mutex); 
		int tmp = get(); 
		pthread_cond_signal(&cond); 
		pthread_mutex_unlock(&mutex); 
		printf("%d\n", tmp); 
	}
}




cond_d empty, fill; 
mutex_t mutex; 
int count = 0;
void* producer(void* arg){
	int i; 
	for(i =0; i<loops; i++){
		
		if(count == MAX) // buffer is full  
			pthread_cond_wait(&empty, &mutex);
		
		pthread_mutex_lock(&mutex); 
		
		// put data to the shared buffer 
		
		++count; 
		
		pthread_cond_signal(&empty); 
		pthread_mutex_unlock(&mutex); 	
	}
}

void* consumer(void* arg){
	int i; 
	for(i=0; i<loops; i++){
	
		if(count == 0) // buffer is empty 
			pthread_cond_wait(&fill, &mutex); 
		
		pthread_mutex_lock(&mutex); 
		
		// take data from the shared buffer 
		
		--count;
		
		pthread_cond_signal(&fill); 
		pthread_mutex_unlock(&mutex); 
	}
}


	pthread_mutex_lock(global); 
	pthread_mutex_lock(L1); 
	pthread_mutex_lock(L2); 
	...
	pthread_mutex_unlock(global); 


	top:
		pthread_mutex_lock(L1); 
		if(pthread_mutex_trylock(L2) != 0){
			pthread_mutex_unlock(L1); 
			goto top; 
		}
		
		
	void AtomicIncrement(int * value, int amount){
		do{
			int old = *value; 
		}while(CompareAndSwap(value, old, old+amount) == 0); 
	}

	void do_something(mutex * m1, mutex * m2){
		
		if(m1 > m2){
			pthread_mutex_lock(m1); 
			pthread_mutex_lock(m2); 
		}else{
			pthread_mutex_lock(m2); 
			pthread_mutex_lock(m1); 
		}
	}


	// sem_wait(&semaphore) is the implementation in POSIX for semaphore.wait() 
	// sem_post(&semaphore) is the implementation in POSIX for semaphore.signal()
	// sem_init(&semaphore, pshared, ini_value) is the implementation in POSIX 
	// to initialize a sempahore with ini_value. If pshared is 0, it is used for 
	// multithreads, otherwise, it is used for multiprocesses.   	
	
	sem_t semaphore;
	int* pG = 0; 
	void* func1(void* param){

		pG = (int*)malloc(sizeof(int)); 
		
		pthread_exit(0);
	
	}

	void* func2(void* param){

		*pG = 24; 
		
		pthread_exit(0);
	}

	int main(int argc, char* argv[]){

		pthread_t tid1, tid2;  
		pthread_create(&tid1, NULL, func1, NULL); 
		pthread_create(&tid2, NULL, func2, NULL); 

		pthread_join(&tid1); 
		pthread_join(&tid2); 

		return 0; 

	}



	void *runner(); 
	sem_t mysem;
	int val = 42;
	int main(int argc, char *argv[]) {
	  pthread_t tid1, tid2; 
	  pthread_attr_t attr;
	  pthread_attr_init(&attr);
	  sem_init(&mysem, 0, 2);
	  pthread_create(&tid1,&attr,runner,NULL);
	  pthread_create(&tid2,&attr,runner,NULL);
	  pthread_join(tid1,NULL);
	  pthread_join(tid2,NULL);
	  sem_destroy(&mysem);
	  return 0;
	}
	void *runner()  {
	  int valcopy = val;
	  sem_wait(&mysem);
	  val = valcopy + 42;
	  sem_post(&mysem);
	  pthread_exit(0);
	}




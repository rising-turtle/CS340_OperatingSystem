#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>

char * default_cmd = "ps -eo user,pid,ppid,nlwp,pcpu,pmem,comm";

int main(int argc, char* argv[]){

	char data[1024]; 
	FILE* pipe; 
	if(argc <= 1){
		// printf("useage: input a command\n"); 
		printf("use default cmd: %s\n", default_cmd); 
		pipe = popen(default_cmd, "r"); 

	}else{
		printf("run cmd: %s\n", argv[1]);
		pipe = popen(argv[1], "r"); 
	}

	// FILE* pipe = popen(argv[1], "r"); 
	int line = 1; 
	while(fgets(data, sizeof(data), pipe) != NULL){

		printf("line %d: \n", line++);
		printf("%s\n", data); 
	}

	return 0;

}
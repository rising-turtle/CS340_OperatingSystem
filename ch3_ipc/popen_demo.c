#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	char data[1024]; 
	if(argc <= 1){
		printf("useage: input a command\n"); 
		return -1; 
	}

	FILE* pipe = popen(argv[1], "r"); 
	int line = 1; 
	while(fgets(data, sizeof(data), pipe) != NULL){

		printf("line %d: \n", line++);
		printf("%s\n", data); 
	}

	return 0;

}
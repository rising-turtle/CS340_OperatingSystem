#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[])
{

	printf("input a command!\n"); 

	char program_name[1024]; 
	fgets(program_name, 1024, stdin); 

	program_name[strcspn(program_name, "\n")] = 0; // get rid of linefeed char
	printf("get input %s\n", program_name);

	pid_t pid = fork(); 

	if(pid == 0){

		// child process
		execlp(program_name, program_name, NULL); // Load the program 

		// only print this if the program cannot be found 
		printf("I cannot find this program %s\n", program_name);

	}else{
		
		// parent process 
		sleep(1);
		waitpid(pid, 0, 0); // wait for the child process to terminate 
		printf("Program %s has finished!\n", program_name);  

	}
	return 0; 
}
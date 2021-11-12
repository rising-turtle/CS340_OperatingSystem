
// example for ordinary pipe 

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
	int fd[2],n;
	char buffer[100];

	pipe(fd); //creates a unidirectional pipe with two end fd[0] (READ) and fd[1] (WRITE)
	pid_t p = fork();
	if(p>0) // parent
	{
		printf("Parent Passing: hello\n");
		write(fd[1],"hello\n",6); //fd[1] is the write end of the pipe
		// sleep(5); 
		// read(fd[0], buffer, 100); 
		// printf("parent read %s\n", buffer); 
		wait(NULL);
	}
	else // child
	{
		printf("Child printing received value\n");
		n=read(fd[0],buffer,100); //fd[0] is the read end of the pipe
		printf("child reads %s \n", buffer); 
		// sleep(2); 
		// write(fd[1], "hello2\n", 7);
		// printf("child passing hello2\n"); 

	}
	return 0; 
}
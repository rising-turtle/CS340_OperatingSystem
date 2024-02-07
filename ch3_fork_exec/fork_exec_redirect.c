
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){


    int pid = fork(); 

    if(pid < 0){
        fprintf(stderr, "fork failed\n"); 
        exit(-1);
    }else if(pid == 0){ // child process
        close(STDOUT_FILENO); 
        open("./tmpfile", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);


        // now exec wc 
        char * myargs[3]; 
        myargs[0] = strdup("wc"); 
        myargs[1] = strdup("fork_exec_input.c");
        myargs[2] = NULL; 

        execvp(myargs[0], myargs);
        
    }else{ // parent process
        wait(NULL); 
    }
    return 0; 
}
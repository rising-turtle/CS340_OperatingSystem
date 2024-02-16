#include <assert.h>
#include <stdio.h>
#include <pthread.h>

typedef struct {
    int a;
    int b;
} myarg_t;

typedef struct {

    char** ptr; 
    int N; 

}myarg_t2; 

void *mythread_struct(void *arg) {
    myarg_t *args = (myarg_t *) arg;
    printf("%d %d\n", args->a, args->b);
    return NULL;
}

void *mythread_string(void* arg){
    char** args = (char**)(arg); 
    printf("%s\n", *args); 
    return NULL; 
}


void *mythread_array(void* arg){
    char* args = (char*) arg; 
    for(int i=0; i<6; i++){
        printf("%c ", args[i]); 
    }
    printf("\n"); 
    return NULL; 
}


void *mythread_array_str(void* arg){
    char** args = (char**)arg; 
    for(int i=0; i<6; i++){
        printf("%s \n", args[i]);
    }
    return NULL; 
}

void* mythread_struct2(void* arg){
    myarg_t2* args = (myarg_t2*)(arg); 
    for(int i=0; i<args->N; i++){
        printf("%s \n", args->ptr[i]);
    }
    return NULL;
}


int main(int argc, char *argv[]) {
    pthread_t p;
 
    // pass in a struct 
    // myarg_t args = { 10, 20 };
    // int rc = pthread_create(&p, NULL, mythread, &args); 

    // pass in a string 
    // char * myparam = "my param"; 
    // int rc = pthread_create(&p, NULL, mythread, &myparam);


    // pass in an array of chars 
    char array[6] = {'a', 'b', 'c', 'd', 'e', 'f'};
    // int rc = pthread_create(&p, NULL, mythread_array, (void*)(array));

    // pass in two dimension array 
    char array2[3][2] = {{'a', 'b'}, {'c', 'd'}, {'e', 'f'}}; 
    // int rc = pthread_create(&p, NULL, mythread_array, array2);

    // pass in an array of strings 
    char* array3[6] = {"ab", "cd", "ffff", "ehg", "xxx", "a"}; 
    // int rc = pthread_create(&p, NULL, mythread_array_str, array3);

    // pass in a structured array 
    myarg_t2 myarg2; 
    myarg2.ptr = array3; 
    myarg2.N = sizeof(array3)/sizeof(array3[0]); 
    int rc = pthread_create(&p, NULL, mythread_array_str, array3);

    assert(rc == 0);
    (void) pthread_join(p, NULL);
    printf("done\n");
    return 0;
}

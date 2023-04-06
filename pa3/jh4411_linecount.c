#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

// These are the global variables I am using to lock the variables on 
// multiple threads and the variables I am using to keep track of 
// the linecount in each file.
pthread_mutex_t lock;
int lines = 0;
int linecount = 0;

// This function is what each thread is using for linecount
void* filelinecount(void * arg){
     FILE* file = fopen(arg, "r");
     char *line = NULL;
     size_t len = 0;
     ssize_t read;

// I looked at the manpage for reference on how to set
// up this while loop to iterate based on the files lines
// instead of character count etc. 
// https://linux.die.net/man/3/getline
     while((read = getline(&line, &len, file)) != -1){
// I locked this variable, since multiple threads use it to keep track 
// of the linecount
          pthread_mutex_lock(&lock);
          lines++;
          pthread_mutex_unlock(&lock);
     }

     fclose(file);
     printf("%d %s\n", lines, arg);

     pthread_mutex_lock(&lock);
     linecount += lines;
     lines = 0;
     pthread_mutex_unlock(&lock);
     pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
     int error;
     pthread_t tid[argc];

// This check is to make sure that the lock initalization
// works so I will not have to worry about global variables
// having werid values.
     if (pthread_mutex_init(&lock, NULL) != 0) {
          printf("\n mutex init has failed\n");
          return 1;
     }

// This is the main loop of my program. It starts all of the threads and 
// joins the open ones to make sure the linecount is correct. 
// I started the loop on one to avoid the program name in the arguements
// being passed to the threads and I then decremented the variable on thread
// creation.
// I used this website for reference: 
// https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/
     for(int i = 1; i <argc; i++){
          error = pthread_create(&tid[i-1], NULL, &filelinecount, (char**)argv[i]);
          if (error != 0){ 
               printf("\nThread can't be created : [%s]", strerror(error));
          }
          pthread_join(tid[i-1], NULL);
     }

// This handles cleanup and is the final print to the screen after
// the threads
     printf("%d total\n", linecount);
     pthread_exit(NULL);
     pthread_mutex_destroy(&lock);
     return 0;
}

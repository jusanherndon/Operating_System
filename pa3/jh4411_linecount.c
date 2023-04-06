#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int lines = 0;

void* filelinecount(void * arg){
FILE* file;

char *line = NULL;
size_t len = 0;
ssize_t read;

file = fopen(arg, "r"); 

while((read = getline(&line, &len, file)) != -1){
     lines++;
}

printf("%d %s\n", lines, arg);

fclose(file);
lines = 0;

}

int main(int argc, char* argv[]) {
int error;
pthread_t tid[argc];
int linecount = 0;
int lines = 0;



for(int i = 1; i <argc; i++){
     error = pthread_create(&tid[i-1], NULL, &filelinecount, (char**)argv[i]);
     if (error != 0) printf("\nThread can't be created : [%s]", strerror(error));
     lines = error;
     pthread_join(tid[i-1], NULL);
     linecount += lines;
     lines = 0;
}


printf("%d total\n", linecount);
}

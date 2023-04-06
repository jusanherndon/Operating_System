#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t lock;
int lines = 0;
int linecount = 0;

void* filelinecount(void * arg){
pthread_mutex_lock(&lock);
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
linecount += lines;
pthread_mutex_unlock(&lock);
}

int main(int argc, char* argv[]) {
int error;
pthread_t tid[argc];

if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }

for(int i = 1; i <argc; i++){
     error = pthread_create(&tid[i-1], NULL, &filelinecount, (char**)argv[i]);
     if (error != 0) printf("\nThread can't be created : [%s]", strerror(error));
     pthread_join(tid[i-1], NULL);
}

printf("%d total\n", linecount);
pthread_mutex_destroy(&lock);
return 0;
}

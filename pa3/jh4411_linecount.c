#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int filelinecount(char filename[]){
FILE* file;
int lines = 0;

char *line = NULL;
size_t len = 0;
ssize_t read;

file = fopen(filename, "r"); 

while((read = getline(&line, &len, file)) != -1){
     lines++;
}

fclose(file);
return lines;
}

int main(int argc, char* argv[]) {
int linecount = 0;
int lines;

for(int i = 1; i <argc; i++){
     lines = filelinecount(argv[i]);
     printf("%d %s\n", lines, argv[i]);
     linecount += lines;
     lines = 0;
}

printf("%d total\n", linecount);
}

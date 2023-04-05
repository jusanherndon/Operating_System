#include <stdio.h>
#include <pthread.h>

int filelinecount(char filename[]){
FILE* file;
int lines;
char buf[200];

file = fopen(filename, "r"); 

while(fgets(buf,sizeof(buf),file) != NULL)
{
  lines++;
}

return lines;
}

int main(int argc, char* argv[]) {
int linecount = 0;
int lines;

for(int i = 1; i <argc; i++){
     lines = filelinecount(argv[i]);
     printf("\n%d %s\n", lines, argv[i]);
     linecount += lines;
     lines = 0;
}

printf("%d total\n", linecount);
}

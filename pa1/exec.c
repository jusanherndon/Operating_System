#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){

char* command = argv[1];
char* arguements[50];

printf("%s\n",command);

for(int i=2;i<argc;i++){
arguements[i] = argv[i];
printf("\n%s\n",arguements[i]);
}

}

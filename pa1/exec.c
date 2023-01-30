#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){

char* command = argv[1];
char* arguements[50] = {};
int counter = 0;

for(int i=2;i<argc;i++){
arguements[counter] = argv[i];
counter++;
}

int status_code = execvp(command,arguements);

if(status_code == -1){
printf("Process did not terminate corectly\n");
return 1;
}

return 0;
}

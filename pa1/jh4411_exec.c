#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){

if(argv[1]== NULL){
printf("A command was not entered in as an arguement. Rerun the program.\n");
return 1;
}

char* command = argv[1];
char* arguements[50] = {};
int counter = 0;
int exit_code = 0;
int status_code = 0;

for(int i=2;i<4;i++){
if(argv[i]== NULL){
exit_code = -1; 
printf("An arguement was left out. Please rerun the program again with all of its arguements\n");
return 1;
}
arguements[counter] = argv[i];
counter++;
}

if(exit_code != -1){
status_code = execvp(command,arguements);
}

if(status_code == -1){
printf("Process did not terminate corectly\n");
return 1;
}

return 0;
}

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){

if(argc < 4){
printf("Not enough arguemnts were entered into the command line. Please enter the correct amount\n");
return 1;
}
if(argv[1]== NULL){
printf("A command was not entered in as an arguement. Rerun the program.\n");
return 1;
}

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

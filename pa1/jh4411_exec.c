#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
// This is a check to make sure that the currect amount of arguemnts are used for the executable
if(argc < 4){
printf("Not enough arguemnts were entered into the command line. Please enter the correct amount\n");
return 1;
}
// Setting arg 1 as the command, since arg 0 is the executable name. Another counter is initalized
// becuase the command starts at arg 2 for the inputted executable while it needs to be in 
// position 0 for the arguements array.
// Also setting up the arg array as 50 args as stated in the instructions. 
char* command = argv[1];
char* arguements[50] = {};
int counter = 0;
// Simple for loop to place the inputted arguements in the correct place in the arguemnts array. It 
// runs until the given args to the executable NULL thanks to the argc variable.
for(int i=2;i<argc;i++){
arguements[counter] = argv[i];
counter++;
}

int status_code = execvp(command,arguements);
// error checking to make sure that the command actually ran and is a valid linux/unix command
if(status_code == -1){
printf("The command and/or arguements that were inputted are not valid\n");
return 1;
}

return 0;
}

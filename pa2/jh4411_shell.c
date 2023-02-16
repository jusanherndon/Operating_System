#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
// logic used in my last programming assignment in order to take 
// in command arguements and run it as a seperate process this time


char input[10];
char* split_input;
char* args;

while(1){

printf("Please enter a string into the terminal:");
scanf("%s",input);

strtok_r(input, "", &split_input);

// The first line in the string inputed should be the command
//if(split_input[0] != NULL){

char* command;
strcpy(command, input);

strtok_r(split_input, "", &args);

char* arguements[50] = {}; 

arguements[0] = split_input;
arguements[1] = args;

//fork();
int status_code = execvp(command,arguements);

if(status_code == -1){
printf("The command and/or arguements that were inputted are not valid\n");
return 1;
}
//}

}


return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
// logic used in my last programming assignment in order to take 
// in command arguements and run it as a seperate process this time


char input[10];
char* command = malloc(sizeof(input));

//char* split_input;
char* args;

while(1){

printf("Please enter a string into the terminal:");
scanf("%s",input);

strcpy(command, input);

char* arguements[50] = {}; 

arguements[0] = NULL;

//fork();
int status_code = execvp(command,arguements);


if(status_code == -1){
printf("The command and/or arguements that were inputted are not valid\n");
return 1;
}

}


return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
// logic used in my last programming assignment in order to take 
// in command arguements and run it as a seperate process this time


char input[20];
char* command = malloc(sizeof(input));

char* search= " ";
char* args[20] = {};

while(1){

printf("Please enter a string into the terminal:");
fgets(input,sizeof(input),stdin);

puts(input);


command = strtok(input,search);
args[0] = strtok(NULL,search);

printf(args[0]);


//fork();
int status_code = execvp(command,args);


if(status_code == -1){
printf("The command and/or arguements that were inputted are not valid\n");
return 1;
}

}


return 0;
}

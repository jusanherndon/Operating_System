#include <stdio.h>
#include <unistd.h>

int main(){
// logic used in my last programming assignment in order to take 
// in command arguements and run it as a seperate process this time


char input[10];

while(1){

printf("Please enter a string into the terminal:");
scanf("%s",input);

printf("\n%s\n", input);
}

/*
char* command = argv[1];
char* arguements[50] = {};
int counter = 0;

for(int i=2;i<argc;i++){
arguements[counter] = argv[i];
counter++;
}

fork();
int status_code = execvp(command,arguements);

if(status_code == -1){
printf("The command and/or arguements that were inputted are not valid\n");
return 1;
}
*/





return 0;
}

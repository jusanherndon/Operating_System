#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//I used babyshell and simple-strtok as examples

int main(){

char input[50];
char* args[50] = {};
char* arguements[50] = {};
int counter = 0;
int count = 0;

while(1){

printf("Please enter a string into the terminal:");
while ( fgets(input,256,stdin) != NULL ){	
    char* pch = strtok (input," \t\n");
    while (pch != NULL)
        {
	    args[counter] = pch;
	    pch = strtok (NULL, " \t\n");
	    counter++;
        }    
    for(int i=1; i<counter; i++)
        {
	    arguements[count] = args[i];
	    count++;
        }  
    char* command = args[0]; 

    int status_code = execvp(command,arguements);
    
    // error cheching on the command being run
    if(status_code == -1){
        printf("The command and/or arguements that were inputted are not valid\n");
        return 1;
    }
//execlp(command,command, (char *) NULL);  

}
}


return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

//I used babyshell and simple-strtok as examples

int main(){

char input[257];
char* args[50] = {};
char* arguements[50] = {};
int pid;
int counter = 0;
int count = 0;
int status_code; 

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
        char* command = args[0]; 
        switch(pid=fork()){
            /*
            default: wait();
	         break;
            */
	    case 0: status_code = execvp(command,args);
		    break;
        }
    }
}

return 0;
}

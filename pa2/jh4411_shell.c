#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

//I used babyshell and simple-strtok as examples

int main(){

char input[257];
char* args[50] = {};
char* arguements[50] = {};
int pid;
int ampersant = 0;
int counter = 0;
int status_code = 0; 

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

	for(int i = 1; i <counter; i++){
            if(strcspn(args[i], "&")){
	        ampersant = 1;
	    }
	}

        switch(pid=fork()){
	    /*	    
            default: 
	             break;
	    */
	    case 0: status_code = execvp(command,args);
		    wait(&status_code);
		    break;
	    case 1: status_code = execvp(command,args);
		    wait(&status_code);
		    break;
        }
    }
    printf("Please enter a string into the terminal:");
}

return 0;
}

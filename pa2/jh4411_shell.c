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
int pid;
int counter = 0;
int status_code = 0; 

enum ampersand;
enum lessthansign;
enum greatorthansign;


while(1){

    printf("Please enter a string into the terminal:");
    while ( fgets(input,256,stdin) != NULL ){	
        char* pch = strtok (input," \n");
        int ampersant = 0;
        while (pch != NULL){
	        if(strcmp(pch,"&")== 0){
		    ampersant = 1;
		}
		else{
	            args[counter] = pch;
	            pch = strtok (NULL, " \t\n");
	            counter++;
		}
            }    
        char* command = args[0]; 
	
for(int i =0; i < 5; i++){
printf(args[i]);
printf("\n");
}

        switch(pid=fork()){
            
	    default: if(!ampersant){
		     wait(&status_code);
		     }
	             break;
	    case 0: status_code = execvp(command,args);
		    break;
        }
    }
}

return 0;
}

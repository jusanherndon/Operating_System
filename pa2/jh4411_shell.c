#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){

char command[10];
char arg1[20] = "";
char arg2[20] = "";

char* search= " ";
char* arguements[20] = {};
int counter = 0;
int count = 0;

while(1){

printf("Please enter a string into the terminal:");
fscanf(stdin,"%s %s %s", command, arg1, arg2);
	
printf("%s\n", command);
printf("%s\n", arg1);
//printf("%s\n", arg2);

printf("continue");
/*
printf("first strcpy");
if (input != NULL) {

  while ((token = strsep(&input, " ")) != NULL)
  {
    strcpy(args[counter],token);
    //args[counter] = token; 
    counter++;
  }
}

for(int i=1; 1<counter; i++){
arguements[count]= args[i];
count++;
}

puts(input);

strcpy(command,args[0]);
//command = args[0];

printf(command);
printf(arguements[0]);
printf(arguements[1]);
*/
//fork();

/*
int status_code = execvp(command,arguements);


if(status_code == -1){
printf("The command and/or arguements that were inputted are not valid\n");
return 1;
}
*/
}


return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
// logic used in my last programming assignment in order to take 
// in command arguements and run it as a seperate process this time


char input[20];
char* buffer;
char* token;
char* command = malloc(sizeof(input));

char* search= " ";
char* args[20] = {};
char* arguements[20] = {};
int counter = 0;
int count = 0;

while(1){

printf("Please enter a string into the terminal:");
fgets(input,sizeof(input),stdin);

puts(input);


if (input != NULL) {

  buffer = input;

  while ((token = strsep(&buffer, " ")) != NULL)
  {
    args[counter] = token; 
    counter++;
  }

  free(buffer);
}

for(int i=1; 1<counter; i++){
arguements[count]= args[i];
count++;
}


command = args[0];

printf(command);
printf(arguements[0]);
printf(arguements[1]);
//fork();
int status_code = execvp(command,arguements);


if(status_code == -1){
printf("The command and/or arguements that were inputted are not valid\n");
return 1;
}

}


return 0;
}

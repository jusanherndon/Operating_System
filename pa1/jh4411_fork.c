#include <stdio.h>
#include <unistd.h>

int main(){

for(int i=0; i<20;i++){
fork();
printf("%d",i);
}
return 0;
}

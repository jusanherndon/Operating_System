#include <stdio.h>
#include <unistd.h>

int main(){
//Not much to explain here. This is a for loop that forks on every instance until completion and
//prints out its current counter value
for(int i=0; i<20;i++){
fork();
printf("%d",i);
}
return 0;
}

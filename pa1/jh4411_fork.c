#include <stdio.h>
#include <unistd.h>

int main(){
// I am using an if conditional to check if the process running is ths child or the parent

for(int i=0; i<20;i++){
printf("parent:%d\n",i);
}

if(fork()== 0){
for(int i=0; i<20;i++){
printf("child:%d\n",i);
}
}
return 0;
}

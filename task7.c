#include <stdio.h>
#include <unistd.h> 
#include<stdlib.h>
#include<math.h>
int main(int argc,char ** argv)
{
pid_t pid;
pid = fork();

if (pid == 0)
{
printf("\nI am in Child Process\n");
int a = atoi(argv[1]);
while(a!=1)
{
if(a % 2 == 0){
printf("\n %d \n",a);
a=a/2;
}
else
{
printf("\n %d \n",a);
a=(3*a)+1;
}
}
printf("\n %d \n",a);
exit(1);



}
else if(pid>0)
{
printf("\nI am the parent process  \n");
}
else
{
printf("Error fork failed\n");
}
return 0;
}

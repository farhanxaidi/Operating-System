#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<sys/file.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#define READ 0
#define WRITE 1

int main()
{

 pid_t pid;
 int fd[2];
 if(pipe(fd) == 0)
 {
    pid=fork();
    if(pid == 0)
	{
       close(fd[READ]); /*Closes the unused end*/
       dup2(fd[WRITE],1);/*Result of (Grep "Ali" < input.txt) written to Pipe*/ 	     
	   close(fd[WRITE]);/*Used end closed as It's duplicate is in 1(stdout)*/
       int f1=open("./input.txt", 0666|O_RDONLY);/*Opened in read only mode*/
       dup2(f1,0);
       close(f1); /*Input.txt will be Grep's input as it is now 0(stdin) */    
       execlp("grep","grep","Ali",NULL);
      }
      else if(pid > 0)
	  {
          pid=fork();
          if(pid == 0)
		{
			close(fd[WRITE]);/*Closes unused end*/
            dup2(fd[READ],0);/* sort will take input from read end*/
            close(fd[READ]);/*Used end closed as it is in 0(stdin)*/
            int f2=open("./output.txt",0666|O_CREAT|O_TRUNC);
            dup2(f2,1);/* Output.txt is the output of sort 1(stdout)*/
            close(f2);
            execlp("sort","sort",NULL);
		}
			close(fd[WRITE]);
            close(fd[READ]);
            wait(NULL);  
       }
    }
  return 0;
}

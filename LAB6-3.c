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

int main(){

 pid_t pid;
 int fd1[2],fd2[2];
 if(pipe(fd1) == 0 && pipe(fd2) == 0 ){
    pid=fork();
    if(pid == 0){
       int f1=open("./error.txt", 0666|O_CREAT|O_TRUNC|O_RDWR);
       dup2(f1,2);
       close(f1);
       execlp("ls","ls","/","-lR",NULL);
      }
      else if(pid > 0){ 
             wait(NULL);
              pid=fork();
              if(pid == 0){
                 close(fd1[READ]);
                 dup2(fd1[WRITE],1);
                 close(fd1[WRITE]);
                 int f2=open("./error.txt",0666|O_RDONLY);
                 dup2(f2,0);
                 close(f2);
                 execlp("grep","grep","Nov",NULL);
		}
               else if(pid > 0){
                       pid=fork();
                       if(pid == 0){
                          close(fd1[WRITE]);
                 	  dup2(fd1[READ],0);
                 	  close(fd1[READ]);
                          close(fd2[READ]);
			  dup2(fd2[WRITE],1);
                          close(fd2[WRITE]);
                          execlp("sort","sort",NULL);
		        }
                       else if(pid > 0){
                              pid=fork();
                              if(pid == 0){
                                 close(fd2[WRITE]);
                 	         dup2(fd2[READ],0);
                 	         close(fd2[READ]);
                                 execlp("less","less",NULL);
                               }

		      }
 		}
               wait(NULL);
      

       }
    }/* end of Pipe's if */
 

  return 0;
}

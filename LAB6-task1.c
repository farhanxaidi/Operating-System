#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include<signal.h>
#include <sys/wait.h> 
#include <unistd.h> 
int main (int argc, char* argv[])
{

int fd ;
fd = open ("input.txt", O_CREAT | O_TRUNC | O_RDWR, 0777) ;

dup2 (fd, 1) ; 
close (fd) ; 

execlp("ls","ls","/","-l",NULL);

}

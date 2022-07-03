#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
int main(int argc , char *argv[])
{

int filepipe[2];
int filepipe2[2];
if(pipe(filepipe)==0&&pipe(filepipe2)==0)
{


int id = fork();
if(id==0)
{
int size=0;
int buffer[1000];
memset(buffer,0,1000);
close(filepipe[1]);
int byte=read(filepipe[0],buffer,sizeof(buffer));
printf(" \n child read %d bytes from pipe: ",byte);
size=byte/4;
for(int i=0 ; i<size ;i++)
{
printf("%d , ",buffer[i]);
}
  printf("\n");

//bubble sort
int swap=0;
  for (int c = 0 ; c < ( size - 1 ); c++)
  {
    for ( int d = 0 ; d <  size - c - 1; d++)
    {
      if (buffer[d] > buffer[d+1]) /* For decreasing order use < */
      {
        swap       = buffer[d];
        buffer[d]   = buffer[d+1];
        buffer[d+1] = swap;
      }
    }
  }

close(filepipe2[0]);
write(filepipe2[1],buffer,byte);
}
else
{
//parent
int arr[argc-1];
int c=0;
while(c!=argc-1)
{
arr[c]=atoi(argv[c+1]);
printf("%d , ",arr[c]);
c++;
}
int size=sizeof(int)*(argc-1);
close(filepipe[0]);
int byte=write(filepipe[1],&arr,size);

printf("parent write %d bytes in pipe:        ",byte);
  printf("\n");

//reading sorted array
int buffer[argc-1];
close(filepipe2[1]);
read(filepipe2[0],buffer,size);
printf("Sorted array in parent:\n ");
for(int i=0;i<argc-1;i++)
{
printf("%d ",buffer[i]);
}

}
}
return 0;
}




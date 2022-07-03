//Dining philosopher using multiprogramming using semaphores
#include<stdio.h>
#include<fcntl.h>
#include<semaphore.h>
#include<sys/wait.h>
#include<pthread.h>
#include<stdlib.h>
sem_t *sem[20];
int n;
int main()
{
pid_t cpid[5];
char semname[5];
int i,j=0;
n = 5;
for(i=0;i<n;i++)
{
sprintf(semname,”%d”,getpid()+i);
sem[i]=sem_open(semname,O_CREAT|O_EXCL,0666,1);
if(sem[i]==SEM_FAILED)
perror(“Unable to create semaphore”);

}

for(i=0;i<n;i++)
{

cpid[i]=fork();
if(cpid[i]==0)
break;

}
if(i==n)
{
int status;
for(i=0;i<n;i++)
waitpid(cpid[i],&status,WUNTRACED);

//waitpid is a function which waits for the child process to finish executing after that //control switches back to parent
for(i=0;i<n;i++)
{
sem_close(sem[i]);
sprintf(semname,”%d”,getpid()+i);
sem_unlink(semname);
}
}
else
reader(i);

}
int reader(int val)
{
printf(“%d Thinking\n”,val+1);
while(1)
{
sem_wait(sem[val%n]);
if(!sem_trywait(sem[(val+1)%n]))
break;
else
sem_post(sem[val%n]);
}
printf(“%d Eating\n”,val+1);
sleep(2);
sem_post(sem[val%n]);
sem_post(sem[(val+1)%n]);
printf(“%d Finished Eating\n”,val+1);
}
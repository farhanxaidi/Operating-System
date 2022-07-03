#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include <semaphore.h>
 

sem_t chopsticks[5];


void* dinning (void* ptr)
{
	int i = (int)(long) ptr;

	if(i%2==0)
		{
		sem_wait(&chopsticks[i]); usleep(1*1000*1000); 
		sem_wait(&chopsticks[(i+1)%5]);
		}
	else
		{
		sem_wait(&chopsticks[(i+1)%5]); usleep(1*1000*1000); 
		sem_wait(&chopsticks[i]);
		}
	printf("Philosopher %d is eating\n ",i);
	usleep(2000000);
	sem_post(&chopsticks[i]);
	sem_post(&chopsticks[(i+1)%5]);	
	printf("Philosopher %d is thinking\n ",i);
	pthread_exit(0);	
}
int main()
{
pthread_t pid[5];
for(int i=0;i<5;i++)
		sem_init(&chopsticks[i], 0, 1);


for(int i=0;i<5;i++)
	pthread_create(&pid[i],NULL,&dinning,(void*)((long)i));

for(int i=0;i<5;i++)
	pthread_join(pid[i],NULL);

return 0;
}
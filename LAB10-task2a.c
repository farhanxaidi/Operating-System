#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include <semaphore.h>
 

sem_t chopsticks[5],mutex,mut;
int m,n;

void* dinning (void* ptr)
{
	int i = (int)((long) ptr);
	do
	{
		sem_getvalue(&chopsticks[(i+1)%5],&m);
		sem_getvalue(&chopsticks[i],&n);
		sem_wait(&mut);
		if(m&n) 
		{	
			sem_wait(&mutex);
				
			break;
		}
		else
			sem_post(&mut);
		usleep(1*1000*1000);	
	}
	while(m==0 || n==0); //wait while adjacent philosphers are eating
	
	sem_wait(&chopsticks[i]); //usleep(1*1000*1000); //adding delay for deadlock temptation. 
	sem_wait(&chopsticks[(i+1)%5]);
	sem_post(&mutex);
	sem_post(&mut);
	printf("Philosopher %d is eating\n ",i);
	usleep(5*1000*1000); //eat slowly
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
	sem_init(&mutex, 0, 1);
	sem_init(&mut, 0, 1);

	for(int i=0;i<5;i++)
		pthread_create(&pid[i],NULL,&dinning,(void*)((long)i));

	for(int i=0;i<5;i++)
		pthread_join(pid[i],NULL);

	return 0;
}
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include <semaphore.h>
 

sem_t chopsticks[5],mutex;


void* dinning (void* ptr)
{
	int i = (int)(long) ptr;
	sem_wait(&mutex);
	sem_wait(&chopsticks[i]); usleep(1*1000*1000); //adding delay for deadlock temptation. 
	sem_wait(&chopsticks[(i+1)%5]);
	sem_post(&mutex);
	printf("Philosopher %d is eating\n ",i);
	usleep(5*1000*1000);
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

for(int i=0;i<5;i++)
	pthread_create(&pid[i],NULL,&dinning,(void*)((long)i));

for(int i=0;i<5;i++)
	pthread_join(pid[i],NULL);

return 0;
}
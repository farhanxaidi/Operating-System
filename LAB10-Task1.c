#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include <unistd.h> 

#define Phil_left (Phil_number + 4) % number 
#define Phil_right (Phil_number + 1) % number 
#define hung 1 
#define eat 0 
#define number 5 
#define think 2 

int Phil_Status[number]; 
int Phil_Array[number] = {0,1,2,3,4}; 
sem_t mutex; 
sem_t semaphore[number]; 

void Check(int Phil_number) 
{ 
	if (Phil_Status[Phil_number] == hung && Phil_Status[Phil_left] != eat && Phil_Status[Phil_right] != eat)
	{ 
		Phil_Status[Phil_number] = eat; 
		sleep(2); 
		printf("Philosopher %d Is Picking The fork %d and %d\n",Phil_number + 1, Phil_left + 1, Phil_number + 1); 
		printf("Philosopher %d is Eating\n", Phil_number + 1); 
		sem_post(&semaphore[Phil_number]); 
	} 
} 

void PickFork(int Phil_number) 
{
	sem_wait(&mutex); 
	Phil_Status[Phil_number] = hung; 
	printf("Philosopher %d is Hungry\n", Phil_number + 1); 
	Check(Phil_number); 
	sem_post(&mutex); 
	sem_wait(&semaphore[Phil_number]); 
	sleep(1); 
}

void ReleaseFork(int Phil_number) 
{
	sem_wait(&mutex); 
	Phil_Status[Phil_number] = think;
	printf("Philosopher %d is put Down The fork %d and %d down\n",Phil_number + 1, Phil_left + 1, Phil_number + 1); 
	printf("Philosopher %d is thinking\n", Phil_number + 1); 
	Check(Phil_left); 
	Check(Phil_right); 
	sem_post(&mutex); 
} 

void *Phil(void *num) 
{ 
	while (1)
	{ 
		int *i = num; 
		sleep(1); 
		PickFork(*i); 
		sleep(0); 
		ReleaseFork(*i); 
	} 
} 

int main() 
{ 
	int i; 
	pthread_t thread_id[number]; 
	sem_init(&mutex, 0, 1); 

	for (i = 0; i < number; i++) 
	{
		sem_init(&semaphore[i], 0, 0); 
	}

	for (i = 0; i < number; i++)
	{
		pthread_create(&thread_id[i], NULL, Phil, &Phil_Array[i]);
		printf("Philosopher %d is thinking\n", i + 1); 
	} 
	for (i = 0; i < number; i++) 
	{
		pthread_join(thread_id[i], NULL); 
	}
}

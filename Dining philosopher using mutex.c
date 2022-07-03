#include <stdio.h> 
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NO_OF_PHILOSOPHERS 5

pthread_t philosophers[NO_OF_PHILOSOPHERS];
pthread_mutex_t mutex_forks = PTHREAD_MUTEX_INITIALIZER;; 
int forks[NO_OF_PHILOSOPHERS];

void init()
{
    int i;
    for(i=0; i<NO_OF_PHILOSOPHERS; i++)
        forks[i] = 0;
}

void philosopher(int i)
{
    int right = i;
    int left = (i - 1 == -1) ? NO_OF_PHILOSOPHERS - 1 : (i - 1);
        int locked;
    while(1)
    {
            locked = 0;
            while(!locked)
            {
                pthread_mutex_lock(&mutex_forks);
                if(forks[right] || forks[left])
                {
                    pthread_mutex_unlock(&mutex_forks);     // give up the forks unless you can take both at once.
                    printf("Philosopher %d cannot take forks. Giving up and thinking.\n",i); 
                    usleep(random() % 1000); // think. 
                    continue;
                }
                forks[right] = 1; // take forks.
                forks[left] = 1;

                pthread_mutex_unlock(&mutex_forks);
                locked = 1; 
            }

        printf("Philosopher %d took both forks. Now eating :)\n",i);
        usleep(random() % 500);
        printf("Philosopher %d done with eating. Giving up forks.\n",i);
        pthread_mutex_lock(&mutex_forks); // give up forks. 
        forks[right] = 0;
        forks[left] = 0;
        pthread_mutex_unlock(&mutex_forks);
        usleep(random() % 1000);
    }

}

int main()
{
    init();
    int i;
    for(i=0; i<NO_OF_PHILOSOPHERS; i++)
        pthread_create( &philosophers[i], NULL, philosopher, (void*)i);
    for(i=0; i<NO_OF_PHILOSOPHERS; i++)
        pthread_join(philosophers[i],NULL);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int buf[256];
int in = 0;
int out = 0;
sem_t full;
sem_t empty;
sem_t mutex;
int buf_size;
int counter = 0;

void *producer(void *arg)
{
    int i, item, *index;
    index = (int *)arg;
    for (i = 0;; i++)
    {
        item = 1000 + i;
        sem_wait(&empty);
        sem_wait(&mutex);
        buf[in] = item;
        in = (in + 1) % (*index);
        counter++;
        printf("\n%d [P%d] ", item, *index);
        sem_post(&mutex);
        sem_post(&full);
        /* if (i % 5 == 0)
            sleep(1); */
    }
}

void *consumer(void *arg)
{
    int i, item, *index;
    index = (int *)arg;
    for (i = 0;;i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        item = buf[out];
        out = (out + 1) % (*index);
        counter--;
        printf("\n%d [C%d] ", item, *index);
        sem_post(&mutex);
        sem_post(&empty);
        /* if (i % 5 == 0)
            sleep(1); */
    }
}

int main()
{
    int produce, consume;
    int i;
    printf("\nThe Buffer Size:");
    scanf("%d", &buf_size);
    printf("\nThe Producer:");
    scanf("%d", &produce);
    printf("\nThe Consumer:");
    scanf("%d", &consume);
    pthread_t prod, cons;
    void* exit_status;
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, buf_size);
    sem_init(&mutex, 0, 1);
    for (i = 0; i < produce; i++)
    {
        pthread_create(&prod, NULL, producer, &i);
    }
    for (i = 0; i < consume; i++)
    {
        pthread_create(&cons, NULL, consumer, &i);
    }
    pthread_join(prod, &exit_status);
    pthread_join(cons, &exit_status);
    // pthread_exit(NULL);
    return 0;
}
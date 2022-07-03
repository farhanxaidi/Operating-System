#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

#define BUFF_SIZE 4
#define FULL 0
#define EMPTY 0
char buffer[BUFF_SIZE];
int nextIn = 0;
int nextOut = 0;

sem_t empty_sem_mutex; //producer semaphore
sem_t full_sem_mutex; //consumer semaphore

void Put(char item)
{
  int value;
  sem_wait(&empty_sem_mutex); //get the mutex to fill the buffer

  buffer[nextIn] = item;
  nextIn = (nextIn + 1) % BUFF_SIZE;
  printf("Producing %c ...nextIn %d..Ascii=%d\n",item,nextIn,item);
  if(nextIn==FULL)
    {
      sem_post(&full_sem_mutex);
      sleep(1);
    }
  sem_post(&empty_sem_mutex);

}

void * Producer()
{
  int i;
  for(i = 0; i < 10; i++)
    {
      Put((char)('A'+ i % 26));
    }
}

void Get()
{
  int item;

  sem_wait(&full_sem_mutex); // gain the mutex to consume from buffer

  item = buffer[nextOut];
  nextOut = (nextOut + 1) % BUFF_SIZE;
  printf("\t...Consuming %c ...nextOut %d..Ascii=%d\n",item,nextOut,item);
  if(nextOut==EMPTY) //its empty
    {
      sleep(1);
    }

  sem_post(&full_sem_mutex);
}

void * Consumer()
{
  int i;
  for(i = 0; i < 10; i++)
    {
      Get();
    }
}

int main()
{
  pthread_t ptid,ctid;
  //initialize the semaphores

  sem_init(&empty_sem_mutex,0,1);
  sem_init(&full_sem_mutex,0,0);

  //creating producer and consumer threads

  if(pthread_create(&ptid, NULL,Producer, NULL))
    {
      printf("\n ERROR creating thread 1");
      exit(1);
    }

  if(pthread_create(&ctid, NULL,Consumer, NULL))
    {
      printf("\n ERROR creating thread 2");
      exit(1);
    }

  if(pthread_join(ptid, NULL)) /* wait for the producer to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

  if(pthread_join(ctid, NULL)) /* wait for consumer to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

  sem_destroy(&empty_sem_mutex);
  sem_destroy(&full_sem_mutex);

  //exit the main thread

  pthread_exit(NULL);
  return 1;
}
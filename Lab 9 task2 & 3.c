#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
//*******************************************************************
long compare_and_set(long *flag, long expected, long new);
	asm(  /* compile with 64-bit compiler*/
	"compare_and_set:;"
	"movq %rsi,%rax;"
	"lock cmpxchgq %rdx,(%rdi);"
	"retq;"
	);
long _flag=0, _expected=0, _new=1; 
void wait(int *s)
{
while(*s <= 0);
while(compare_and_set(&_flag,_expected,_new)!=0);
(*s)--; //printf("wait function %d",*s);
_flag=0;
}	
void signal(int *s)
{
while(compare_and_set(&_flag,_expected,_new)!=0);
(*s)++; //printf("Signal function %d",*s);
_flag=0;
}	
//*******************************************************************


int n=10; int buffer[10];
int in=0, out=0; 
int empty=10,full=0;

void* producer (void* ptr)
{
	
	for(unsigned int i=1;i<8;i++)
	{
		wait(&empty);
		buffer[in]=i;
		in=(in+1)%n; 
		signal(&full);
	}		
	pthread_exit(0);
}

void* consumer (void* ptr)
{
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
	
	while(1)
	{
		wait(&full); /* check if there is new data*/
		printf("%d\n",buffer[out]); /*print that data*/
		
		out=(out+1)%n; /*increment counter */
		signal(&empty); /* create vacancy */
		
	}
	pthread_exit(0);	
}
int main()
{
pthread_t pid1,pid2;

pthread_create(&pid2,NULL,&consumer,NULL);
pthread_create(&pid1,NULL,&producer,NULL);
pthread_join(pid1,NULL);
usleep(2*1000*1000); //delay of 2 seconds
pthread_cancel(pid2); //cancel consumer thread


return 0;
}
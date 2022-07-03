#include<stdio.h>
#include<pthread.h>

long compare_and_set(long *flag, long expected, long new);
	asm(  /* compile with 64-bit compiler*/
	"compare_and_set:;"
	"movq %rsi,%rax;"
	"lock cmpxchgq %rdx,(%rdi);"
	"retq;"
	);

int d=11;
int produce_data()
{	
		return d++;
}
void consume_data(int data)
{
	printf("%d\n",data);
}

int n=10;
long count=0, flag=0, expected=0, new=1; 
int in=0, out=0; int buffer[10];
void* producer (void* ptr)
{
	for(unsigned int i=0;i<20;i++)
	{
		
		while(count==n);
		buffer[in]=produce_data();
		in=(in+1)%n;
		while(compare_and_set(&flag,expected,new)!=0);
		count++; 
		flag=0;
	}		
	pthread_exit(0);
}
void* consumer (void* ptr)
{
	for(unsigned int i=0;i<20;i++)
	{
		while(count==0);
		consume_data(buffer[out]);
		out=(out+1)%n;
		while(compare_and_set(&flag,expected,new)!=0);
		count--; 
		flag=0;
	}
	pthread_exit(0);	
}
int main()
{
count = 0;
pthread_t pid1,pid2;

pthread_create(&pid1,NULL,&producer,NULL);
pthread_create(&pid2,NULL,&consumer,NULL);

pthread_join(pid1,NULL);
pthread_join(pid2,NULL);

return 0;
}
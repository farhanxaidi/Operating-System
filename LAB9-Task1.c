#include<pthread.h>
#include<stdio.h>
#define BUF_SIZE 10

long compare_and_set(long *flag, long expected, long new);
asm( /* compile with 64-bit compiler*/
"compare_and_set:;"
"movq %rsi,%rax;"
"lock cmpxchgq %rdx,(%rdi);"
"retq;"
);

int buffer[1000];
long counter, flag=0, expected=0, new=1;
int in,out=0;

void *increment (void *ptr)
{
	for(int i=0;i<BUF_SIZE;i++) 
	{
	     while(compare_and_set(&flag,expected,new)!=0);
{
			while (counter == BUF_SIZE );
{			
				buffer[in] = i;
                		printf("Initial value of Next Producer %d \n",buffer[in]);
				in = (in + 1) % BUF_SIZE ;
				counter++;
                		flag=0;
}
}
	}
	
	pthread_exit(0);
}

int Consumed=0;

void *decrement (void *ptr)
{
	for(int i=0;i<BUF_SIZE;i++ )
	{
	    while(compare_and_set(&flag,expected,new)!=0);
{	
		while (counter == 0 );
{
			Consumed = buffer[out];
			printf("Initial value of Next Consumed %d \n",Consumed);
			out = (out + 1) % BUF_SIZE ;
			counter--;
	                flag=0;
} 
}
	}
	pthread_exit(0);
}

int main()
{
	counter = 100;
	pthread_t pid1,pid2;

	printf("\nInitial value of Count is %ld \n\n",counter);
	pthread_create(&pid1,NULL,&increment,NULL);
	pthread_create(&pid2,NULL,&decrement,NULL);
	pthread_join(pid1,NULL);
	pthread_join(pid2,NULL);
	printf("\nFinal value of Count is %ld \n\n",counter);

	return 0;
}

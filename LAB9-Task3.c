#include<stdio.h>
#include<pthread.h>



long compare_and_set(long *flag, long expected, long new);
asm( /* compile with 64-bit compiler*/
"compare_and_set:;"
"movq %rsi,%rax;"
"lock cmpxchgq %rdx,(%rdi);"
"retq;"
);
int  BUFSIZE= 10;
int buffer[100];
long counter, flag=0, expected=0, new=1;
int in,out;
void busywait(long*S)
{
	while(compare_and_set(&flag,expected,new)!=0);
	while (S <= 0 ); 
	{}
	(*S)--;

}

void signal(long*S)
{
	while(compare_and_set(&flag,expected,new)!=0);
 	(*S)++;
}

void* increment (void* ptr)
{

	for(int i=0;i<10;i++) 
	{
	      
		while (counter == BUFSIZE );
		buffer[in] = i;
                printf("inital value of next producer %d\n",buffer[in]);
		in = (in + 1) % BUFSIZE ;
		long* temp1=&counter;
                 signal(temp1);
                
               
                flag=0;
	}

pthread_exit(0);
}

int nextconsumed=0;
void* decrement (void* ptr)
{

	for(int i=0;i<10;i++ )
	{
	   
		while (counter == 0 );
		nextconsumed = buffer[out];
		printf("inital value of next consumed %d\n ",nextconsumed);
		out = (out + 1) % BUFSIZE ;
                long* temp1=&counter;
                
                busywait(temp1);
		
                flag=0;
	}

pthread_exit(0);

}





int main()
{
counter = 0;
pthread_t pid1,pid2;
printf("\nInitial value of Count is %ld\n ",counter);
pthread_create(&pid1,NULL,&increment,NULL);
pthread_create(&pid2,NULL,&decrement,NULL);
pthread_join(pid1,NULL);
pthread_join(pid2,NULL);
printf("\nFinal value of Count is %ld \n ",counter);

printf("\nIs it correct? \n");
return 0;
}





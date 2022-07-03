#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define FORK_CALLS 2
#define PROCESS 5
#define VALUE 5

int main()
{
	pid_t pid;

	int matrix1[VALUE][VALUE];
	int matrix2[VALUE][VALUE];
	int resultant[VALUE][VALUE];

	int val;
	int *p;
		  
	p=0;
 
	val = shmget(IPC_PRIVATE, sizeof(int)*(VALUE*VALUE)*3, IPC_CREAT|0666);
	p = (int*) shmat(val, NULL,0);

	for(int i=0;i<VALUE;i++)
	{ 
		for(int j=0;j<VALUE;j++)
		{
			matrix1[i][j]=i+j;
			matrix2[i][j]=i+3;
		}
	}

	for(int i=0;i<VALUE;i++)
	{
	    pid=fork();
	}

	if(pid<0)
	{
		fprintf(stderr,"Fork Failed");
		return 1;
	}
	else if(pid==0)
	{
		int s=(*p*VALUE)/PROCESS;
		int e=((*p+1)*VALUE)/PROCESS;

		for(int i=s;i<e;i++)
		{
			for(int j=0;j<VALUE;j++)
			{
				resultant[i][j]=0;
				for(int k=0;k<VALUE;k++)
				{
					resultant[i][j] += matrix1[i][k] * matrix2[k][j];
				}
			}
		}
	}
	else
	{
		printf("Matrix 1: \n ");

		for(int i=0;i<VALUE;i++)
		{
			for(int j=0;j<VALUE;j++)
			{
				printf("%d ",matrix1[i][j]);
			}
		}

		printf("\n");
		printf("Matrix 2: \n ");

		for(int i=0;i<VALUE;i++)
		{
			for(int j=0;j<VALUE;j++)
			{
				printf("%d ",matrix2[i][j]);
			}
		}

		printf("\n");
		printf("Result: \n");

		for(int i=0;i<VALUE;i++)
		{
			for(int j=0;j<VALUE;j++)
			{
				printf("%d ",resultant[i][j]);
			}
		}
		printf("\n");
	}
	return 0;
}

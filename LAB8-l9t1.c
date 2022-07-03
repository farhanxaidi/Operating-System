#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#define MATRIX_TH 5
#define VALUE 5

int matrix1[VALUE][VALUE];
int matrix2[VALUE][VALUE];
int resultant[VALUE][VALUE];

int val=0;

void *multiplication(void *v)
{
	int m = val++;

	for (int i = m * VALUE / 4; i < (m + 1) * VALUE / 4; i++)
	{
		for (int j = 0; j < VALUE; j++)
		{
			for (int k = 0; k < VALUE; k++)
			{
				resultant[i][j] =resultant[i][j] + matrix1[i][k] * matrix2[k][j];
			}
		}
	}
	return 0;
}

int main()
{
	for(int i=0;i<VALUE;i++)
	{
		for(int j=0;j<VALUE;j++)
		{
			matrix1[i][j]=rand()%10;
			matrix2[i][j]=rand()%10;
		}
	}

	printf("Matrix 1: \n");

	for(int i=0;i<VALUE;i++)
	{
		for(int j=0;j<VALUE;j++)
		{
			printf("%d ",matrix1[i][j]);
		}
	}
	
	printf(" \n ");
	printf("Matrix 2: \n");

	for(int i=0;i<VALUE;i++)
	{
		for(int j=0;j<VALUE;j++)
		{
			printf("%d ",matrix2[i][j]);
		}
	}

	pthread_t th[MATRIX_TH];

	for(int i=0;i<MATRIX_TH;i++)
	{
		int *p=NULL;
		pthread_create(&th[i],NULL,multiplication,(void*)(p));
	}
	for(int i=0;i<MATRIX_TH;i++)
	{
		pthread_join(th[i],NULL);
	}
	
	printf(" \n ");
	printf("Result: \n");

	for(int i=0;i<VALUE;i++)
	{
		for(int j=0;j<VALUE;j++)
		{
			printf("%d ",resultant[i][j]);
		}
	}
	printf(" \n ");

	return 0;
}

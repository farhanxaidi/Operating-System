#define _GNU_SOURCE
#include<stdlib.h>
#include <unistd.h>
#include<stdio.h>
#include <sys/sysinfo.h>
#include<sched.h>

int main(int argc,char **argv)
{

	cpu_set_t mask;

	int array[argc-1];
	int minimum;
	int maximum;
	float average=0;

	for(int i=0;i<argc-1;i++)
	{
		array[i]= atoi(argv[i+1]);
	}

	minimum = array[0];
	maximum = array[0];

	int c1,c2,c3;
	c1=fork();

	if(c1==0)
	{
		CPU_ZERO(&mask);
		CPU_SET(0, &mask);
		sched_setaffinity(0, sizeof(cpu_set_t), &mask);

		printf("\nThis process is currently running on processor # %d\n",sched_getcpu());
		
		for(int i=0; i<argc-1; i++)
    		{
		        for(int j=i+1; j<argc-1; j++)
 		       {
				if(array[i] > array[j])
            			{
                			int temp = array[i];
                			array[i] = array[j];
                			array[j] = temp;
            			}
        		}
    		}

		printf("\nSorted arrayay = ");

		for(int i=0; i<argc-1; i++)
	   	{
			printf("%d ",array[i]);
		}
			printf("\n");
	}
	else
	{	
		int sum=0;
		c2=fork();

		if(c2==0)
		{
			CPU_ZERO(&mask);
			CPU_SET(1, &mask);
			sched_setaffinity(0, sizeof(cpu_set_t), &mask);

			printf("\nThis process is currently running on processor # %d\n",sched_getcpu());

			for(int i=0; i<argc-1; i++)
    			{
				sum+=array[i];		        
        		}
			average=sum/(argc-1);
			printf("\nAverage is = %f \n",average);			
		}
		else
		{
			c3=fork();
			if(c3==0)
			{
				CPU_ZERO(&mask);
				CPU_SET(2, &mask);
				sched_setaffinity(0, sizeof(cpu_set_t), &mask);
				printf("\nThis process is currently running on processor # %d\n",sched_getcpu());
				for(int i=0; i<argc-1; i++)
    				{
					if(minimum>array[i])
					{
						minimum=array[i];
					}
					if(maximum<array[i])
					{
						maximum=array[i];
					}		        
        			}
				printf("Maximumimum is =  %d \n",maximum);
				printf("Minimumimum is  = %d \n",minimum);
				
			}
		}
	}	
}

#define _GNU_SOURCE
#include<sched.h>
#include<stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>

int main ()
{

	cpu_set_t my_set;
	
	CPU_ZERO(&my_set);

	int proc = get_nprocs();
	for( int i =0;i< proc;i++)
	{
		printf("Processor %d = %d \n",i,CPU_ISSET(i,&my_set));
	}

	int userCPU = 0;
	printf("\nEnter CPU:\t");
	scanf("%d",&userCPU);
	
	CPU_ZERO(&my_set);
	CPU_SET(userCPU,&my_set); 
	sched_setaffinity(0, sizeof(cpu_set_t), &my_set);
	
	for (int i = 0; i < get_nprocs(); i++)
		printf("Processor %d = %d \n",i,CPU_ISSET(i,&my_set));



	char * command;
	printf("\nEnter Command:\t");
	scanf("%s",command);
	execlp(command,command,NULL);


	return 0;


}

#define _GNU_SOURCE
#include<sched.h>
#include<stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>

int main(void) 
{
	int value; 

	printf("\nThis process is currently running on processor # %d \n",sched_getcpu());

	cpu_set_t mask;

	int nproc = get_nprocs_conf();

	sched_getaffinity(0, sizeof(cpu_set_t), &mask);

	printf("\nCurrent Affinity is\n");
	for (int i = 0; i < nproc; i++)

		printf("\nProcessor %d = %d \n",i,CPU_ISSET(i, &mask));
	
	printf("\nEnter Processer You Want to Set : ");

	scanf("%d",&value);
	
	CPU_ZERO(&mask);
	CPU_SET(value, &mask);
	sched_setaffinity(0, sizeof(cpu_set_t), &mask);
	printf("\n\nNew Affinity is\n");
	sched_getaffinity(0, sizeof(cpu_set_t), &mask);

	for (int i = 0; i < nproc; i++)

		printf("\nProcessor %d = %d \n",i,CPU_ISSET(i, &mask));
	
	printf("\nThis process is currently running on processor # %d \n\n",sched_getcpu());
	execlp("ls","ls",NULL);

}

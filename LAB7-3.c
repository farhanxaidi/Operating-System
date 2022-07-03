#define _GNU_SOURCE
#include<sched.h>
#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <sys/wait.h>
int main()
{
long int nsteps = 10000000; double x;
double dx = 1.0 / nsteps;
double pi = 0.0;
int msg1[2];
int msg2[2];
int msg3[2];

pipe(msg1);
pipe(msg2);
pipe(msg3);


int forkSt1=fork();
int forkSt2=fork();

if(forkSt1>0 && forkSt2>0) //Parent
{
    close(msg1[1]);
    close(msg2[1]);
    close(msg3[1]);
    cpu_set_t mainset;
    CPU_ZERO(&mainset);
    CPU_SET(0,&mainset);
    sched_setaffinity(0,sizeof(cpu_set_t),&mainset);

    for(long int i=0;i<2500000;i++)
    {
        x = (i + 0.5) * dx;
        pi += 4.0 / (1.0 + x * x);
    }
    pi *= dx;

    printf("\nValue from CPU 0 : %lf:\n",pi);
    double piMsg1,piMsg2,piMsg3;
    read(msg1[0],&piMsg1,sizeof(double));
    close(msg1[0]);
    read(msg2[0],&piMsg2,sizeof(double));
    close(msg2[0]);
    read(msg3[0],&piMsg3,sizeof(double));
    close(msg3[0]);
    
    pi+=piMsg1+piMsg2+piMsg3;
    printf("\nFinal Pi Value Calculated : %lf\n",pi);
}
else if(forkSt1>0 && forkSt2==0)
{
    close(msg1[0]);
    close(msg2[1]);
    close(msg3[1]);
    close(msg2[0]);
    close(msg3[0]);

    cpu_set_t ch1set;
    CPU_ZERO(&ch1set);
    CPU_SET(1,&ch1set);
    sched_setaffinity(0,sizeof(cpu_set_t),&ch1set);

    for(long int i=2500000;i<5000000;i++)
    {
        x = (i + 0.5) * dx;
        pi += 4.0 / (1.0 + x * x);
    }
    pi *= dx;

    printf("\nValue from CPU 1 : %lf:\n",pi);
    write(msg1[1],&pi,sizeof(double));
    close(msg1[1]);

}
else if(forkSt1==0 && forkSt2>0)
{
    close(msg2[0]);
    close(msg1[1]);
    close(msg3[1]);
    close(msg1[0]);
    close(msg3[0]);

    cpu_set_t ch2set;
    CPU_ZERO(&ch2set);
    CPU_SET(2,&ch2set);
    sched_setaffinity(0,sizeof(cpu_set_t),&ch2set);

    for(long int i=5000000;i<7500000;i++)
    {
        x = (i + 0.5) * dx;
        pi += 4.0 / (1.0 + x * x);
    }
    pi *= dx;
    printf("\nValue from CPU 2 :%lf:\n",pi);
    write(msg2[1],&pi,sizeof(double));
    close(msg2[1]);

    

}
else if(forkSt1==0 && forkSt2==0)
{
    close(msg3[0]);
    close(msg2[1]);
    close(msg1[1]);
    close(msg2[0]);
    close(msg1[0]);

    cpu_set_t ch3set;
    CPU_ZERO(&ch3set);
    CPU_SET(3,&ch3set);
    sched_setaffinity(0,sizeof(cpu_set_t),&ch3set);

    for(long int i=7500000;i<10000000;i++)
    {
        x = (i + 0.5) * dx;
        pi += 4.0 / (1.0 + x * x);
    }
    pi *= dx;

    printf("\nValue from CPU 3 :%lf:\n",pi);
    write(msg3[1],&pi,sizeof(double));
    close(msg3[1]);

    
}

return 0;
}


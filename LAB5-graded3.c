#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/wait.h>
#define RD 0
#define WR 1
void bubbleSort(int array[], int size);
void printArray(int array[], int size);


int main(int argc,char * argv[])
{
		int a2[2];
		int check=pipe(a2);                                               int a11[2];pipe(a11);   int a22[2]; pipe(a22);
        int sd[2];
        pipe(sd);
		if(check==0)
		{
			printf("Pipe creation  \n");
		}
		else
		{
			printf("Pipe creation failed \n");
		}
	int a[2];
	int arry[100]={0};
    //int arry2[100]={0};
	int count=argc-1;
	int child_arry[100];
	int val=pipe(a);
			for(int i=0;i<argc-1;i++)
			{
				arry[i]= atoi(argv[i+1]);
			}
		

	//             divide=ing arrys     
	int half =count/2;
	int half2=count - half;
	int * ch1_arry =(int *) malloc (half *sizeof(int));
	int * ch2_arry =(int *) malloc (half2 *sizeof(int));
			printf("1st half \n");
			for(int i=0;i<half;i++)
			{
				ch1_arry[i]=arry[i];
			}
			printArray(ch1_arry,half);
			int j=0;
			printf("2st half \n");
			for(int i=half;i<count;i++)
			{
				ch2_arry[j]=arry[i];
				j++;
			}
			printArray(ch2_arry,half2);
	
	if(val==0)
	{
		printf("Pipe created \n");
		pid_t pid=fork();
		if(pid==0)// child 1
		{
			printf("child 1\n");
			close(a[WR]);
			read(a[RD],child_arry,sizeof(int)*100);
			close(a[RD]);
			for(int i=0;i<half;i++)
			{
				printf("At index %d : %d \n",i,child_arry[i]);
			}
			printf("sortted 1 \n");
			bubbleSort(child_arry,half);
			printf("min after ch1 sorted : %d \n",child_arry[0]);
			printf("child sending\n");
			close(a11[RD]);//
			write(a11[WR],child_arry,sizeof(int)*100);
			close(a11[RD]);
            int x;
            read(sd[RD],&x,sizeof(int));
			//printf("---------     END    ---------\n");
				printf("---------     child * Termination    ---------\n");
			
		/*    */
		}
		else if(pid>1)
		{	
			pid_t pid2=fork();
			if(pid2==0) //child 2
			{	int child_arry2 [100];
				printf("child 2 \n");					
					close(a2[WR]);
					read(a2[RD],child_arry2,sizeof(int)*100);
					close(a2[RD]);
					for(int i=0;i<half2;i++)
					{
						printf("At index %d : %d \n",i,child_arry2[i]);
					}
					printf("sortted 2 \n");
					bubbleSort(child_arry2,half);
					printf("min after ch2 sorted : %d \n",child_arry2[0]);
					printf("child 2 sending\n");
					close(a22[RD]);//
					write(a22[WR],child_arry2,sizeof(int)*100);
					close(a22[RD]);
                    int x;
                    read(sd[RD],&x,sizeof(int));
                  //   printf("---------     END    ---------\n");
				printf("---------     child Termination    ---------\n");
			}
			else if(pid2>1)
			{
				printf("parent \n");
				close(a[RD]);
				write ( a[WR], ch1_arry, sizeof(int)*100) ;
				close(a[WR]);	
				printf("sending to child1 \n");

				close(a2[RD]);
				write ( a2[WR], ch2_arry, sizeof(int)*100) ;
				close(a2[WR]);
				printf("sending to child2 \n");

					////////////
					//wait(NULL); // 
				/*int v1=0;
				close(a[WR]);
				read(a[RD],ch1_arry,sizeof(int)*100);
				close(a[RD]);
				printf("child 1 send to parent\n");
				printf("Mini from ch1 : %d \n",ch1_arry[0]);


				close(a2[WR]);
				read(a2[RD],ch2_arry,sizeof(int)*100);
				close(a2[RD]);
				printf("child 2 send to parent\n");
				printf("Mini from ch2 : %d \n",ch2_arry[0]);
				printf("---------     END    ---------\n");
				printf("---------     Parent Termination    ---------\n");*/
				close(a11[WR]);
				read(a11[RD],ch1_arry,sizeof(int)*100);
				close(a11[RD]);
				printf("child 1 send to parent\n");
				printf("Mini from ch1 : %d \n",ch1_arry[0]);


				close(a22[WR]);
				read(a22[RD],ch2_arry,sizeof(int)*100);
				close(a22[RD]);
				printf("child 2 send to parent\n");
				printf("Mini from ch2 : %d \n",ch2_arry[0]);
                int signal=0;
                while(signal!=1)
                {
                    printf("enter  digit **  1  ** end child \n");
                    scanf("%d",&signal);  
                    if(signal==1)
                    {
                        break;
                    }
                    else
                    {
                        printf(" again \n");
                    }
                    
                }
                        
                    printf("***************** \n");      
                    write(sd[WR],&signal,sizeof(int)*100);
                    sleep(1/2);
                     printf("parent ending \n");
				printf("---------     END    ---------\n");
				printf("---------     Parent Termination    ---------\n");

			}
			
		}
	}
	else
	{
		printf("Pipe creation failed \n");
	}
	//printArray()
	return 0;

}
void bubbleSort(int array[], int size)
{
  for (int step = 0; step < size - 1; ++step)
  {
    for (int i = 0; i < size - step - 1; ++i)
    {
      // To sort in descending order, change">" to "<".
      if (array[i] > array[i + 1])
      {
        int temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
      }
    }
  }
}

void printArray(int array[], int size)
{
  for (int i = 0; i < size; ++i)
  {
    printf("At index %d : %d \n",i, array[i]);
  }
  printf("\n");
}

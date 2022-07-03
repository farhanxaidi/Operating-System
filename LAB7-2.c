#define _GNU_SOURCE
#include<sched.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/sysinfo.h>
#include<sys/wait.h>
#include<stdlib.h>
/* These new things will be used in this program
1.cpu_set_t mask; This is the affinity mask to be used later(4 byte size)
2.CPU_ZERO(&mask); This will making all the bits of Affinity mask to zero(No Cpu is set) 
3.CPU_SET(2,&mask); This is the setting the 3rd bit of Affinity mask(Cpu 2 will be set) 
4.sched_setaffinity(getpid(),sizeof(cpu_set_t),&mask);// This process will have it's affinity
set to Cpu Number 2 as we set it's third bit earlier
5.printf("The processor# of this Process is:: %d\n",sched_getcpu()); This will be display 
the Processor Number upon which the current process is running
*/
void average(int*,int);
void minMax(int*,int);
void sorting(int*,int);
int main(int argc,char* argv[]){

 if(argc == 1 ){
   printf("Error! User input is missing! \n");
 }
 else{
     int* arr;
     arr=(int*) malloc((argc-1)*sizeof(int));
     for(int i=1;i<argc;i++){
         arr[i-1]=atoi(argv[i]);
     }
     pid_t pid;
     pid=fork();
     if(pid < 0){
        printf("Error! Child creation failed! \n");
     }
     else if(pid == 0){
             cpu_set_t mask;
             CPU_ZERO(&mask);
             CPU_SET(0,&mask);
             sched_setaffinity(getpid(),sizeof(cpu_set_t),&mask);
             printf("The processor# of this Process is:: %d\n",sched_getcpu());
             average(arr,argc-1);        
             printf("The processor# of this Process is:: %d\n\n",sched_getcpu());
             exit(0);

     }
     else{ 
          wait(NULL);
          pid=fork();
          if(pid < 0){
             printf("Error! Child creation failed! \n");
          }
          else if(pid == 0){
                  cpu_set_t mask;
                  CPU_ZERO(&mask);
                  CPU_SET(1,&mask);
                  sched_setaffinity(getpid(),sizeof(cpu_set_t),&mask);
                  printf("The processor# of this Process is:: %d\n",sched_getcpu());
                  minMax(arr,argc-1);        
                  printf("The processor# of this Process is:: %d\n\n",sched_getcpu());
                  exit(0);

         }
         else{ 
              wait(NULL);
              pid=fork();
              if(pid < 0){
                 printf("Error! Child creation failed! \n");
              }
              else if(pid == 0){
                      cpu_set_t mask;
                      CPU_ZERO(&mask); 
                      CPU_SET(2,&mask); 
                      sched_setaffinity(getpid(),sizeof(cpu_set_t),&mask); 
                      printf("The processor# of this Process is:: %d\n",sched_getcpu());
                      sorting(arr,argc-1);        
                      printf("The processor# of this Process is:: %d\n\n",sched_getcpu());
                      exit(0);

             }
             wait(NULL);
         }
 
   }// End of Praent
  free(arr);  
 } 

 return 0;
}
/* These are three helping functions to perform tasks required by three children */
void average(int* ptr,int size){
 float average=0.0;
  for(int i=0;i<size;i++){
      average+=ptr[i];
  }
  printf("The average value is %.3f \n",average/=size);

}
void minMax(int* ptr,int size){
 int min=ptr[0],max=ptr[0];
 for(int i=1;i<size;i++){
     if(min > ptr[i]){
           min=ptr[i];
       }
     if(max < ptr[i]){
           max=ptr[i];
       }
 }
 printf("The minimum and maximum values are %d and %d.\n",min,max);
 
 
}
void sorting(int* ptr,int size){
 int temp=0;
 for(int i=0;i<size;i++){
     for(int j=i;j<size;j++){
         if(ptr[i] > ptr[j]){
            temp=ptr[i];
            ptr[i]=ptr[j];
            ptr[j]=temp; 
         }
     }
 }
 printf("Sorted list:");
 for(int i=0;i<size;i++){
    printf(" %d",ptr[i]);
 }
 printf("\n");
}

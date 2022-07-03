#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

#define READ 0
#define WRITE 1
int smallest(int arr[],int size);
int main(int argc,char* argv[]){

 int fd1[2],fd2[2];
 pid_t pid;
 if(argc > 1){
     	if(pipe(fd1) == 0 && pipe(fd2) == 0){
        	pid=fork();
        	if(pid < 0){printf("Error! Child creation failed \n");}
        	else if(pid == 0){
                	int size,small[1];
                	if((argc-1)%2 == 0){size=(argc-1)/2;}
                	else{size=((argc-1)/2)+1;}
                	int arr[size];
                	close(fd1[WRITE]);
                	read(fd1[READ],arr,sizeof(arr));
                	close(fd1[READ]);
                	close(fd2[READ]);
                	small[0]=smallest(arr,size);
                	write(fd2[WRITE],small,sizeof(small));
                	close(fd2[WRITE]);
                	exit(0);
     		}
     		else{
         		int fd11[2],fd22[2];
         		pid_t pid;
         		int size=(argc-1),firstHalf=0,secondHalf=0;
         		if((argc-1)%2 == 0){firstHalf=(argc-1)/2;}
         		else{firstHalf=((argc-1)/2)+1;}
         		secondHalf=(argc-1)-firstHalf;
         		int arr[size],arr1[firstHalf],arr2[secondHalf];
                        int first[1],second[1];
         		for(int i=0;i<size;i++){
             			arr[i]=atoi(argv[i+1]);
             			if(i<firstHalf){arr1[i]=arr[i];}
             			else{arr2[i-firstHalf]=arr[i];}
        		}
        		close(fd1[READ]);
        		write(fd1[WRITE],arr1,sizeof(arr1));
        		close(fd1[WRITE]);
        		close(fd2[WRITE]);
        		read(fd2[READ],first,sizeof(first));
        		close(fd2[READ]);
        	       if(pipe(fd11) == 0 && pipe(fd22) == 0 ){
           	         pid=fork();
           		 if(pid < 0){printf("Error! Child creation failed \n");}
           		 else if(pid == 0){
                   		int arr3[secondHalf],small[1];
                   		close(fd11[WRITE]);
                   		read(fd11[READ],arr3,sizeof(arr3));
                   		close(fd11[READ]);
                   		close(fd22[READ]);
                   		small[0]=smallest(arr3,secondHalf);
                   		write(fd22[WRITE],small,sizeof(small));
                   		close(fd22[WRITE]);
                   		exit(0);
         		}
         		else{
              			close(fd11[READ]);
              			write(fd11[WRITE],arr2,sizeof(arr2));
              			close(fd11[WRITE]);
              			close(fd22[WRITE]);
              			read(fd22[READ],second,sizeof(second));
              			close(fd22[READ]);
              			if(first[0] < second[0]){
				   printf("The smallest: %d\n",first[0]);}
              			else{printf("The smallest: %d\n",second[0]);}


        		}
        
     		  }
     		  else{printf("Error! Pipe creation failed\n");}

              }// End of Parent pid > 0	
    }// End of first Pipe creation if
    else{
      printf("Error! Pipe creation failed \n");
    }
 }
 else{printf("There was no Input by user \n");}



 return 0;
}

int smallest(int arr[],int size){

  if(size > 1){
     int small=arr[0];
     for(int i=1;i<size;i++){
         if(small > arr[i]){small=arr[i];}
     } return small;
  }
  return arr[0];
}

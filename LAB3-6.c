#include<stdio.h>
#include<stdlib.h>

int main(int argc,char* argv[]){

 if(argc > 1){
    int* arr=(int*) malloc((argc-1)*sizeof(int));
    int i;
    for(i=1;i<argc;i++){
        arr[i-1]=atoi(argv[i]);
    }
    int max=-9999;
    for(i=0;i<(argc-1);i++){
        if(max<arr[i]){ 
           max=arr[i];
         }
    }
    printf("Output: %d\n",max);

    free(arr);
 }
 else{
      printf("No Input given by the User! \n");
 }
 
 return 0;
}

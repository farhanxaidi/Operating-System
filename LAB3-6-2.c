#include<stdio.h>
#include<stdlib.h>

int main(int argc,char* argv[]){

 if(argc == 3){
    printf("Sum:: %d\n", (atoi(argv[1])+atoi(argv[2])));
 }
 else{ 
      printf("Invalid Input! \n");
  }

 return 0;
}

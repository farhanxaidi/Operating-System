#include<stdio.h>

void primeFinder();
int main(){

 primeFinder();

 return 0;
}
void primeFinder(){
      int input=0;
      printf("Enter the number: = ");
      scanf("%d",&input);
      int i=2,checker=0,limit=input/2;
      while(i<= limit){
           if(input%i == 0){
              checker=1; 
              i=input;
           } 
      i++;
      }
      if(checker == 1){
         printf("Output: Not Prime\n");
      }
      else{
         printf("Output: Prime\n");
      }
}

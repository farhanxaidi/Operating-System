#include<stdio.h>

int primeFinder(int*);
int main(){

 int input=0;
 printf("Enter the number: = ");
 scanf("%d",&input);
 if(primeFinder(&input) == 1){
    printf("Output: Not Prime\n");
 }
 else{
      printf("Output: Prime\n");
 }

 return 0;
}
int primeFinder(int* ptr){

      int i=2,checker=0,limit=*ptr/2;
      while(i<= limit){
          if(*ptr%i == 0){
             checker=1;
             i=*ptr;
           } 
      i++;
      }
      
      return checker;
}

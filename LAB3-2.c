#include<stdio.h>


int main(){

 int obtainedMarks=0,totalMarks=0;
 printf("Enter Your Obtained Marks=");
 scanf("%d",&obtainedMarks);
 printf("Enter Total Marks=");
 scanf("%d",&totalMarks);
 int percentage=((obtainedMarks/(float)totalMarks)*100);
 if(percentage >=90 && percentage<=100){
    printf("Your Marks Percentage is=%d%c\nYour Grade is=%c\n",percentage,'%','A');
 }
 else if(percentage >=80 && percentage<90){
         printf("Your Marks Percentage is=%d%c\nYour Grade is=%c\n",percentage,'%','B');
 }
 else if(percentage >=70 && percentage<80){
         printf("Your Marks Percentage is=%d%c\nYour Grade is=%c\n",percentage,'%','C');
 }
 else if(percentage >=60 && percentage<70){
         printf("Your Marks Percentage is=%d%c\nYour Grade is=%c\n",percentage,'%','D');
 }
 else if(percentage >=50 && percentage<60){
         printf("Your Marks Percentage is=%d%c\nYour Grade is=%c\n",percentage,'%','E');
 }
 else if(percentage<50){
         printf("Your Marks Percentage is=%d%c\nYour Grade is=%c\n",percentage,'%','F');
 }
 else{
      printf("Your Input is Invalid! \n");
 }


 return 0;
}

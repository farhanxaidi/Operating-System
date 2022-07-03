#include<stdio.h>


int main(){

 int initialDeposit=0,interestRate=10;
 printf("Enter initial deposit amount= ");
 scanf("%d",&initialDeposit);
 initialDeposit+=(initialDeposit/interestRate);
 printf("Amount after 1 month = %d\n",initialDeposit);

 return 0;
}

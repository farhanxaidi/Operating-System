#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void sum(int a , int b)
{
    printf("Sum of Numbers :%d",a+b);
}
void subtract(int a , int b)
{
    printf("Sub of Numbers :%d",a-b);
}
void multiply(int a , int b)
{
    printf("Multiplication of Numbers :%d",a*b);
}
void divide(int a , int b)
{
    printf("Division of Numbers :%d",a+b);
}

int fibMain(int a)
{
    if(a==0)
    {
        return 0;
    }
    else if(a==1)
    {
        return 1;
    }
    else
        return fibMain(a-2)+fibMain(a-1);
}
void fib(int a)
{

    for(int i=0;i<a;i++)
    {
        printf("%d,",fibMain(i));
    }
    
}
void fact(int a)
{
    double ans=1;
    for(int i=1;i<=a;i++)
    {
        ans*=i;
    }
    printf("Answer : %f",ans);
}
void even(int a)
{
    if(a%2==0)
    {
        printf("Number is Even");
    }
    else
    {
        printf("Number is not Even");
    }
    
}
void odd(int a)
{
    if(a%2==1)
    {
        printf("Number is odd");
    }
    else
    {
        printf("Number is Not Odd");
    }
    
}
void prime(int a)
{
    int flag=0;
    for(int i=2;i<a/2;i++)
    {
        if(a%i==0)
        {
            flag=-1;
        }
    }
    if(flag==0)
    {
        printf("Entered Number is Prime");
    }
    else
    {
        printf("Number is Not Prime !");
    }
}
void square(int a)
{
    printf("Square of Number :%d",a*a);
}
void cube(int a)
{
    printf("Cube of Number :%d",a*a*a);

}
int main(int argc,char** argv)
{
    if (strcmp(argv[argc-1],"Sum")==0)
    {
        sum(atoi(argv[1]),atoi(argv[2]));
        printf("\n");
    }
    else if (strcmp(argv[argc-1],"Sub")==0)
    {
        subtract(atoi(argv[1]),atoi(argv[2]));
        printf("\n");
    }
    else if (strcmp(argv[argc-1],"Mul")==0)
    {
        multiply(atoi(argv[1]),atoi(argv[2]));
        printf("\n");
    }   
    else if( strcmp(argv[argc-1],"Div")==0)
    {
        divide(atoi(argv[1]),atoi(argv[2]));
        printf("\n");
    }
    else if(strcmp(argv[argc-1],"Fib")==0)
    {
        fib(atoi(argv[1]));
        printf("\n");
    }
    else if(strcmp(argv[argc-1],"Fact")==0)
    {
        fact(atoi(argv[1]));
        printf("\n");
    }
    else if( strcmp(argv[argc-1],"Even")==0)
    {
        even(atoi(argv[1]));
        printf("\n");
    } 
    else if(strcmp(argv[argc-1],"Odd")==0)
    {   odd(atoi(argv[1]));
        printf("\n");
    }
    else if(strcmp(argv[argc-1],"Prime")==0)
    {   prime(atoi(argv[1]));
        printf("\n");
    }    
    else if(strcmp(argv[argc-1],"Square")==0)
    {
        square(atoi(argv[1])); 
        printf("\n");
    }
    else if(strcmp(argv[argc-1],"Cube")==0)
    {
        cube(atoi(argv[1]));
        printf("\n");
    }
    else
    {
                printf("\n");
                printf("\nError \n");
    }

    return 0;
}
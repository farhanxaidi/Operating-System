#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char** argv)
{

    printf("\nLoading math.out ....... : \n");
    execv("math.out",argv);



    return 0;
}
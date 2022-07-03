#include<stdio.h>
#include<string.h>


struct Student{
    char name[30];
    char roll[20];
    int marks;
};

void input(struct Student*);
void output(struct Student*);

int main(){
 struct Student s1;
 input(&s1);
 output(&s1);
 

 return 0;
}
void input(struct Student* s1){

 printf("Enter Name of the Student: - ");
 scanf("%[^'\n']s",s1->name);
 printf("Enter Roll Number of the Student: - ");
 scanf("%s",s1->roll);
 printf("Enter Marks of the Student: - ");
 scanf("%d",&s1->marks);
}
void output(struct Student* s1){
 
 printf("\nName of the Student: - %s\n",s1->name);
 printf("Roll Number of the Student: - %s\n",s1->roll);
 printf("Marks of the Student: - %d\n",s1->marks);
 
}

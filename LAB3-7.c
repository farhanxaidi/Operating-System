#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Student{
 char name[20];
 char id[20];
 char gender;
 int quiz1;
 int quiz2;
 int mid;
 int final;
 int obtnMrks;
};

void printStd(struct Student);
void readData(struct Student[],int*);
void addRecord(struct Student[],int*); 
void searchById(char reg[],struct Student[],int count);
void showAllRecord(struct Student[],int count);
float average(struct Student[],int count);
void showBelowAverage(struct Student[],int count);

int main(){
 struct Student s1[100];
 int count=0,checker=1,input=-1;
 char reg[25];
 readData(s1,&count);
 while(checker){
       printf("\n\n\t\t\t\t====================\n");
       printf("\t\t\t\t\tMENU\n");
       printf("\t\t\t\t====================\n");
       printf("\t\t\t\t1. Add a record\n");
       printf("\t\t\t\t2. Search a record by ID\n");
       printf("\t\t\t\t3. Show all records\n");
       printf("\t\t\t\t4. Show students below average\n");
       printf("\t\t\t\t5. Save and exit\n");
       printf("\t\t\t\tEnter Your Choice: ");
       scanf("%d",&input);
       if(input == 1){
          if(count == 99){
            printf("\t\t\t\tStorage is already full! \n");
          }
          else{
               addRecord(s1,&count);
          }
       }
       else if(input == 2){
               printf("\t\t\t\tEnter ID of the Student: ");
               scanf("%s",reg);
               searchById(reg,s1,count);
      }
      else if(input == 3){
              showAllRecord(s1,count);
      }
      else if(input == 4){
              showBelowAverage(s1,count);
      }
      else if(input == 5){
             checker=0;
             printf("\n\n\t\t\t\t===================================\n");
             printf("\t\t\t\tThanks for using this Application!\n");
             printf("\t\t\t\t===================================\n");
      }
      else{
           printf("\t\t\t\tWrong Input!, Try Again\n");
         }
 }

 return 0;
}
void printStd(struct Student s1){
 printf("\n\n\t\t\t\t=========Student Info====================\n");
 printf("\t\t\t\t1. Name of the Student: %s\n",s1.name);
 printf("\t\t\t\t2. ID of the Student: %s\n",s1.id);
 printf("\t\t\t\t3. Gender of the Student: %c\n",s1.gender);
 printf("\t\t\t\t4. Quiz 1 Marks: %d\n",s1.quiz1);
 printf("\t\t\t\t5. Quiz 2 Marks: %d\n",s1.quiz2);
 printf("\t\t\t\t6. Mid Term Marks: %d\n",s1.mid);
 printf("\t\t\t\t7. Final Term Marks: %d\n",s1.final);
 printf("\t\t\t\t8. Obtained Marks: %d\n",s1.obtnMrks);
 printf("\t\t\t\t=========================================\n\n");
 
}
void readData(struct Student s1[],int* count){
 
 FILE *fptr; int checker=10;
 if((fptr=fopen("/home/ali/OSLabTask3/task1.txt","r")) != NULL){
     while(checker != EOF){
           checker=fscanf(fptr,"%s %s %c %d %d %d %d %d",s1[*count].id,s1[*count].name,&s1[*count].gender,&s1[*count].quiz1,&s1[*count].quiz2,&s1[*count].mid,&s1[*count].final,&s1[*count].obtnMrks);
           *count+=1; 
    }
    *count-=2;
    fclose(fptr);
 }
 else{
      printf("\t\t\t\tError! opening file to Read\n");
 } 

}
void addRecord(struct Student s1[],int* count){

 FILE *fptr; 
 *count+=1;
 printf("\n\n\t\t\t\t========ENTER STUDENT INFO============\n");
 printf("\t\t\t\t1. Name of the Student: ");
 scanf("%s",s1[*count].name);
 printf("\t\t\t\t2. ID of the Student: ");
 scanf("%s",s1[*count].id);
 printf("\t\t\t\t3. Gender of the Student: ");
 scanf(" %c",&s1[*count].gender);
 printf("\t\t\t\t4. Quiz 1 Marks: ");
 scanf("%d",&s1[*count].quiz1);
 printf("\t\t\t\t5. Quiz 2 Marks: ");
 scanf("%d",&s1[*count].quiz2);
 printf("\t\t\t\t6. Mid Term Marks: ");
 scanf("%d",&s1[*count].mid);
 printf("\t\t\t\t7. Final Term Marks: ");
 scanf("%d",&s1[*count].final);
 printf("\t\t\t\t8. Obtained Marks: ");
 scanf("%d",&s1[*count].obtnMrks);
 printf("=========================================\n\n");
 
 if( (fptr=fopen("/home/ali/OSLabTask3/task1.txt","a")) != NULL ){
      fprintf(fptr,"%s %s %c %d %d %d %d %d\n",s1[*count].id,s1[*count].name,s1[*count].gender,s1[*count].quiz1,s1[*count].quiz2,s1[*count].mid,s1[*count].final,s1[*count].obtnMrks);
      fclose(fptr);
 }
 else{
      printf("\t\t\t\tError! opening file to Write\n");
 }
 
}
void searchById(char reg[],struct Student s1[],int count){
 int i,checker=-1;
 for(i=0;i<=count;i++){
     if(strcmp(s1[i].id,reg) == 0){
        checker =i;
        i=count+1;
      }
  }
  if(checker == -1){
     printf("\t\t\t\tThe Record of %s isn't Present\n",reg);
  }
  else{
      printf("\t\t\t\tThe Record of %s is Present\n",reg);
  }
}
void showAllRecord(struct Student s1[],int count){
 int i;
 for(i=0;i<=count;i++){
     printStd(s1[i]);
 }
      
}
float average(struct Student s1[],int count){
    float avrg=0;
    int i;
    for(i=0;i<=count;i++){
        avrg+=s1[i].obtnMrks;
    }
    return (avrg/=(count+1));
}
void showBelowAverage(struct Student s1[],int count){

 float avrg=average(s1,count);
 int i;
 for(i=0;i<=count;i++){
     if(avrg > s1[i].obtnMrks){
        printStd(s1[i]);       
     }
 }
}

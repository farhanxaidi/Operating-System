#include<stdio.h>
#include<string.h>


int main(){

 char input[100];
 printf("Enter Your Sentence: - ");
 scanf("%[^'\n']s",input);
 int i=0,vowel=0,upperCase=0,lowerCase=0,val=0;
 while(input[i] != '\0'){
       val=(int)input[i];
       if(val >=65 && val<=90){
	  upperCase+=1;
          if(val == 65 || val == 69 || val  == 73 || val == 79 || val == 85){
             vowel+=1;
	  }
       }
       else if(val >=97 && val<=122){
	       lowerCase+=1;
               if(val==97 || val==101 || val==105 || val==111 || val == 117){
                  vowel+=1;
	       }	
	}
  i++;
  }
  printf("Vowel count = %d\nUppercase count = %d\nLowercase = %d\n",vowel,upperCase,lowerCase);


 return 0;
}

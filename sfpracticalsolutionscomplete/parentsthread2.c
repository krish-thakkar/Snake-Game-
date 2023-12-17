#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
// #include <sys/wait.h>
#include <ctype.h>

int countVowels(char *sentense){
    int count = 0 ;
 while(*sentense){
    char c = tolower(*sentense);
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
            count ++ ;
    }
    sentense++;
 }
 return count ;
}

int countWordsofsentense(char *sentese){
    int count = 0 ;
    int isWord = 0 ;
    
    while(*sentese){
        char c = tolower(*sentese);
        if( c==' ' || c=='\t' || c=='\n'){ // I replaced here " " with ' ' because it was showing the error of comaprsion because " " it is used for integer and ' ' for char
                isWord=0;
        }else if  ( isWord ==0 ){
            isWord=1;
            count++ ;
        }
        sentese++;
    }

    return count;
}
int main(){
 char sentense[]="Death is the only truth";


 pid_t pid = fork();

 if ( pid > 0 ){
    wait(NULL); // wait null systypes 
 int c2=countWordsofsentense(sentense);
 printf("%d" ,  c2);
 }
 else {
 int count = countVowels(sentense);
 printf("%d\n" ,  count);
 }



return 0 ;
}

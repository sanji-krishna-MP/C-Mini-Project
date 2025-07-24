#include<stdio.h>
#include <string.h>

int main(){
    char array[100];
    char newarray[100];
    fgets(array,100,stdin);
    strcpy(array,newarray);
    printf("%s",newarray);
}
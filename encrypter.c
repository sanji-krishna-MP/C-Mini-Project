#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
    FILE *data,*output;
    char ch;
    data = fopen("D:\\c files checker\\datafile.txt","r");
    output = fopen("D:\\c files checker\\encryptedfile.txt","w");
    srand(time(0));
    int number1 = (rand()%6) + 1;
    if(data == NULL){
        printf("Error in opening the data file");
        return(1);
    }
    if(output == NULL){
        printf("Error in opening the encrypted file");
    }
    do{
        ch = fgetc(data);
        fputc(ch+number1,output);    
    }while(ch != EOF);

    fclose(data);
    fclose(output);

    printf("Data file is encrypted and saved in the outputfile\n");
    printf("%d",number1);
}
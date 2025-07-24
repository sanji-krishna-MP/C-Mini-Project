#include<stdio.h>
int main(){
    FILE *parking = fopen("D:\\c files checker\\parking.txt","r");
    char buffer[250];
    int i = 0;
    int array[5];
    int array2[5] = {50,100,20,30,10};
    int totalsum = 0;
    int tot;
    while(i!=5){
        fgets(buffer,250,parking);
        printf("%s",buffer);
        scanf("%d",&array[i]);
        i++;
    }
    for(int i = 0;i<=4;i++){
        tot  = array[i]*array2[i];
        totalsum =totalsum + tot;
    }
    printf("The total amount gained is %d ",totalsum);

    fclose(parking);
    return 0;
}
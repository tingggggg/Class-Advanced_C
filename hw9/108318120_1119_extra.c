#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void del(char[],int,int);
int getIndexOfSigns(char ch);
void HextoDec(char* input);
void bintoDec(char* input);


int main(){
    int inp;
    char input[15];
    int input_type;

    while(1){
        printf("Input number: ");
        scanf("%s", input);
        // printf("Out: %s\n", input);
        if (input[0] == 'h' || input[0] == 'b') 
        {
            input_type = input[0]=='h' ? 0:1;
            del(input, 0, 1);
            void (*func[2])(char*) = {HextoDec, bintoDec};
            func[input_type](&input[0]);
        }
        else
        {
            printf("ERROR: no such option! \n\n");
        }
    }

    
    
    return 0;
}


int getIndexOfSigns(char ch)
{
    if(ch >= '0' && ch <= '9')
    {
        return ch - '0';
    }
    if(ch >= 'A' && ch <='F') 
    {
        return ch - 'A' + 10;
    }
    if(ch >= 'a' && ch <= 'f')
    {
        return ch - 'a' + 10;
    }
    return -1;
}


void del(char sum[],int del,int len)
{
    int i=0;
    for (; i<strlen(sum)-len-del; i++)
    {
        sum[del+i]=sum[len+del+i];
    }
    sum[del+(strlen(sum)-len-del)]='\0';
    
}


void HextoDec(char* input){
    long t = 1;
    int len = strlen(input);
    int i, sum = 0;
    for(i=len-1; i>=0; i--)
    {
        sum += t * getIndexOfSigns(input[i]);
        t *= 16;
    }

    printf("Result: %d", sum);
    printf("\n");
}


void bintoDec(char* input){
    long t = 1;
    int len = strlen(input);
    int i, sum = 0;
    for(i=len-1; i>=0; i--)
    {
        sum += t * getIndexOfSigns(input[i]);
        t *= 2;
    }

    printf("Result: %d", sum);
    printf("\n");
}

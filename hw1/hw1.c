#include <stdio.h>

int main()
{
    int i = 1;
    while(i <= 81){
        printf("%dx%d=%2d,", ((i - 1) / 9) + 1, ((i - 1) % 9) + 1, (((i - 1) / 9) + 1) * (((i - 1) % 9) + 1));
        i++;
        if((i - 1) % 9 == 0){
            printf("\n");
        }
    }
}
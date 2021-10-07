#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])  
{   
    int* array;
    int total = atoi(*(argv + 1)), row = 0;
    int i;

    array = (int*)malloc(sizeof(int) * total);
    for (i = 0; i < total; ++i) {
        *(array + i) = atoi(*(argv + 2 + i));
    }

    row = sqrt(atoi(*(argv + 1)));
    for (i = 0; i < total; i++) {
        printf("%2d ", *(array + i));
        if ((i + 1) % row == 0) printf("\n");
    }


    printf("\n");
    for (i = 0; i < total; i++) {
        int r = i / row;
        int c = i % row;

        if (r == 0)
            r = 2;
        else if(r == 2)
            r = 0;
        
        printf("%2d ", *(array + r * row + c));
        if ((i + 1) % row == 0) printf("\n");
    }


    printf("\n");
    for (i = 0; i < total; i++) {
        int r = i / row;
        int c = i % row;
        
        if (r == 0)
            r = 2;
        else if(r == 2)
            r = 0;

        if (c == 0)
            c = 2;
        else if (c == 2) 
            c = 0;
        
        printf("%2d ", *(array + r * row + c));
        if ((i + 1) % row == 0) printf("\n");
    }
}
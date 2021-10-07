#include <stdio.h>
#include <stdlib.h>

#define TOTAL 5

void bubble_sort(int* arr, int (*comp)(int, int));
void printSortBuff(int *buf);
int CompInc(int x, int y);
int CompDec(int x, int y);


int main(void){
    int i, flag;
    int *buf = (int*)malloc(sizeof(int) * TOTAL);

    while (1)
    {
        printf("Please enter(0) increasing or (1) descesing sort: ");
        scanf("%d", &flag);
        if(flag > 1 || flag < 0)
        {
            printf("ERROR: no such option! \n\n");
            continue;
        }

        printf("  Please enter %d integers: ", TOTAL);
        for(i = 0; i < TOTAL;i++){
            scanf("%d", (buf+i));
        }

        int (*func[2])(int, int) = {CompInc, CompDec};
        bubble_sort(buf, func[flag]);

        printSortBuff(buf);
        
    }
    
    return 0;
}


int CompInc(int x, int y){
    return x > y ? 1:0;
}


int CompDec(int x, int y){
    return y > x ? 1:0;
}


void printSortBuff(int *buf){
    int i;
    for(i = 0; i < TOTAL;i++){
        printf("%d ", buf[i]);
    }
    printf("\n\n");
}


void bubble_sort(int* arr, int (*comp)(int, int)) {
    int i, j;
    int temp;

    for (i=0; i < TOTAL-1; i++){ 
 		for (j=0; j < TOTAL-1-i; j++) 
 		{ 
 			if (comp(arr[j], arr[j+1]))
 			{ 
 				temp = arr[j];
 				arr[j] = arr[j+1];
 				arr[j+1] = temp;
 			}
        }
    }
}
#include<stdio.h>
#include<stdlib.h>

#define TOTAL 5

void print_array(int *arr);
void selectSort(int *arr, int (*comp)(int, int));
int cmpAscend(int x, int y);
int cmpDescend(int x, int y);

int main() {
    int flag;
    int *arr = (int*)malloc(sizeof(int) * TOTAL);

    while (1) {
        printf("Please enter (0)ascending or (1)descending: ");
        scanf("%d", &flag);
        if (flag > 1 || flag < 0) {
            printf("No such option \n");
            continue;
        }

        printf("Input element of array: ");
        int temp;
        for (int i = 0; i < TOTAL; ++i) {
            scanf("%d", &temp);
            *(arr + i) = temp;
        }

    
        int (*cmpFunc[2])(int, int) = {cmpAscend, cmpDescend};
        selectSort(arr, cmpFunc[flag]);

        print_array(arr);
    }
    return 0;
}

void print_array(int *arr) {
    for (int i = 0; i < TOTAL; ++i) {
        printf("%d ", *(arr + i));
    }
    printf("\n");
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectSort(int *arr, int (*comp)(int, int)) {
    for (int i = 0; i < TOTAL; ++i) {
        int idx = i;
        for (int j = i + 1; j < TOTAL; ++j) {
            // if (*(arr + j) < *(arr + idx)) {
            //     idx = j;
            // }
            if ( comp(*(arr + j), *(arr + idx)) ) {
                idx = j;
            }
        }
        if (idx != i) {
            swap((arr + idx), (arr + i));
        }
    }
    printf("\n");
}

int cmpAscend(int x, int y) {
    return x < y ? 1 : 0;
}

int cmpDescend(int x, int y) {
    return x > y ? 1 : 0;
}
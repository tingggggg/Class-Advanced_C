#include<stdio.h>
#include<stdlib.h>

typedef unsigned int Int32;
Int32 input;
Int32 high;
Int32 low;

int checkRangeLoop(Int32 input, Int32 high, Int32 low);
int checkRangeWithoutLoop(Int32 input, Int32 high, Int32 low);


int main() {

    int flag = 1;
    while (flag) {
        printf("Specify the input: ");
        scanf("%x", &input);
        
        printf("    Specify the high: ");
        scanf("%d", &high);

        printf("    Specify the low: ");
        scanf("%d", &low);

        printf("CheckRangeLoop result: ");
        checkRangeLoop(input, high, low);

        printf("CheckRangeWithoutLoop result: ");
        checkRangeWithoutLoop(input, high, low);
        
        printf("\n");
    }

    return 0;
}

int checkRangeLoop(Int32 input, Int32 high, Int32 low) {
    int left = 31 - high;
    for (int i = 0; i < left; i++) {
        input <<= 1;
    }

    for (int i = 0; i < left + low; ++i) {
        input >>= 1;
    }

    if (input) {
        printf("1\n");
    }
    else {
        printf("0\n");
    }
    return 0;
}

int checkRangeWithoutLoop(Int32 input, Int32 high, Int32 low) {
    int left = 31 - high;
    input <<= left;
    input >>= left + low;

    if (input) {
        printf("1\n");
    }
    else {
        printf("0\n");
    }
    return 0;
}
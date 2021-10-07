#include <stdio.h>

typedef unsigned int Int32;
Int32 input;
Int32 high;
Int32 low;

int CheckRangeLoop(Int32 input, Int32 high, Int32 low);
int CheckRangeNoLoop(Int32 input, Int32 high, Int32 low);

int main(void){
    int conti = 1;
    while(conti){
        printf("Please specify the input: ");
        scanf("%x", &input);

        printf("    Please specify the high: ");
        scanf("%d", &high);

        printf("    Please specify the low: ");
        scanf("%d", &low);

        printf("CheckRangeLoop result: ");
        CheckRangeLoop(input, high, low);

        printf("CheckRangeNoLoop result: ");
        CheckRangeNoLoop(input, high, low);

        printf("\n\nEnter 1 to keep trying the next round: ");
        scanf("%d", &conti);
    }

    return 0;
} 

int CheckRangeLoop(Int32 input, Int32 high, Int32 low){
    int left = 31 - high;
    // ship left first
    for(int i = 0; i < left; i++){
        input = input << 1;
    }
    //then ship right
    for(int i = 0; i < low + left; i++){
        input = input >> 1;
    }

    // then final res just only bit for (low ~ high)
    if(input)
        printf(" 1\n");
    else
        printf(" 0\n");
}


int CheckRangeNoLoop(Int32 input, Int32 high, Int32 low){
    int left = 31 - high;
    // ship left first
    input = input << left;
    //then ship right
    input = input >> left + low;

    // then final res just only bit for (low ~ high)
    if(input)
        printf(" 1\n");
    else
        printf(" 0\n");
}
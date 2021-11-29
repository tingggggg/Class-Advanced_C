#include <stdio.h>
#include <stdlib.h>

#define TOTAL 5

typedef int Int32;
typedef Int32 Buf[TOTAL];
typedef Int32 (*Comp)(Int32, Int32);

Int32 CompAscend(Int32 x, Int32 y) {
    return x > y ? 1 : 0;
}

Int32 CompDescend(Int32 x, Int32 y) {
    return x < y ? 1 : 0;
}

void bubbleSort(Buf *buf, Comp comp) {
    for (int i = 0; i < TOTAL; ++i) {
        for (int j = 0; j < TOTAL - 1 - i; ++j) {
            if (comp((*buf)[j], (*buf)[j + 1])) {
                Int32 temp = (*buf)[j];
                (*buf)[j] = (*buf)[j + 1];
                (*buf)[j + 1] = temp;
            }
        }
    }
}

void show(Buf *buf) {
    for (int i = 0; i < TOTAL; ++i) {
        printf("%d, ", (*buf)[i]);
    }
    
    printf("\n");
}


Int32 main() {
    Int32 i, flag;

    Buf* buf = (Buf*)malloc(sizeof(Buf));

    while (1) {
        printf("Enter (0) ascending or (1) descending: ");
        scanf("%d", &flag);

        if (flag < 0 || flag > 1) {
            printf("\tNo such option...\n");
            continue;
        }

        printf("Input %d int element(s): ", TOTAL);
        for (int i = 0; i < TOTAL; ++i) {
            scanf("%d", &(*buf)[i]);
        }

        Comp comp;

        Int32 (*funcs[2])(Int32, Int32) = {CompAscend, CompDescend};

        comp = funcs[flag];

        bubbleSort(buf, comp);

        printf("Content of buf: ");
        show(buf);
    }


    return 0;
}
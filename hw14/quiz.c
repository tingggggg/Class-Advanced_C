#include<stdio.h>

typedef char buf[2];

int main() {
    buf K[3];
    buf* p = K;

    printf("sizeof(K): %lu\n", sizeof(K));
    printf("reference of K[0]: %p, K[1]: %p, K[2]: %p\n", &K[0], &K[1], &K[2]);

    K[0][0] = 0x10; K[0][1] = 0x20;
    K[1][0] = 0x30; K[1][1] = 0x40;
    K[2][0] = 0x50; K[2][1] = 0x60;

    printf("%x, %x, %x, %x\n", *p, **p, *p[0], (*p)[0]);

    printf("%x, %x, %x, %x, %x\n", (*p)[1], \
                                   *p[1],
                                   **(p + 1),
                                   *(p + 1)[1],
                                   (*(p + 1))[1]);
    
    // 0x20
    // 0x30
    // 0x30
    // 0x50
    // 0x40

    return 0;
}
#include "space.h"

typedef struct node {
    tTypeScore *dataPtr;
    struct node *next;
} tNode;

typedef struct nodeInfo {
    int count;
    struct node *head;  
} tStack;

tStack *createStack(void);

void pushOperation(tStack *pStack);

void popOperation(tStack *pStack);

void printStackConetent(tStack *pStack);
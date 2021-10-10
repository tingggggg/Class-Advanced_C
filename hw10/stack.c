#include "stack.h"

tStack *createStack(void) {
    tStack *newStack;
    newStack = (tStack*)malloc(sizeof(tStack));
    newStack->count = 0;
    newStack->head = NULL;
    return newStack;
}

void pushOperation(tStack *pStack) {
    if (pStack->count == N) {
        printf("[Error] pushOperation(): spcae full\n");
        return;
    }
    
    int score;
    printf("\tEnter score: ");
    scanf("%d", &score);

    tNode *newNode = (tNode*)malloc(sizeof(tNode));

    tTypeScore *data;
    getScoreSpace(&data);
    
    data->used = 1;
    data->score = score;

    newNode->dataPtr = data;
    newNode->next = NULL;

    if (pStack->count == 0) {
        pStack->head = newNode;
    }
    else {
        newNode->next = pStack->head;
        pStack->head = newNode;
    }
    pStack->count++;
}

void popOperation(tStack *pStack) {
    if (pStack->count == 0) {
        printf("[Error] popOperation(): nothing in stack\n");
        return;
    }

    tNode* currHead = pStack->head;

    printf("\tpopOperation(): poped value: %d\n", currHead->dataPtr->score);
    returnScoreSpace(currHead->dataPtr->loc);

    pStack->head = currHead->next;
    pStack->count--;

    currHead->dataPtr->loc = 0;
    currHead->dataPtr->score = 0;
    currHead->dataPtr->used = 0;
}

void printStackConetent(tStack *pStack) {
    tNode *nodePtr = pStack->head;
    printf("*******\n");

    printf("Stack: ");
    for (int i = 0; i < pStack->count; i++) {
        printf(" %d(%d) ", nodePtr->dataPtr->score, nodePtr->dataPtr->loc);
        nodePtr = nodePtr->next;
    }

    printf("\n*******\n");

}
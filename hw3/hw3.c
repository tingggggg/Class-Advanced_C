#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct num_list {
    int counts;
    int *pList;
} tNumList;

void printList(tNumList *list) {
    int *ptr = list->pList;
    for (int i = 0; i < list->counts; ++i) {
        printf("%2d, ", *ptr);
        ptr++;
    }
    printf("\n");
}

void swap(int *p1, int *p2) {
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int partition(tNumList *list, int start, int end) {
    int pviot = start + (rand() % (end - start + 1));
    int j = start;
    for (int i = start ; i <= end; ++i) {
        if (*(list->pList + i) < *(list->pList + pviot)) {
            swap(list->pList + j, list->pList + i);
            if (pviot == j) {
                pviot = i;
            }
            ++j;
        }
    }
    swap(list->pList + j, list->pList + pviot);
    return j;
}

void quickSort(tNumList *list, int start, int end) {
    if (start < end) {
        int pviot = partition(list, start, end);
        quickSort(list, start, pviot - 1);
        quickSort(list, pviot + 1, end);
    }
}

tNumList* merge(tNumList* list1, tNumList *list2) {
    tNumList *mergeList = (tNumList*)malloc(sizeof(tNumList));
    mergeList->counts = list1->counts + list2->counts;
    mergeList->pList = (int*)malloc(sizeof(int) * mergeList->counts);

    int *ptr = mergeList->pList;
    while(list1->counts--) {
        *ptr = *(list1->pList + list1->counts);
        ++ptr;
    }
    free(list1->pList);
    free(list1);

    while (list2->counts--) {
        *ptr = *(list2->pList + list2->counts);
        ++ptr;
    }
    free(list2->pList);
    free(list2);

    return mergeList;
}

int main() {
    srand(time(NULL));

    int numList1 = 0, numList2 = 0;
    printf("Input nums of list1: ");
    scanf("%d", &numList1);
    tNumList* list1;
    list1 = (tNumList*)malloc(sizeof(tNumList));
    list1->counts = numList1;
    list1->pList = (int*)malloc(sizeof(int) * numList1);

    int *ptr = list1->pList;
    while (numList1) {
        scanf("%d", ptr);
        ++ptr;
        --numList1;
    }
    printList(list1);


    printf("Input nums of list2: ");
    scanf("%d", &numList2);
    tNumList *list2 = (tNumList*)malloc(sizeof(tNumList));
    list2->counts = numList2;
    list2->pList = (int*)malloc(sizeof(int) * numList2);

    ptr = list2->pList;
    while (numList2) {
        scanf("%d", ptr);
        ++ptr;
        --numList2;
    }
    printList(list2);

    tNumList *newList = merge(list1, list2);
    printf("Origin: ");
    printList(newList);

    quickSort(newList, 0, newList->counts - 1);
    printf("Sorted: ");
    printList(newList);

    return 0;
}
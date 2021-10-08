#include"list.h"

void inital_list(tNumStorHead* list) {
    list->counts = 0;
    list->head = NULL;
    list->tail = NULL;
}

tNumStorHead * productList() {
    tNumStorHead *newList = (tNumStorHead*)malloc(sizeof(tNumStorHead));
    return newList;
};

void add_inToList(tNumStorHead* list, int in, int loc, int beforeOrAfter) {
    tNumStorage *newNum = (tNumStorage*)malloc(sizeof(tNumStorage));
    newNum->number = in;
    newNum->prev = NULL;
    newNum->next = NULL;

    if (list->counts == 0) {
        list->head = newNum;
        list->tail = newNum;
    }
    else {
        int cntLoc = 1;
        tNumStorage *ptr = list->head;
        while (cntLoc != loc) {
            cntLoc++;
            ptr = ptr->next;
        }
        if (beforeOrAfter == 1) {
            newNum->prev = ptr->prev;
            newNum->next = ptr;
            ptr->prev = newNum;
            if (newNum->prev == NULL) {
                list->head = newNum;
            }
            else {
                newNum->prev->next = newNum;
            }
        }
        else if (beforeOrAfter == 2) {
            newNum->prev = ptr;
            newNum->next = ptr->next;
            ptr->next = newNum;
            if (newNum->next == NULL) {
                list->tail = newNum;
            }
            else {
                newNum->next->prev = newNum;
            }
        }

    }

    list->counts++;
}

void del_fromList(tNumStorHead* list, int loc) {
    if (list->counts == 1) {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
    }
    else {
        tNumStorage *ptr = list->head;
        while (--loc)
        {
            ptr = ptr->next;
        }
        tNumStorage *tempNext = ptr->next;
        tNumStorage *tempPrev = ptr->prev;
        if (tempPrev != NULL) {
            tempPrev->next = tempNext;
        }
        else {
            list->head = tempNext;
        }
        if (tempNext != NULL) {
            tempNext->prev = tempPrev;
        }
        else {
            list->tail = tempPrev;
        }
        free(ptr);
    }
    list->counts--;
}


void print_list(tNumStorHead* list) {
    tNumStorage *ptr = list->head;
    printf("\nlist->counts: %d\n", list->counts);
    printf("from head: ");
    while (ptr) {
        printf("%2d ", ptr->number);
        ptr = ptr->next;
    }
    printf("\n");

    printf("from tail: ");
    ptr = list->tail;
    while (ptr)
    {
        printf("%2d ", ptr->number);
        ptr = ptr->prev;
    }
    printf("\n");
    
}
#include<stdio.h>
#include<stdlib.h>

typedef struct num_storage {
    int number;
    struct num_storage *next;
    struct num_storage *prev;
} tNumStorage;

typedef struct num_stor_head {
    int counts;
    struct num_storage *head;
    struct num_storage *tail;
} tNumStorHead;

void inital_list(tNumStorHead* list);

void get_input(tNumStorHead* list);

void add_inToList(tNumStorHead* list, int in, int loc, int beforeOrAfter);

void del_fromList(tNumStorHead* list, int loc);

void print_list(tNumStorHead* list);


int main() {

    tNumStorHead *list;
    list = (tNumStorHead*)malloc(sizeof(tNumStorHead));
    inital_list(list);
    get_input(list);

    return 0;
}

void inital_list(tNumStorHead* list) {
    list->counts = 0;
    list->head = NULL;
    list->tail = NULL;
}

void get_input(tNumStorHead* list) {
    int in = 0;
    int addOrDel = 0, beforeOrAfter = 0;
    int loc = 0;
    while(in != -1) {
        printf("1. Add a number or 2. Delete a number: ");
        scanf("%d", &addOrDel);
        // Add element
        if (addOrDel == 1) {
            printf("Add a number: ");
            scanf("%d", &in);
            if (list->counts >= 1) {
                printf("Specify a target location: ");
                scanf("%d", &loc);
                if (loc > list->counts || loc == 0) {
                    printf("smaller than counts or equal !!! \n");
                    continue;
                }
                printf("1. Before or 2. After loc [%d]: ", loc);
                scanf("%d", &beforeOrAfter);
            }
            else {
                loc = 0;
            }
            add_inToList(list, in, loc, beforeOrAfter);
        }
        // Delete element
        else if (addOrDel == 2) {
            if (list->counts == 0) {
                printf("No element in list\n");
                continue;
            }

            printf("Specify a target location: ");
            scanf("%d", &loc);
            if (loc > list->counts || loc == 0) {
                printf("smaller than counts or equal\n");
                continue;
            }
            del_fromList(list, loc);
        }
        else {
            printf("No such choose! \n");
        }

        print_list(list);
    }
}

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


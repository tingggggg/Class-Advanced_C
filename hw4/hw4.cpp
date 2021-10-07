#include<stdio.h>
#include<stdlib.h>

typedef struct num_storage {
    int number;
    struct num_storage *next;
} tNumStorage;

typedef struct num_stor_head {
    int counts;
    struct num_storage* head;
    struct num_storage* tail;
} tNumStorHead;

void inital_list(tNumStorHead* list);
void print_list(tNumStorHead* list);
void get_input(tNumStorHead* list);
void sort_list(tNumStorHead* list, int in);

int main() {
    tNumStorHead* list;
    inital_list(list);
    get_input(list);
    return 0;
}

void inital_list(tNumStorHead* list) {
    list->counts = 0;
    list->head = NULL;
    list->tail = NULL;
}

void print_list(tNumStorHead* list) {
    tNumStorage* ptr = list->head;
    printf("list->counts: %d\n", list->counts);
    printf("list: ");
    while (ptr) {
        printf("%2d ", ptr->number);
        ptr = ptr->next;
    }
    printf("\n");
}

void get_input(tNumStorHead* list) {
    int in;
    while (1)
    {
        printf("Input: ");
        scanf("%d", &in);
        if (in != -1) {
            sort_list(list, in);
            print_list(list);
        }
        else {
            break;
        }
    }
}

void sort_list(tNumStorHead* list, int in) {
    tNumStorage *newNum = (tNumStorage*)malloc(sizeof(tNumStorage));
    newNum->number = in;
    newNum->next = NULL;

    if (list->counts == 0) {
        list->head = newNum;
        list->tail = newNum;
    }
    else {
        tNumStorage* ptrPrev = NULL;
        tNumStorage* ptr = list->head;
        while (ptr) {
            // 若找到比新插入數大位置就插入新數
            if (ptr->number > newNum->number) {
                newNum->next = ptr;
                if (ptrPrev == NULL) {
                    list->head = newNum;
                }
                else {
                    ptrPrev->next = newNum;
                }
                break;
            }
            ptrPrev = ptr;
            ptr = ptr->next;
        }

        // 遍歷完沒找到位置的話，ptr會是null，ptrPrev會是tail
        if (ptr == NULL) {
            list->tail->next = newNum;
            list->tail = newNum;
        }
    }
    list->counts++;
}
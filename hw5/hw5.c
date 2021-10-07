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

void sort_list(tNumStorHead* list, int in);

void print_list(tNumStorHead* list);

void delete_list(tNumStorHead* list);

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
    while(in != -1) {
        scanf("%d", &in);
        if (in != -2) {
            sort_list(list, in);
            print_list(list);
        }
        else if (in == -2) {
            delete_list(list);
            print_list(list);
        }
    }
}

void sort_list(tNumStorHead* list, int in) {
    tNumStorage *newNum = (tNumStorage*)malloc(sizeof(tNumStorage));
    newNum->next = NULL;
    newNum->prev = NULL;
    newNum->number = in;

    if (list->counts == 0) {
        list->head = newNum;
        list->tail = newNum;
    }
    else {
        tNumStorage *ptrPrev = NULL;
        tNumStorage *ptr = list->head;
        while (ptr) {
            if (ptr->number > newNum->number) {
                newNum->next = ptr;
                ptr->prev = newNum;
                // insert head
                if (ptrPrev == NULL) {
                    list->head = newNum;
                }
                // not insert head
                else {
                    newNum->prev = ptrPrev;
                    ptrPrev->next = newNum;                  
                }
                break;
            }
            ptrPrev = ptr;
            ptr = ptr->next;
        }

        if (ptr == NULL) {
            newNum->prev = list->tail;
            list->tail->next = newNum;
            list->tail = newNum;
        }
    }
    list->counts++;
}

void print_list(tNumStorHead* list) {
    tNumStorage *ptr = list->head;
    printf("list->counts: %d\n", list->counts);
    printf("list: ");
    while (ptr) {
        printf("%2d ", ptr->number);
        ptr = ptr->next;
    }
    printf("\n");
}

void delete_list(tNumStorHead* list) {
    if (list->counts == 0) {
        printf("Nothing \n");
    }
    else if (list->counts == 1) {
        list->counts--;
        free(list->head);

        list->head = NULL;
        list->tail = NULL;
    }
    else {

        tNumStorage *prev = list->tail->prev;
        prev->next = NULL;
        free(list->tail);

        list->tail = prev;
        list->counts--;
    }
}
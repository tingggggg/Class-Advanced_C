#include <stdio.h>
#include <stdlib.h>

typedef struct num_storage
{
    int number;
    struct num_storage *prev;
    struct num_storage *next;
    
} tNumStorage;

typedef struct num_stor_head
{
    int counts;
    struct num_storage *head;
    struct num_storage *tail;
} tNumStorHead;


void inital_list(tNumStorHead* list);
void print_list(tNumStorHead* list);
void get_input(tNumStorHead *list);
void add_intolist(tNumStorHead* list, int input, int loc, int beforeOrAfter);
void del_fromlist(tNumStorHead* list, int loc);


int main(void){
    int i;

    tNumStorHead *list;
    list = (tNumStorHead * )malloc(sizeof(tNumStorHead));
    inital_list(list);
    get_input(list);

    return 0;
}


void inital_list(tNumStorHead* list){
    list->counts = 0;
    list->head = NULL;
    list->tail = NULL;
}


void print_list(tNumStorHead* list){
    tNumStorage *p_store = list->head;
    printf("counts: %d \n", list->counts);
    printf("from head: ");
    while(p_store != NULL){
        printf("%d ", p_store->number);
        p_store = p_store->next;
    }
    
    printf("\n");

    printf("from tail: ");
    p_store = list->tail;
    while(p_store != NULL){
        printf("%d ", p_store->number);
        p_store = p_store->prev;
    }
    printf("\n");
}


void add_intolist(tNumStorHead* list, int input, int loc, int beforeOrAfter){
    tNumStorage* tstor;
    tstor = (tNumStorage*)malloc(sizeof(tNumStorage));
    tstor->next = NULL;
    tstor->prev = NULL;
    tstor->number = input;
    int cnt = loc - 1; 
    
    if (loc == 0){
        list->head = tstor;
        list->tail = tstor;
    }
    else{

        tNumStorage* tmpP = list->head;
        while(cnt){
            tmpP = tmpP->next;
            cnt--;
        }
        if(beforeOrAfter == 1){
            tstor->next = tmpP;
            tNumStorage* tmpPrev = tmpP->prev;
            
            tmpP->prev = tstor;
            tstor->prev = tmpPrev;
            if(loc == 1){
                list->head = tstor;
            }
            else
            {
                tmpPrev->next = tstor;
            }
            
            
        }
        else if(beforeOrAfter == 2)
        {
            tNumStorage* tmpNext = tmpP->next;
            tmpP->next = tstor;
            tstor->prev = tmpP;
            tstor->next = tmpNext;
            
            if(loc == list->counts){
                list->tail = tstor;
            }
            else
            {
                tmpNext->prev = tstor;
            }
            
        }
        else
        {
            printf(" only 1. or 2. \n");
        }   
    }
    list->counts++;
    print_list(list);
    printf("\n");
}


void del_fromlist(tNumStorHead* list, int loc){
    tNumStorage* tmpP = list->head;
    int cnt = loc - 1;
    if(tmpP != NULL){
        while(cnt){
            tmpP = tmpP->next;
            cnt--;
        }
        tNumStorage* pPrev = tmpP->prev;
        tNumStorage* pNext = tmpP->next;

        if(loc == list->counts)
            list->tail = pPrev;
        else
            pNext->prev = pPrev;
        
        if(loc == 1)
            list->head = pNext;
        else
            pPrev->next = pNext;

        free(tmpP);
    }
    list->counts--;
    print_list(list);
    printf("\n");
}


void get_input(tNumStorHead *list){
    int input = 0;
    int addOrDel = 0, beforeOrAfter = 0;
    int loc = 0;
    while (input != -1)
    {   
        printf("1. Add a number or 2. Delete a number: ");
        scanf("%d", &addOrDel);
        if(addOrDel == 1)
        {
            printf("add");
            printf("Add a number: ");
            scanf("%d", &input);
            if(list->counts >= 1){
                printf("Specify a target location: ");
                scanf("%d", &loc);
                if(loc > list->counts)
                {
                    printf("smaller than counts or equal\n !!!");
                    continue;
                }
                printf("1. Before or 2. After the location %d: ", loc);
                scanf("%d", &beforeOrAfter);
            }
            else
                loc = 0;

            add_intolist(list, input, loc, beforeOrAfter);
        }
        else if(addOrDel == 2)
        {
            if(list->counts >= 1){
                printf("Specify a target location: ");
                scanf("%d", &loc);
                if(loc > list->counts)
                {
                    printf("smaller than counts or equal\n");
                    continue;
                }
            }
            del_fromlist(list, loc);
        }
        else
            printf("No such choose !\n");


        // scanf("%d", &input);
        // if(input == -2)
        // {
        //     delete_last(list);
            
        // }
        // else if(input != -1)
        // {
        //     sort_list(list, input);
        // }
    }
}
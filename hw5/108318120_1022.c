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
void delete_last(tNumStorHead* list);
void sort_list(tNumStorHead* list, int input);


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
    printf("list->counts: %d \n", list->counts);
    printf("The sorted list: ");
    while(p_store != NULL){
        printf("%d ", p_store->number);
        p_store = p_store->next;
    }
    
    printf("\n");
}


void get_input(tNumStorHead *list){
    int input = 0;
    while (input != -1)
    {
        scanf("%d", &input);
        if(input == -2)
        {
            delete_last(list);
            
        }
        else if(input != -1)
        {
            sort_list(list, input);
        }
    }
}


void delete_last(tNumStorHead* list){
    if(list->counts <= 0){
        printf("Nothing \n");
    }
    else if(list->counts == 1)
    {
        list->counts = 0;
        list->head = NULL;
        list->tail = NULL;
        print_list(list);
    }
    else
    {
        tNumStorage* tmpTail = list->tail, *beforeTail = list->tail->prev;
        beforeTail->next = NULL;
        list->tail = beforeTail;
        list->counts--;
        free(tmpTail);
        print_list(list);
    }
}


void sort_list(tNumStorHead* list, int input){
    tNumStorage* tstor;
    tstor = (tNumStorage*)malloc(sizeof(tNumStorage));
    tstor->next = NULL;
    tstor->prev = NULL;
    tstor->number = input;

    if (list->counts == 0){
        list->head = tstor;
        list->tail = tstor;
    }
    else
    {
        tNumStorage *p_store_ori = list->head;
        tNumStorage *p_store = list->head;
        int posti = 0;
        while (p_store_ori != NULL)
        {   
            
            if(input > p_store_ori->number){
                p_store_ori = p_store_ori->next;
                posti++;
            }
            else
            {
                break;
            }          
        }
        
        if (posti == list->counts){
            // add tail
            tstor->prev = list->tail;
            list->tail->next = tstor;
            
                
            list->tail = tstor;
            }
        else if (posti < list->counts && posti != 0) {
            // add midd
            while (posti - 1)
            {
                p_store = p_store->next;
                posti--;
            }
            p_store->next->prev = tstor;
            tstor->next = p_store->next;
            tstor->prev = p_store;
            p_store->next = tstor;
        }
        else{
            // add head

            tstor->prev = NULL;
            tstor->next = list->head;
            list->head->prev = tstor;
            list->head = tstor;
        }
    }
    list->counts += 1;

    print_list(list);

}
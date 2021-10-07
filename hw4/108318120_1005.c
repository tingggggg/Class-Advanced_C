#include <stdio.h>
#include <stdlib.h>



typedef struct num_storage
{
    int number;
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
    printf("The sorted list: ");
    while(p_store != NULL){
        printf("%d ", p_store->number);
        p_store = p_store->next;
    }
    printf("\n");
}

void get_input(tNumStorHead *list){
    int input;
    while (1)
    {
        scanf("%d", &input);
        if(input == -1) break;
        sort_list(list, input);
    }
    
    
}

void sort_list(tNumStorHead* list, int input){
    tNumStorage* tstor;
    tstor = (tNumStorage*)malloc(sizeof(tNumStorage));
    tstor->next = NULL;
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
                // printf("position %d \n", posti);
                // printf("Next one %d \n", p_store_ori->number);
                break;
            }
            
        }
        // printf("position %d \n", posti);
        
        if (posti == list->counts){
            // add tail
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
            
            tstor->next = p_store->next;
            p_store->next = tstor;
        }
        else{
            // add head
            tstor->next = list->head;
            list->head = tstor;
        }
    }
    list->counts += 1;
    print_list(list);
}
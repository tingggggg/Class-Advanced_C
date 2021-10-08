#include "main.h"


void get_input(tNumStorHead *list);


int main(void){
    printf("123\n");

    tNumStorHead *list;
    list = productList();
    inital_list(list);
    get_input(list);

    return 0;
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
                    printf("smaller than counts or equal !!! \n");
                    continue;
                }
                printf("1. Before or 2. After the location %d: ", loc);
                scanf("%d", &beforeOrAfter);
            }
            else
                loc = 0;
            if(beforeOrAfter == 1 || beforeOrAfter == 2 || beforeOrAfter == 0){
                add_inToList(list, input, loc, beforeOrAfter);
                print_list(list);
                printf("\n");
            }
            else{
                printf("input only 1 or 2");
            }
            
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
            else if(list->counts == 0)
            {
                printf("please add number first \n");
                continue;
            }
            del_fromList(list, loc);
            print_list(list);
            printf("\n");
        }
        else
            printf("No such choose !\n");
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef enum operator Operator;

enum operator {
    CHT=1,
    FET,
    TWN
};

typedef struct home{
    char name[10];
    char number[10];
} HOME;
typedef struct cellular{
    char name[10];
    char number[10];
    Operator oper;
} CELL;

typedef union user{
    HOME home;
    CELL cellular;
}User;

typedef struct user_t user_type;
struct user_t {
    int type;    // 1 or 2 (home or cellular)
    User user;
    user_type *prev;
    user_type *next;
};

typedef struct manageUser{
    int counts;
    user_type *head;
    user_type *tail;

}manageUser;

void printList(manageUser *manageuser);

void sort_list(manageUser* list, user_type* newUser){


    if (list->counts == 0){
        list->head = newUser;
        list->tail = newUser;
    }
    else
    {   
        int ret;
        user_type *p_store_ori = list->head;
        user_type *p_store = list->head;
        int posti = 0;
        while (p_store_ori != NULL)
        {   
            if (newUser->type == 1)
            {   
                if (p_store_ori->type == 1)
                    ret = strcmp(newUser->user.home.name, p_store_ori->user.home.name);
                else if (p_store_ori->type == 2)
                    ret = strcmp(newUser->user.home.name, p_store_ori->user.cellular.name);

                if(ret > 0){
                    p_store_ori = p_store_ori->next;
                    posti++;
                }
                else
                {
                    break;
                }     
            }
            else if(newUser->type == 2)
            {
                if (p_store_ori->type == 1)
                    ret = strcmp(newUser->user.cellular.name, p_store_ori->user.home.name);
                else if (p_store_ori->type == 2)
                    ret = strcmp(newUser->user.cellular.name, p_store_ori->user.cellular.name);

                if(ret > 0){
                    p_store_ori = p_store_ori->next;
                    posti++;
                }
                else
                {
                    break;
                } 
            }
                 
        }
        
        if (posti == list->counts){
            // add tail
            newUser->prev = list->tail;
            list->tail->next = newUser;
            
                
            list->tail = newUser;
            }
        else if (posti < list->counts && posti != 0) {
            // add midd
            while (posti - 1)
            {
                p_store = p_store->next;
                posti--;
            }
            p_store->next->prev = newUser;
            newUser->next = p_store->next;
            newUser->prev = p_store;
            p_store->next = newUser;
        }
        else{
            // add head

            newUser->prev = NULL;
            newUser->next = list->head;
            list->head->prev = newUser;
            list->head = newUser;
        }
    }
    list->counts += 1;

    printList(list);

}


void printList(manageUser *manageuser)
{
    user_type *ut = manageuser->head;
    while(ut)
    {
        if (ut->type == 1)
        {   
            printf("HOME: \n");
            printf("    name: %s \n", ut->user.home.name);
            printf("    number: %s \n\n", ut->user.home.number);
        }
        else if(ut->type == 2)
        {
            printf("Cellular: \n");
            printf("    name: %s \n", ut->user.cellular.name);
            printf("    number: %s \n", ut->user.cellular.number);
            switch (ut->user.cellular.oper)
            {
                case CHT:
                    printf("    operator: CHT\n\n");
                    break;
                case FET:
                    printf("    operator: FET\n\n");
                    break;
                case TWN:
                    printf("    operator: TWN\n\n");
                    break;
                default:
                    printf("    you have no select\n\n");
            }
        }
        ut = ut->next;
    }
}


int main(){
    // init
    manageUser* manageuser = (manageUser*)malloc(sizeof(manageUser));
    manageuser->counts = 0;
    manageuser->head = NULL;
    manageuser->tail = NULL;

    while(1)
    {
        int type;
        printf("select type 1.home  2. cellular: ");
        scanf("%d", &type);
        if (type == 1)
        {   
            user_type *newUser = (user_type*)malloc(sizeof(user_type));
            newUser->next = NULL;
            newUser->prev = NULL;
            char name[10], number[10];
            printf("    input name: ");
            scanf("%s", name);
            printf("    input number: ");
            scanf("%s", number);

            newUser->type = type;
            strcpy(newUser->user.home.name, name);
            strcpy(newUser->user.home.number, number);

            sort_list(manageuser, newUser);

        }
        else if (type == 2)
        {
            user_type *newUser = (user_type*)malloc(sizeof(user_type));
            newUser->next = NULL;
            newUser->prev = NULL;
            char name[10], number[10];
            printf("    input name: ");
            scanf("%s", name);
            printf("    input number: ");
            scanf("%s", number);
            printf("    select operator (1. CHT, 2. FET, 3. TWN): ");
            Operator oper;
            scanf("%u", &oper);

            newUser->type = type;
            strcpy(newUser->user.cellular.name, name);
            strcpy(newUser->user.cellular.number, number);
            newUser->user.cellular.oper = oper;

            sort_list(manageuser, newUser);
        }
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 307

typedef struct tnameid
{
    int ID;
    char name[10];
    struct tnameid* next;
}tNameID;

int eval_hash(char *name, int ID){
    long key = 1;
    for(int i = 0; name[i]; i++){
        // printf("%c的ASCII:%d\t",name[i],name[i]);
        key *= name[i];
    }
    key *= ID;
    key = key % N;
    // printf("\n key: %ld \n", key);
    return key;
}

int main(){
    tNameID *name_list = (tNameID*)malloc(sizeof(tNameID) * N);

    int mode;
    char name[10];
    int ID;

    while(1)
    {   
        printf("\n");
        printf("1. add user, 2. lookup user: ");
        scanf("%d", &mode);
        if (mode == 1)
        {   

            printf("Add User \n");
            printf("    Input Name: ");
            scanf("%s", name);
            printf("    Input ID: ");
            scanf("%d", &ID);

            int key = eval_hash(name, ID);

            tNameID *newOne = (tNameID*)malloc(sizeof(tNameID));
            newOne->ID = ID;
            strcpy(newOne->name, name);
            newOne->next = NULL;

            tNameID *bucker_slot = (name_list + key);
            if(strlen(bucker_slot->name) == 0)
            {
                *(name_list + key) = *newOne;
            }
            else
            {   
                int cnt = 2;
                while(bucker_slot->next != NULL)
                {
                    bucker_slot = bucker_slot->next;
                    cnt += 1;
                }
                bucker_slot->next = newOne;
            }
        }
        else
        {

            printf("Lookup User \n");
            printf("    Input Name: ");
            scanf("%s", name);
            printf("    Input ID: ");
            scanf("%d", &ID);

            int key = eval_hash(name, ID);

            tNameID *bucker_slot = (name_list + key);
            if(strlen(bucker_slot->name) != 0)
            {
                while(bucker_slot)
                {
                    printf("ID   -> %d \n", bucker_slot->ID);
                    printf("Name -> %s \n", bucker_slot->name);
                    printf("---------------\n");
                    bucker_slot = bucker_slot->next;
                }
            }
            else
            {
                printf("User Unknown \n");
            }
        }
    }

    return 0;
}
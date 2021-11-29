#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5

typedef struct tnameid {
    int ID;
    char name[10];
    struct tnameid* next;
} tNameID;

int eval_hash(char name[], int ID);

int main() {
    // init name list
    tNameID* name_list = (tNameID*)malloc(sizeof(tNameID) * N);

    int mode;
    int ID;
    char name[10];

    while (1) {
        printf("\n");
        printf("Select 1. add user, 2. lookup user: ");
        scanf("%d", &mode);

        if (mode < 1 || mode > 2) {
            printf("\tNo such option...\n");
            continue;
        }

        if (mode == 1) {
            printf("Add user\n");
            printf("\tInput name: ");
            scanf("%s", name);
            printf("\tInput id: ");
            scanf("%d", &ID);

            int key = eval_hash(name, ID);

            tNameID* newPerson = (tNameID*)malloc(sizeof(tNameID));

            newPerson->ID = ID;
            strcpy(newPerson->name, name);
            newPerson->next = NULL;

            tNameID *bucker_slot = (name_list + key);

            // empty bucket
            if (strlen(bucker_slot->name) == 0) {
                *bucker_slot = *newPerson;

                // use name_list space, so free newPerson space
                free(newPerson);
            }

            else {
                while (bucker_slot->next != NULL) {
                    bucker_slot = bucker_slot->next;
                }
                bucker_slot->next = newPerson;
            }
        }

        else if (mode == 2) {
            printf("Lookup user\n");
            printf("\tInput name: ");
            scanf("%s", name);
            printf("\tInput ID: ");
            scanf("%d", &ID);

            int key = eval_hash(name, ID);

            tNameID* bucker_slot = (name_list + key);

            printf("Lookup results\n");
            if (strlen(bucker_slot->name) != 0) {
                int found = 0;
                while (bucker_slot) {
                    if (bucker_slot->ID == ID) {
                        printf("\tID: %d\n", bucker_slot->ID);
                        printf("\tName: %s\n", name);
                        printf("\t----------\n");

                        found = 1;
                        break;
                    }
                    
                    bucker_slot = bucker_slot->next;
                }

                if (!found) {
                    printf("\tNot found...\n");
                }
            }

            else {
                printf("\tKey %d is empty...\n", key);
            }
        }
    }
    

    return 0;
}

int eval_hash(char name[], int ID) {
    long key;
    for (int i = 0; i < strlen(name); ++i) {
        key *= name[i];
    }
    
    key *= ID;
    
    key = key % N;

    return key;
}
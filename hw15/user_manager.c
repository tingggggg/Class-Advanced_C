#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum operator {
    CHT = 1,
    FET,
    TWN
} Operator;

typedef struct home {
    char name[10];
    char number[10];
} HOME;

typedef struct cellular {
    char name[10];
    char number[10];
    Operator op;
} CELL;

typedef union user {
    HOME home;
    CELL cellular;
} User;

typedef struct user_t {
    int type; // 1. home / 2. cellurlar
    User user;
    struct user_t* prev;
    struct user_t* next;
} user_type;

typedef struct managerUser {
    int counts;
    user_type* head;
    user_type* tail;
} ManagerUser;

void sortInsert(ManagerUser* mu, user_type* user);

void show(ManagerUser* mu);

int main() {
    // init manager
    ManagerUser* managerUser = (ManagerUser*)malloc(sizeof(ManagerUser));
    managerUser->counts = 0;
    managerUser->head = NULL;
    managerUser->tail = NULL;

    while (1) {
        int type;
        printf("Input type 1. home or 2. cellular: ");
        scanf("%d", &type);

        if (type < 1 || type > 2) {
            printf("\tNo such option...\n");
            continue;
        }

        // init user
        user_type* newUser = (user_type*)malloc(sizeof(user_type));
        newUser->type = type;
        newUser->prev = NULL;
        newUser->next = NULL;

        // user input name and number
        char name[10], number[10];
        printf("\tInput name: ");
        scanf("%s", name);
        printf("\tInput number: ");
        scanf("%s", number);

        strcpy(newUser->user.home.name, name);
        strcpy(newUser->user.home.number, number);

        if (type == 2) {
            Operator op;
            printf("\tSelect operator (1. CHT, 2. FET, 3. TWN): ");
            scanf("%u", &op);
            newUser->user.cellular.op = op;
        }

        sortInsert(managerUser, newUser);

        show(managerUser);
    }

    return 0;
}

void sortInsert(ManagerUser* mu, user_type* user) {
    // first insert
    if (mu->counts == 0) {
        mu->head = user;
        mu->tail = user;
    }

    else {
        user_type* pUserPrev = NULL;
        user_type* pUser = mu->head;

        int cmp_ret = 0;
        while (pUser) {
            if (pUser->type == 1) {
                if (user->type == 1) {
                    cmp_ret = strcmp(user->user.home.name, pUser->user.home.name);
                }
                else if (user->type == 2) {
                    cmp_ret = strcmp(user->user.cellular.name, pUser->user.home.name);
                }
            }

            else if (pUser->type == 2) {
                if (user->type == 1) {
                    cmp_ret = strcmp(user->user.home.name, pUser->user.cellular.name);
                }
                else if (user->type == 2) {
                    cmp_ret = strcmp(user->user.cellular.name, pUser->user.cellular.name);
                }
            }

            if (cmp_ret < 0) break;

            pUserPrev = pUser;
            pUser = pUser->next;
        }

        // found at head
        if (pUserPrev == NULL ) {
            user->next = pUser;
            pUser->prev = user;

            mu->head = user;
        }

        // found at tail
        else if (pUser == NULL) {
            pUserPrev->next = user;
            user->prev = pUserPrev;

            mu->tail = user;
        }

        // found at mid
        else {
            pUserPrev->next = user;
            user->prev = pUserPrev;

            pUser->prev = user;
            user->next = pUser;
        }
        
    }

    ++mu->counts;
}

void show(ManagerUser* mu) {
    user_type* user = mu->head;

    while (user) {
        // home
        if (user->type == 1) {
            printf("HOME: \n");
            printf("\tname: %s\n", user->user.home.name);
            printf("\tnumber: %s\n", user->user.home.number);
        }
        else if (user->type == 2) {
            printf("Cellular: \n");
            printf("\tname: %s\n", user->user.home.name);
            printf("\tnumber: %s\n", user->user.home.number);
            switch(user->user.cellular.op) {
                case CHT:
                    printf("\toperator: CHT");
                    break;
                case FET:
                    printf("\toperator: FET");
                    break;
                case TWN:
                    printf("\toperator: TWN");
                    break;
                default:
                    break;
            }
        }
        printf("\n");
        
        user = user->next;
    }
}

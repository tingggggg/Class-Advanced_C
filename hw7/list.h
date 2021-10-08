#ifndef _LIST_H_
#define _LIST_H_

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

tNumStorHead * productList();
void inital_list(tNumStorHead* list);
void print_list(tNumStorHead* list);
void add_inToList(tNumStorHead* list, int input, int loc, int beforeOrAfter);
void del_fromList(tNumStorHead* list, int loc);

#endif




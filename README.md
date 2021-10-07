# Class-Advanced_C

## HW1
- 一個迴圈完成九九乘法表

## HW2
- 輸入 1 + x^2 個數 (第一個數代表總數， x 必須大於三)

- 交換一三列，交換一三行

- 不能使用 "[]"，除了cmd line argument

## HW3
- 使用者輸入兩個list(維護list)

- 兩個list合併並且排序(quick sort)

## HW4
- 維護list，依照升序插入某數
``` c=
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
```
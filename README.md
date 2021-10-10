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

## HW5
- 延續 HW4，新增尾刪(implement with prev node)

## HW6
- list 指定位置(前or後)新增 / 刪除某數

## HW7
- 延續 HW6，分割頭文件

## HW8
- bitwise 操作
- 判斷指定 high low 範圍中是否有值

## HW9
- Function Pointer (升/降序實作)

- Function Pointer(Extra) (16進位/2進位 轉換成 10進位)

# HW10
- Stack 管理

- Pointer to pointer 改變pointer指向
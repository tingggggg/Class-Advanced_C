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

## HW10
- Stack 管理

- Pointer to pointer 改變pointer指向(指向事先開放在棧區的記憶體地址/空間)

## HW11
- 大/小 struct 不同 size 的記憶體 buffer 管理
```c=
#define TYPE_SMALL 0
#define TYPE_LARGE 1

#define NUM_SMALL_BYTE_BUF     8
#define NUM_LARGE_BYTE_BUF     8

#define SMALL_ELEMENT_SIZE  32
#define LARGE_ELEMENT_SIZE  64

#define LARGE_BUFFER_START (NUM_SMALL_BYTE_BUF * SMALL_ELEMENT_SIZE)

unsigned char buffer[NUM_SMALL_BYTE_BUF*SMALL_ELEMENT_SIZE + NUM_LARGE_BYTE_BUF*LARGE_ELEMENT_SIZE];

// size 28
typedef struct type_small{
    int id;
    int score;
    int location;
    struct type_small* next;
    struct type_small* prev;
} tQueueSmall;

// size 56
typedef struct type_large{
    int id;
    int score[8];
    int location;
    struct type_large* next;
    struct type_large* prev;
} tQueueLarge;
...
```

```shell=
Which type you are going to operate?
1. Add a type 1 item
2. Add a type 2 item
3. remove a type 1 item with a specific Id
4. remove a type 2 item with a specific Id
2
	enter id: 33

Status
	byte_small_buff_mask: 0 0 0 1 1 1 1 1
	byte_large_buff_mask: 0 0 0 0 0 1 1 1
	type small queue: 1 2 3 4 5
	type large queue: 11 22 33
```

## HW12
- 承上題，改成統一使用`tQueueNode`，並使用void pointer 管理大/小 struct 記憶體
```c=
typedef struct type_small{
    int id;
    int score;
    int location;
} tQueueSmall;

typedef struct type_large{
    int id;
    int score[8];
    int location;
} tQueueLarge;

typedef struct node {
    int type;
    void *content;
    struct node *next;
    struct node *prev;
} tQueueNode;

typedef struct {
    tQueueNode* front;
    tQueueNode* rear;
    int count;
} tQueue;
```

```shell=
Which type you are going to operate?
1. Add a type 1 item
2. Add a type 2 item
3. remove a type 1 item with a specific Id
4. remove a type 2 item with a specific Id
2
	enter id: 33

Status
	byte_small_buff_mask: 0 0 0 1 1 1 1 1
	byte_large_buff_mask: 0 0 0 0 0 1 1 1
	type mixed queue: 1(0), 2(0), 3(0), 4(0), 5(0), 11(1), 22(1), 33(1),
```

## HW13
- 承上題，擴充buffer大小為可調整

- large size 在小的 buffer 尋找空位置時，需處理跨不同 buffer 的狀況

```shell=
Which type you are going to operate?
1. Add a type 1 item
2. Add a type 2 item
3. remove a type 1 item with a specific Id
4. remove a type 2 item with a specific Id
2
	enter id: 4444

Status
	byte_small_buff_mask: 0 0 0 1 1 1 1 0  | 1 1 1 1 1 1 1 1  |
	byte_large_buff_mask: 1 1 1 1 1 1 1 1  | 1 1 1 1 1 1 1 1  |
	type mixed queue: 1(0), 2(0), 3(0), 4(0), 5(0), 6(0), 7(0), 11(1), 33(1), 44(1), 55(1), 66(1), 77(1), 88(1), 111(1), 222(1), 444(1), 555(1), 666(1), 777(1), 888(1), 1111(1), 8(0), 2222(1), 333(1), 4444(1),
```

## HW14
- typedef 宣告(不同於define單純代碼)

- 例如 security key(128bit)，能夠使用`typedef unsigned char skey[16]; sizeof(skey) = 16 bytes`來代替

```c=
#define TOTAL 5

typedef int Int32;
typedef Int32 Buf[TOTAL];
typedef Int32 (*Comp)(Int32, Int32);

...
Buf* buf = (Buf*)malloc(sizeof(Buf));
(*buf)[1] = 22;

Comp comp;

Int32 (*funcs[2])(Int32, Int32) = {ComeAscend, CompDescend};

comp = funcs[1]; // CompDescend
```
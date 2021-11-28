#include <stdio.h>
#include <stdlib.h>

#define TYPE_SMALL 0
#define TYPE_LARGE 1

#define NUM_SMALL_BYTE_BUF     8
#define NUM_LARGE_BYTE_BUF     8

#define SMALL_ELEMENT_SIZE  32
#define LARGE_ELEMENT_SIZE  64

#define LARGE_BUFFER_START (NUM_SMALL_BYTE_BUF * SMALL_ELEMENT_SIZE)

unsigned char buffer[NUM_SMALL_BYTE_BUF*SMALL_ELEMENT_SIZE + NUM_LARGE_BYTE_BUF*LARGE_ELEMENT_SIZE];

unsigned char byte_large_buf_mask = 0;
unsigned char byte_small_buf_mask = 0;

typedef struct type_small{
    int id;
    int score;
    int location;
    struct type_small* next;
    struct type_small* prev;
} tQueueSmall;

typedef struct type_large{
    int id;
    int score[8];
    int location;
    struct type_large* next;
    struct type_large* prev;
} tQueueLarge;

typedef struct {
    tQueueSmall* type_small_front;
    tQueueSmall* type_small_rear;
    tQueueLarge* type_large_front;
    tQueueLarge* type_large_rear;
    int num_type_small;
    int num_type_large;
} tQueue;

tQueue* createQueue(void);

void ourMalloc(int type, int size, void **target, int *mem_location);
void ourFree(int type, void *target, int mem_location);

int enqueue_type_small(tQueue* queue, int id, int score);
int enqueue_type_large(tQueue *queue, int id, int score); 

int test_single_location(unsigned char mask, int mask_length);
int test_dual_location(unsigned char mask, int make_length);

void set_single_bit(unsigned char* mask, int location);

tQueueSmall* find_target_small_node(tQueue* queue, int id);
tQueueLarge* find_target_large_node(tQueue* queue, int id);

void dequeue_type_small(tQueue* queue, tQueueSmall* target);
void dequeue_type_large(tQueue* queue, tQueueLarge* target);

void clear_single_bit(unsigned char* mask, int mem_location);

void show_buff() {
    printf("\tbyte_small_buff_mask: ");
    for (int i = NUM_SMALL_BYTE_BUF - 1; i >= 0; --i) {
        printf("%d ", (byte_small_buf_mask >> i) & 0x01);
    }

    printf("\n");

    printf("\tbyte_large_buff_mask: ");
    for (int i = NUM_LARGE_BYTE_BUF - 1; i >= 0; --i) {
        printf("%d ", (byte_large_buf_mask >> i) & 0x01);
    }

    printf("\n");
}

void show_queue(tQueue* queue) {
    printf("\ttype small queue: ");
    void* p = queue->type_small_front;
    for (int i = 0; i < queue->num_type_small; ++i)
    {
        printf("%d ", ((tQueueSmall*)p)->id);
        p = ((tQueueSmall*)p)->next;
    }

    printf("\n");

    p = NULL;

    printf("\ttype large queue: ");
    p = queue->type_large_front;
    for (int i = 0; i < queue->num_type_large; ++i)
    {
        printf("%d ", ((tQueueLarge*)p)->id);
        p = ((tQueueLarge*)p)->next;
    }

    printf("\n");
}

int main() {
    tQueue* queue;
    queue = createQueue();

    int operation;

    int id, score = 0, ret;

    // main
    while (1) {
        printf("\nWhich type you are going to operate? \n");
        printf("1. Add a type 1 item\n");
        printf("2. Add a type 2 item\n");
        printf("3. remove a type 1 item with a specific Id\n");
        printf("4. remove a type 2 item with a specific Id\n");

        scanf("%d", &operation);

        // add element in type small
        if (operation == 1) {
            printf("\tenter id: ");
            scanf("%d", &id);

            ret = enqueue_type_small(queue, id, score);

            if (ret == -1)
            {
                printf("\tCannot enter to the queue\n");
            }


            printf("\nStatus\n");
            show_buff();

            show_queue(queue);
        }

        // add element in type large
        else if (operation == 2) {
            printf("\tenter id: ");
            scanf("%d", &id);

            ret = enqueue_type_large(queue, id, score);

            if (ret == -1)
            {
                printf("\tCannot enter to the queue\n");
            }


            printf("\nStatus\n");
            show_buff();

            show_queue(queue);
            
        }

        else if (operation == 3) {
            printf("\tenter a small id to remove: ");
            scanf("%d", &id);

            tQueueSmall *target_type_small = NULL;
            target_type_small = find_target_small_node(queue, id);
            
            // not found
            if (target_type_small == NULL) {
                printf("\tCannot find the target id in queue\n");
            }
            else {
                dequeue_type_small(queue, target_type_small);
            }
            
            printf("\nStatus\n");
            show_buff();

            show_queue(queue);
        }

        else if (operation == 4) {
            printf("\tenter a large id to remove: ");
            scanf("%d", &id);

            tQueueLarge *target_type_large = NULL;
            target_type_large = find_target_large_node(queue, id);

            // not found
            if (target_type_large == NULL) {
                printf("\tCannor find the target id in queue");
            }
            else {
                dequeue_type_large(queue, target_type_large);
            }

            printf("\nStatus\n");
            show_buff();

            show_queue(queue);
        }
    }

    return 0;
}

tQueue* createQueue() {
    tQueue* newQueue;
    newQueue = (tQueue*)malloc(sizeof(tQueue));

    if (newQueue) {
        newQueue->type_small_front = NULL;
        newQueue->type_small_rear = NULL;
        newQueue->type_large_front = NULL;
        newQueue->type_large_rear = NULL;
        newQueue->num_type_small = 0;
        newQueue->num_type_large = 0;
    }

    return newQueue;
}

int enqueue_type_small(tQueue* queue, int id, int score) {
    tQueueSmall* newPtr = NULL;
    int mem_location;

    ourMalloc(TYPE_SMALL, sizeof(tQueueSmall), (void *)&newPtr, &mem_location);

    if (newPtr == NULL) {
        printf("\tEnqueue failed...\n");
        return -1;
    }

    newPtr->id = id;
    newPtr->score = score;
    newPtr->location = mem_location;
    newPtr->next = NULL;
    newPtr->prev = NULL;

    if (queue->num_type_small == 0)
        queue->type_small_front = newPtr;
    else
        queue->type_small_rear->next = newPtr;

    newPtr->prev = queue->type_small_rear;
    queue->type_small_rear = newPtr;
    ++queue->num_type_small;

    return 1;
}

void ourMalloc(int type, int size, void **target, int *mem_location) {
    if (type == TYPE_SMALL) {
        *mem_location = test_single_location(byte_small_buf_mask, NUM_SMALL_BYTE_BUF);

        // found in small buffer
        if (*mem_location < NUM_SMALL_BYTE_BUF) {
            *target = &buffer[*mem_location * SMALL_ELEMENT_SIZE];

            set_single_bit(&byte_small_buf_mask, *mem_location);

            *mem_location *= SMALL_ELEMENT_SIZE;
        }

        // test in large buffer
        else {
            *mem_location = test_single_location(byte_large_buf_mask, NUM_LARGE_BYTE_BUF);

            if (*mem_location < NUM_LARGE_BYTE_BUF) {
                *target = &buffer[LARGE_BUFFER_START + *mem_location * LARGE_ELEMENT_SIZE];

                set_single_bit(&byte_large_buf_mask, *mem_location);

                *mem_location = LARGE_BUFFER_START + *mem_location * LARGE_ELEMENT_SIZE;
            }
        }
    }

    else if (type == TYPE_LARGE) {
        *mem_location = test_single_location(byte_large_buf_mask, NUM_LARGE_BYTE_BUF);

        if (*mem_location < NUM_LARGE_BYTE_BUF) {
            *target = &buffer[LARGE_BUFFER_START + *mem_location * LARGE_ELEMENT_SIZE];

            set_single_bit(&byte_large_buf_mask, *mem_location);

            *mem_location = LARGE_BUFFER_START + *mem_location * LARGE_ELEMENT_SIZE;
        }

        else {
            *mem_location = test_dual_location(byte_small_buf_mask, NUM_SMALL_BYTE_BUF);
            if (*mem_location < NUM_SMALL_BYTE_BUF) {
                *target = &buffer[*mem_location * SMALL_ELEMENT_SIZE];

                set_single_bit(&byte_small_buf_mask, *mem_location);
                set_single_bit(&byte_small_buf_mask, *mem_location + 1);

                *mem_location *= SMALL_ELEMENT_SIZE;
            }
        }
    }
}

int test_single_location(unsigned char mask, int mask_length) {
    unsigned char fmask = 0x01;
    mask = ~mask;

    int idx = 0;
    for (idx = 0; idx < mask_length; ++idx) {
        if (fmask & mask) {
            return idx;
        }
        fmask <<= 1;
    }
    // not found
    return idx;
}

int test_dual_location(unsigned char mask, int mask_length) {
    unsigned char fmask = 0x01;
    mask = ~mask;

    int idx = 0;
    for (idx = 0; idx < mask_length; ++idx) {
        // check continus 2 bits
        if (fmask & mask && (fmask << 1) & mask) {
            return idx;
        }
        fmask <<= 1;
    }
    // not found
    return idx;
}

void set_single_bit(unsigned char* mask, int location) {
    *mask |= (1 << location);
}

tQueueSmall* find_target_small_node(tQueue* queue, int id) {
    tQueueSmall* p = queue->type_small_front;
    while (p) {
        if (p->id == id)
            return p;
        p = p->next;
    }

    return NULL;
}

void dequeue_type_small(tQueue* queue, tQueueSmall* target) {
    if (queue->num_type_small == 1) {
        queue->type_small_front = NULL;
        queue->type_small_rear = NULL;
    }
    else if (target == queue->type_small_front) {
        queue->type_small_front = target->next;
    }
    else if (target == queue->type_small_rear) {
        queue->type_small_rear = target->prev;
    }
    else {
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }

    --queue->num_type_small;
    ourFree(TYPE_SMALL, target, target->location);
}

void  ourFree(int type, void *target, int mem_location) {
    if (type == TYPE_SMALL) {
        // in small buffre
        if (mem_location / SMALL_ELEMENT_SIZE < NUM_SMALL_BYTE_BUF) {
            mem_location /= SMALL_ELEMENT_SIZE;

            clear_single_bit(&byte_small_buf_mask, mem_location);
        }

        // in large buffer
        else {
            mem_location -= LARGE_BUFFER_START;
            mem_location /= LARGE_ELEMENT_SIZE;

            clear_single_bit(&byte_large_buf_mask, mem_location);
        }
    }

    else if (type == TYPE_LARGE) {
        // in large buffer
        if (mem_location >= LARGE_BUFFER_START) {
            mem_location -= LARGE_BUFFER_START;
            mem_location /=  LARGE_ELEMENT_SIZE;

            clear_single_bit(&byte_large_buf_mask, mem_location);
        }

        // in small buffer
        else {
            mem_location /= SMALL_ELEMENT_SIZE;

            clear_single_bit(&byte_small_buf_mask, mem_location);
            clear_single_bit(&byte_small_buf_mask, mem_location + 1);
        }
        
    }
}

void clear_single_bit(unsigned char* mask, int mem_location) {
    *mask &= ~(1 << mem_location);
}

int enqueue_type_large(tQueue *queue, int id, int score) {
    tQueueLarge* newPtr = NULL;
    int mem_location;

    ourMalloc(TYPE_LARGE, sizeof(tQueueLarge), (void* )&newPtr, &mem_location);

    if (newPtr == NULL) {
        printf("\tEnqueue failed...\n");
        return -1;
    }

    newPtr->id = id;
    newPtr->score[0] = score;
    newPtr->location = mem_location;
    newPtr->next = NULL;
    newPtr->prev = NULL;

    if (queue->num_type_large == 0)
        queue->type_large_front = newPtr;
    else
        queue->type_large_rear->next = newPtr;

    newPtr->prev = queue->type_large_rear;
    queue->type_large_rear = newPtr;
    ++queue->num_type_large;

    return 1;

}

void dequeue_type_large(tQueue* queue, tQueueLarge* target) {
    if (queue->num_type_large == 1) {
        queue->type_large_front = NULL;
        queue->type_large_rear = NULL;
    }
    else if (target == queue->type_large_front) {
        queue->type_large_front = target->next;
    }
    else if (target == queue->type_large_rear) {
        queue->type_large_rear = target->prev;
    }
    else {
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }

    --queue->num_type_large;
    ourFree(TYPE_LARGE, target, target->location);
}

tQueueLarge* find_target_large_node(tQueue* queue, int id) {
    tQueueLarge* p = queue->type_large_front;
    while (p) {
        if (p->id == id)
            return p;
        p = p->next;
    }

    return NULL;
}

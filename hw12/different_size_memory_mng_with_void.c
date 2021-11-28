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

tQueue* createQueue(void);

void ourMalloc(int type, void **target, int *mem_location);
void ourFree(int type, int mem_location);

int enqueue(tQueue* queue, int id, int score, int type);
int dequeue(tQueue* queue, tQueueNode* target);

int test_single_location(unsigned char mask, int mask_length);
int test_dual_location(unsigned char mask, int make_length);

void set_single_bit(unsigned char* mask, int location);

tQueueNode* find_target_node(tQueue* queue, int id, int type);

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
    tQueueNode* p = queue->front;
    printf("\ttype mixed queue: ");
    for (int i = 0; i < queue->count; ++i) {
        if (p->type == TYPE_SMALL)
            printf("%d(%d), ", ((tQueueSmall*)p->content)->id, p->type);
        else if (p->type == TYPE_LARGE)
            printf("%d(%d), ", ((tQueueLarge*)p->content)->id, p->type);

        p = p->next;
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

            ret = enqueue(queue, id, score, TYPE_SMALL);

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

            ret = enqueue(queue, id, score, TYPE_LARGE);

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

            tQueueNode *target = NULL;
            target = find_target_node(queue, id, TYPE_SMALL);
            
            // not found
            if (target == NULL) {
                printf("\tCannot find the target id in queue\n");
            }
            else {
                dequeue(queue, target);
            }
            
            printf("\nStatus\n");
            show_buff();

            show_queue(queue);
        }

        else if (operation == 4) {
            printf("\tenter a large id to remove: ");
            scanf("%d", &id);

            tQueueNode* target = NULL;
            target = find_target_node(queue, id, TYPE_LARGE);

            // not found
            if (target == NULL) {
                printf("\tCannor find the target id in queue");
            }
            else {
                dequeue(queue, target);
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
        newQueue->front = NULL;
        newQueue->rear = NULL;
        newQueue->count = 0;
    }

    return newQueue;
}

int enqueue(tQueue* queue, int id, int score, int type) {
    void* ptr_content = NULL;
    int mem_location;

    ourMalloc(type, (void*)&ptr_content, &mem_location);

    if (ptr_content == NULL) {
        printf("\tEnqueue Failded...\n");
        return -1;
    }

    if (type == TYPE_SMALL) {
        ((tQueueSmall*)ptr_content)->id = id;
        ((tQueueSmall*)ptr_content)->score = score;
        ((tQueueSmall*)ptr_content)->location = mem_location;

    }

    else if (type == TYPE_LARGE) {
        ((tQueueLarge*)ptr_content)->id = id;
        ((tQueueLarge*)ptr_content)->score[0] = score;
        ((tQueueLarge*)ptr_content)->location = mem_location;
    }

    tQueueNode* newNode;
    newNode = (tQueueNode*)malloc(sizeof(tQueueNode));
    newNode->type = type;
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->content = ptr_content;

    if (queue->count == 0) {
        queue->front = newNode;
    }
    else {
        queue->rear->next = newNode;
    }

    newNode->prev = queue->rear;
    queue->rear = newNode;
    ++queue->count;

    return 1;
}

void ourMalloc(int type, void **target, int *mem_location) {
    if (type == TYPE_SMALL) {
        // found in small buffer
        if (byte_small_buf_mask < 255) {
            *mem_location = test_single_location(byte_small_buf_mask, NUM_SMALL_BYTE_BUF);

            *target = &buffer[*mem_location * SMALL_ELEMENT_SIZE];

            set_single_bit(&byte_small_buf_mask, *mem_location);
        }

        // found in large buffer
        else if (byte_large_buf_mask < 255) {
            *mem_location = test_single_location(byte_large_buf_mask, NUM_LARGE_BYTE_BUF);

            *target = &buffer[LARGE_BUFFER_START + *mem_location * LARGE_ELEMENT_SIZE];

            set_single_bit(&byte_large_buf_mask, *mem_location);

            *mem_location += NUM_SMALL_BYTE_BUF;
        }

        // not found any empty
        else {
            return;
        }
    }

    else if (type == TYPE_LARGE) {
        // found in large buffer
        if (byte_large_buf_mask < 255) {
            *mem_location = test_single_location(byte_large_buf_mask, NUM_LARGE_BYTE_BUF);

            *target = &buffer[LARGE_BUFFER_START + *mem_location * LARGE_ELEMENT_SIZE];

            set_single_bit(&byte_large_buf_mask, *mem_location);

            *mem_location += NUM_SMALL_BYTE_BUF;
        }

        // found in small buffer
        else if (byte_small_buf_mask < 255){
            *mem_location = test_dual_location(byte_small_buf_mask, NUM_SMALL_BYTE_BUF);
            
            // can not find capacity in small buffer
            if (*mem_location >= NUM_SMALL_BYTE_BUF) return;
            *target = &buffer[*mem_location * SMALL_ELEMENT_SIZE];

            set_single_bit(&byte_small_buf_mask, *mem_location);
            set_single_bit(&byte_small_buf_mask, *mem_location + 1);            
        }
        // not found
        else {
            return;
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

tQueueNode* find_target_node(tQueue* queue, int id, int type) {
    tQueueNode* target = queue->front;

    for (int i = 0; i < queue->count; ++i) {
        if (type == target->type) {
            if (type == TYPE_SMALL && ((tQueueSmall*)target->content)->id == id) {
                return target;
            }
            else if (type == TYPE_LARGE && ((tQueueLarge*)target->content)->id == id) {
                return target;
            }
        }
        
        target = target->next;
    }

    return NULL;
}

int dequeue(tQueue* queue, tQueueNode* target) {
    if (queue->count == 1)
    {
        queue->front = NULL;
        queue->rear = NULL;
    }
    else if (target == queue->front) {
        queue->front = queue->front->next;
    }
    else if (target == queue->rear) {
        queue->rear = queue->rear->prev;
    }
    else {
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }

    --queue->count;

    if (target->type == TYPE_SMALL) {
        ourFree(TYPE_SMALL, ((tQueueSmall*)target->content)->location);
    }
    else if (target->type == TYPE_LARGE) {
        ourFree(TYPE_LARGE, ((tQueueLarge*)target->content)->location);
    }

    free(target);
    
    return 1;
}


void ourFree(int type, int mem_location) {
    if (type == TYPE_SMALL) {
        // in small buffre
        if (mem_location < NUM_SMALL_BYTE_BUF) {
            clear_single_bit(&byte_small_buf_mask, mem_location);
        }

        // in large buffer
        else {
            mem_location -= NUM_SMALL_BYTE_BUF;

            clear_single_bit(&byte_large_buf_mask, mem_location);
        }
    }

    else if (type == TYPE_LARGE) {
        // in large buffer
        if (mem_location >= NUM_SMALL_BYTE_BUF) {
            mem_location -= NUM_SMALL_BYTE_BUF;

            clear_single_bit(&byte_large_buf_mask, mem_location);
        }

        // in small buffer
        else {
            clear_single_bit(&byte_small_buf_mask, mem_location);
            clear_single_bit(&byte_small_buf_mask, mem_location + 1);
        }
    }
}

void clear_single_bit(unsigned char* mask, int mem_location) {
    *mask &= ~(1 << mem_location);
}


// void dequeue_type_large(tQueue* queue, tQueueLarge* target) {
//     if (queue->num_type_large == 1) {
//         queue->type_large_front = NULL;
//         queue->type_large_rear = NULL;
//     }
//     else if (target == queue->type_large_front) {
//         queue->type_large_front = target->next;
//     }
//     else if (target == queue->type_large_rear) {
//         queue->type_large_rear = target->prev;
//     }
//     else {
//         target->prev->next = target->next;
//         target->next->prev = target->prev;
//     }

//     --queue->num_type_large;
//     ourFree(TYPE_LARGE, target, target->location);
// }

// tQueueLarge* find_target_large_node(tQueue* queue, int id) {
//     tQueueLarge* p = queue->type_large_front;
//     while (p) {
//         if (p->id == id)
//             return p;
//         p = p->next;
//     }

//     return NULL;
// }

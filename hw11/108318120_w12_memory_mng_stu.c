#include <stdio.h>
#include <stdlib.h>

#define TYPE_SMALL 0
#define TYPE_LARGE 1

#define NUM_SMALL_BYTE_BUF     8
#define NUM_LARGE_BYTE_BUF     8

#define SMALL_ELEMENT_SIZE  32
#define LARGE_ELEMENT_SIZE  64
#define LARGE_START (SMALL_ELEMENT_SIZE*NUM_SMALL_BYTE_BUF)

unsigned char buffer[NUM_SMALL_BYTE_BUF*NUM_SMALL_BYTE_BUF + NUM_LARGE_BYTE_BUF*LARGE_ELEMENT_SIZE];

unsigned char byte_large_buf_mask = 0;
unsigned char byte_small_buf_mask = 0;

typedef struct type_small {
    int id;
    int score;
    int location;
    struct type_small *next;
    struct type_small *prev;
}tQueueSmall; 

typedef struct type_large {
    int id;
    int score[8];
    int location;
    struct type_large *next;
    struct type_large *prev;
}tQueueLarge; 

typedef struct {
    tQueueSmall *type_small_front;
    tQueueSmall *type_small_rear;
    tQueueLarge *type_large_front;
    tQueueLarge *type_large_rear;
    int type_small_count;
    int type_large_count;
}tQueue;


tQueue* createQueue(void);

int enqueue_type_small(tQueue *queue, int id, int score);
int dequeue_type_small(tQueue *queue, tQueueSmall *target);
tQueueSmall *find_target_small_node(tQueue *queue, int id);

int enqueue_type_large(tQueue *queue, int id, int score);          
int dequeue_type_large(tQueue *queue, tQueueLarge *target);         
tQueueLarge *find_target_large_node(tQueue *queue, int id); 

void print_queue(tQueue *queue);
void print_buffer_status(void);

void  ourMalloc(int type, int size, void **target, int *mem_location);
void  ourFree(int type, void *target, int mem_location);  

int test_single_location(int mask, int mask_length);
void set_single_bit(unsigned char *mask, int location);
int test_dual_location(int mask, int mask_length);

void set_dual_bit(unsigned char *mask, int location);
void clear_single_bit(unsigned char *mask, int location);
void clear_dual_bit(unsigned char *mask, int location);


int main (void)
{
    tQueue *queue;
    int operation;
    tQueueSmall *target_type_small;
    tQueueLarge *target_type_large;
    int id, score=0, ret;
    queue = createQueue();

    while (1)
    {

        printf("\nWhich type you are going to operate? \n");
        printf("1. Add a type 1 item\n");
        printf("2. Add a type 2 item\n");
        printf("3. remove a type 1 item with a specific Id\n");
        printf("4. remove a type 2 item with a specific Id\n");
        
        scanf("%d", &operation);
        
        if (operation == 1)
        {
            printf("  enter id:");
            scanf("%d", &id);

            ret = enqueue_type_small(queue, id, score);
          
            if (ret == 0)
            {
                printf("    Cannot enter to the queue\n");
            }
            print_buffer_status();
        }
        else if (operation == 2)
        {
            printf("  enter id: ");
            scanf("%d", &id);

            ret = enqueue_type_large(queue, id, score);
          
            if (ret == 0)
            {
                printf("    Cannot enter to the queue \n");
            }
            print_buffer_status();

        }
        else if (operation == 3)
        {
            printf ("  enter an ID to remove \n");
            scanf("%d", &id);
            target_type_small = NULL;
            target_type_small = find_target_small_node(queue, id);
            if (target_type_small == NULL)
            {
                printf ("    cannot find the target node \n");
            }
            else
            {
                dequeue_type_small(queue, target_type_small);
            }
            print_buffer_status();

        }
        else if (operation == 4)
        {
            printf ("enter an ID to remove \n");
            scanf("%d", &id);
            target_type_large = NULL;
            target_type_large = find_target_large_node (queue, id);
            if (target_type_large == NULL)
            {
                printf ("    cannot find the target node \n");
            }
            else
            {
                dequeue_type_large(queue, target_type_large);
            } 
            print_buffer_status();
        }
        else 
        {
            printf ("    no such operation \n");   
        }
        print_queue(queue);
    }

}


tQueue* createQueue(void){    
    tQueue *queue;
    queue=(tQueue *) malloc (sizeof(tQueue));

    if (queue)
    {
        queue->type_small_front=NULL;
        queue->type_small_rear=NULL;
        queue->type_large_front=NULL;
        queue->type_large_rear=NULL;        
        queue->type_small_count=0;
        queue->type_large_count=0;
    }

    return queue;
}

int enqueue_type_small(tQueue *queue, int id, int score)
{
    tQueueSmall *newptr = NULL;
    int mem_location;

    ourMalloc (TYPE_SMALL, sizeof(tQueueSmall), (void *)&newptr, &mem_location);
    
    if (newptr == NULL)
    {
        printf("    Enqueue False!!! \n");
        return 0;
    }
    
    newptr->id = id;
    newptr->score = score;
    newptr->next=NULL;
    newptr->prev=NULL;
    newptr->location = mem_location;

    if (queue->type_small_count==0)
    {
        queue->type_small_front = newptr;
    }
    else
    {
        queue->type_small_rear->next = newptr;
    }
    
    newptr->prev = queue->type_small_rear;        
    queue->type_small_rear = newptr;    
    queue->type_small_count++;
    
    return 1;
}

int dequeue_type_small(tQueue *queue, tQueueSmall *target)
{
    
    if (queue->type_small_count == 1)
    {
        queue->type_small_rear = queue->type_small_front = NULL;
    }
    else if (target == queue->type_small_front)
    {
        queue->type_small_front = queue->type_small_front->next;
    }
    else if (target == queue->type_small_rear)
    {
        queue->type_small_rear = queue->type_small_rear->prev;
    }
    else
    {
        target->prev->next = target->next;
    }
    
    queue->type_small_count--; 
    ourFree(TYPE_SMALL, target, target->location);

    return 1;    
}

tQueueSmall *find_target_small_node(tQueue *queue, int id)
{
    int i;
    tQueueSmall *target = queue->type_small_front;
    
    for (i = 0; i < queue->type_small_count; i++)
    {
        if (target->id == id)
        {
            return target;
        }
        else
        {
            target = target->next;
        }
    }
    return NULL;
}

int enqueue_type_large(tQueue *queue, int id, int score)
{
    tQueueLarge *newptr = NULL;
    int mem_location;

    ourMalloc (TYPE_LARGE, sizeof(tQueueLarge), (void *)&newptr, &mem_location);
    
    if (newptr == NULL)
    {
        printf("    Enqueue False!!! \n");
        return 0;
    }
    
    newptr->id = id;
    newptr->score[0] = score;
    newptr->next=NULL;
    newptr->prev=NULL;
    newptr->location = mem_location;

    if (queue->type_large_count==0)
    {
        queue->type_large_front = newptr;
    }
    else
    {
        queue->type_large_rear->next = newptr;
    }
    
    newptr->prev = queue->type_large_rear;        
    queue->type_large_rear = newptr;    
    queue->type_large_count++;
    
    return 1;
}

int dequeue_type_large(tQueue *queue, tQueueLarge *target)
{
    
    if (queue->type_large_count == 1)
    {
        queue->type_large_rear = queue->type_large_front = NULL;
    }
    else if (target == queue->type_large_front)
    {
        queue->type_large_front = queue->type_large_front->next;
    }
    else if (target == queue->type_large_rear)
    {
        queue->type_large_rear = queue->type_large_rear->prev;
    }
    else
    {
        target->prev->next = target->next;
    }
    
    queue->type_large_count--;
    printf("target LOC: %d \n\n", target->id);
    ourFree(TYPE_LARGE, target, target->location);

    return 1;    
}

tQueueLarge *find_target_large_node(tQueue *queue, int id)
{
    int i;
    tQueueLarge *target = queue->type_large_front;
    
    for (i = 0; i < queue->type_large_count; i++)
    {
        if (target->id == id)
        {
            return target;
        }
        else
        {
            target = target->next;
        }
    }
    return NULL;
}



void print_queue (tQueue *queue)
{
    int i;
    tQueueSmall *target = queue->type_small_front;

    printf("      type small queue: ");    
    for (i = 0; i < queue->type_small_count; i++)
    {
        printf ("%d ", target->id);
        target = target->next;
    }
    printf("\n");

    tQueueLarge *target_large = queue->type_large_front;

    printf("      type large queue: ");    
    for (i = 0; i < queue->type_large_count; i++)
    {
        printf ("%d ", target_large->id);
        target_large = target_large->next;
    }
    printf("\n");
}

void print_buffer_status (void)
{
    int i;
    unsigned char mask = 0x80;
  
    printf ("      byte_small_buf_mask: ");
    for (i = 0; i< 8; i++)
    {
        printf ("%d ", (byte_small_buf_mask&mask) >> (7-i));
        mask = mask >> 1;
    }

    mask = 0x80;
    printf ("\n      byte_large_buf_mask: ");
    for (i = 0; i< 8; i++)
    {
        printf ("%d ", (byte_large_buf_mask&mask) >> (7-i));
        mask = mask >> 1;
    }    
    printf ("\n");
}

void  ourMalloc(int type, int size, void **target, int *mem_location)
{

    if (type == 0)
    {
        *mem_location = test_single_location(byte_small_buf_mask, 8);
        if (*mem_location == 8)
        {
            *mem_location = test_single_location(byte_large_buf_mask, 8);
            *target = (&buffer[LARGE_START + *mem_location * LARGE_ELEMENT_SIZE]);
            set_single_bit(&byte_large_buf_mask, *mem_location);
            *mem_location = LARGE_START + *mem_location * LARGE_ELEMENT_SIZE;
        }
        else
        {
            *target = (&buffer[*mem_location * SMALL_ELEMENT_SIZE]);
            set_single_bit(&byte_small_buf_mask, *mem_location);
            *mem_location = *mem_location * SMALL_ELEMENT_SIZE;
        }
        
        
    }
    else if(type == 1)
    {
        *mem_location = test_single_location(byte_large_buf_mask, 8);
        if(*mem_location == 8){
            // test dual space in small
            *mem_location = test_dual_location(byte_small_buf_mask, 8);
            printf("CHECK tLOC: %d \n\n", *mem_location);
            if (*mem_location == -1)
            {
                printf("NO SPACE!!!! \n\n");
            }
            else
            {   
                *target = (&buffer[*mem_location * SMALL_ELEMENT_SIZE]);    
                set_dual_bit(&byte_small_buf_mask, *mem_location);
                *mem_location = *mem_location * SMALL_ELEMENT_SIZE;
            }
            
        }
        else
        {
            *target = (&buffer[LARGE_START + *mem_location * LARGE_ELEMENT_SIZE]);
            set_single_bit(&byte_large_buf_mask, *mem_location);
            *mem_location = LARGE_START + *mem_location * LARGE_ELEMENT_SIZE;
        }   
    }
}

int test_single_location(int mask, int mask_length)
{
    unsigned char fmask = 0x80;
    int i = 0;
    int find_idx = -1;
    for (i = 0; i< mask_length; i++)
    {   
        if (((mask&fmask) >> (7-i) == 0) && (i > find_idx))
        {
            find_idx = i;
        }
        fmask = fmask >> 1;
    }
    return (mask_length - 1) - find_idx;
}

void set_single_bit(unsigned char *mask, int location)
{
    *mask |= (1 << location);
}

int test_dual_location(int mask, int mask_length)
{
    unsigned char fmask = 0x80;
    int i = 0;
    int map[8] = {0};
    for (i = 0; i< 8; i++)
    {   
        if ((mask&fmask) >> (7-i) == 0)
        {
            map[7 - i] += 1;
        }
        // printf ("%d ", (byte_small_buf_mask&mask) >> (7-i));
        fmask = fmask >> 1;
    }

    int dual_idx_fund = 0;
    
    for (i = 0; i< 8; i++)
    {   
        if(map[i])
        {
            dual_idx_fund += 1;
        }
        else
        {
            dual_idx_fund = 0;
        }
        if(dual_idx_fund == 2) break;
    }

    if (dual_idx_fund>=2)
        return i - 1;
    else
        return -1;
}

void set_dual_bit(unsigned char *mask, int location)
{
    *mask |= (1 << location);
    *mask |= (1 << location + 1);
}

void clear_single_bit(unsigned char *mask, int location)
{
    *mask &= ~(1 << location);
}

void clear_dual_bit(unsigned char *mask, int location)
{
    *mask &= ~(1 << location);
    *mask &= ~(1 << location + 1);
}

void  ourFree(int type, void *target, int mem_location)
{   
    // printf("OUTFREE LOC: %d \n\n", mem_location);
    if(type == 0)
    {
        mem_location = mem_location / 32;
        // printf("LOC: %d \n", mem_location);
        // target[mem_location * SMALL_ELEMENT_SIZE] &= ~(1 << mem_location);
        clear_single_bit(&byte_small_buf_mask, mem_location);
    }
    else if(type == 1)
    {   
        printf("LOCCC: %d \n\n", mem_location);
        if (mem_location < LARGE_START)
        {
            mem_location = mem_location / 32;
            clear_dual_bit(&byte_small_buf_mask, mem_location);
        }
        else
        {
            mem_location = (mem_location - LARGE_START) / 64;
            // printf("LOCCC :%d", mem_location);
            clear_single_bit(&byte_large_buf_mask, mem_location);
        }
        
       
    }
}

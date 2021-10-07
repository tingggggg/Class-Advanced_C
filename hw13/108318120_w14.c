#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE_SMALL 0
#define TYPE_LARGE 1

#define MULTIPLIER 4

#define NUM_SMALL_BYTE_BUF     (8*MULTIPLIER)
#define NUM_LARGE_BYTE_BUF     (8*MULTIPLIER)

#define SMALL_ELEMENT_SIZE  32
#define LARGE_ELEMENT_SIZE  64
#define LARGE_START (SMALL_ELEMENT_SIZE*NUM_SMALL_BYTE_BUF)

unsigned char buffer[NUM_SMALL_BYTE_BUF*SMALL_ELEMENT_SIZE + NUM_LARGE_BYTE_BUF*LARGE_ELEMENT_SIZE];

unsigned char byte_large_buf_mask[MULTIPLIER] = {0};
unsigned char byte_small_buf_mask[MULTIPLIER] = {0};

typedef struct type_small {
    int id;
    int location;
    int score;
}tQueueSmall; 

typedef struct type_large {
    int id;
    int location;
    int score[8];
}tQueueLarge; 

typedef struct node_info {
    int type;
    void *content;
    struct node_info *next;
    struct node_info *prev;
}tQueueNode; 

typedef struct {
    tQueueNode *front;
    tQueueNode *rear;
    int count;
}tQueue;


tQueue* createQueue(void);

int tqueue_enqueue(tQueue *queue, int id, int score, int type);
int tqueue_dequeue(tQueue *queue, tQueueNode *target);
tQueueNode *find_target_node(tQueue *queue, int id, int type);

void print_queue(tQueue *queue);
void print_buffer_status(void);

void  ourMalloc(int type, void **target, int *mem_location);
void  ourFree(int type, int mem_location); 
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
    tQueueNode *target;
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

            ret = tqueue_enqueue(queue, id, score, TYPE_SMALL);
          
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

            ret = tqueue_enqueue(queue, id, score, TYPE_LARGE);
          
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
            target = NULL;
            target = find_target_node(queue, id, TYPE_SMALL);
            if (target == NULL)
            {
                printf ("    cannot find the target node \n");
            }
            else
            {
                tqueue_dequeue(queue, target);
            }
            print_buffer_status();

        }
        else if (operation == 4)
        {
            printf ("enter an ID to remove \n");
            scanf("%d", &id);
            target = NULL;
            target = find_target_node (queue, id, TYPE_LARGE);
            if (target == NULL)
            {
                printf ("    cannot find the target node \n");
            }
            else
            {
                tqueue_dequeue(queue, target);
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
        queue->front=NULL;
        queue->rear=NULL;
        queue->count=0;
    }

    return queue;
}

int tqueue_enqueue(tQueue *queue, int id, int score, int type)
{
    int mem_location;

    void *ptr_content = NULL;
    if (type == TYPE_SMALL)
    {   
        ourMalloc (TYPE_SMALL, &ptr_content, &mem_location);
        if (ptr_content == NULL)
        {
            printf("    Enqueue False!!! \n");
            return 0;
        }
        ((tQueueSmall *)ptr_content)->id = id;
        ((tQueueSmall *)ptr_content)->score = score;
        ((tQueueSmall *)ptr_content)->location = mem_location;
    }
    else
    {   
        ourMalloc (TYPE_LARGE, &ptr_content, &mem_location);
        if (ptr_content == NULL)
        {
            printf("    Enqueue False!!! \n");
            return 0;
        }
        ((tQueueLarge *)ptr_content)->id = id;
        ((tQueueLarge *)ptr_content)->score[0] = score;
        ((tQueueLarge *)ptr_content)->location = mem_location;
    }
    
    tQueueNode  *t_node;
    t_node = (tQueueNode*)malloc(sizeof(tQueueNode));
    t_node->type = type;
    t_node->prev = NULL;
    t_node->next = NULL;
    t_node->content = ptr_content;

    
    
    if (queue->count==0)
    {
        queue->front = t_node;
        // queue->rear = t_node;
    }
    else if(queue->count == 1)
    {
        queue->front->next = t_node;
        t_node->prev = queue->front;
        queue->rear = t_node;
    }
    else
    {
        queue->rear->next = t_node;
        t_node->prev = queue->rear;
        queue->rear = t_node;
    }
 
    queue->count++;

}

int tqueue_dequeue(tQueue *queue, tQueueNode *target)
{
    if (queue->count == 1)
    {
        queue->rear = queue->front = NULL;
    }
    else if (target == queue->front)
    {
        queue->front = queue->front->next;
    }
    else if (target == queue->rear)
    {
        queue->rear = queue->rear->prev;
        queue->rear->next = NULL;
    }
    else
    {   
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }
    printf("target : %d \n\n", ((tQueueSmall *)target->content)->id);
    
    queue->count--;
    if(target->type == TYPE_SMALL)
    {
        // printf("target id: %d (%d),  TYPE:(%d) \n\n", ((tQueueSmall *)target->content)->id, ((tQueueSmall *)target->content)->location, target->type);
        ourFree(TYPE_SMALL, ((tQueueSmall *)target->content)->location);
        free(target);
    }
    else
    {
        // printf("target id: %d (%d),  TYPE:(%d) \n\n", ((tQueueLarge *)target->content)->id, ((tQueueLarge *)target->content)->location, target->type);
        ourFree(TYPE_LARGE, ((tQueueLarge *)target->content)->location);
        free(target);
    }
    
    return 1;
}

tQueueNode *find_target_node(tQueue *queue, int id, int type)
{
    int i;
    tQueueNode *target = queue->front;
    
    for (i = 0; i < queue->count; i++)
    {
        if(type == TYPE_SMALL)
        {
            if (((tQueueSmall *)target->content)->id == id && target->type == TYPE_SMALL)
            {
                return target;
            }
        }
        else
        {
            if (((tQueueLarge *)target->content)->id == id && target->type == TYPE_LARGE)
            {
                return target;
            }
        }
        target = target->next;
           
    }
    return NULL;
}

void print_queue (tQueue *queue)
{   
    int i;
    tQueueNode *target = queue->front;
    printf("\ntype mixed queue: ");
    for (i = 0; i < queue->count; i++)
    {   
        if (target->type == TYPE_SMALL)
            printf ("%d(%d) ", ((tQueueSmall*)target->content)->id, target->type);
        else
            printf ("%d(%d) ", ((tQueueLarge*)target->content)->id, target->type);
        target = target->next;
    }
    printf("\n");
}  

void print_buffer_status (void)
{
    int i;
    unsigned char mask = 0x80;
  
    printf ("      byte_small_buf_mask: ");
    for(int j = MULTIPLIER - 1; j >= 0; j--)
    {
        mask = 0x80;

        for (i = 0; i< 8; i++)
        {
            printf ("%d ", (byte_small_buf_mask[j]&mask) >> (7-i));
            mask = mask >> 1;
        }
        printf(" | ");
    }
    

    mask = 0x80;
    printf ("\n      byte_large_buf_mask: ");
    for(int j = MULTIPLIER - 1; j >= 0; j--)
    {   
        mask = 0x80;
        for (i = 0; i< 8; i++)
        {
            printf ("%d ", (byte_large_buf_mask[j]&mask) >> (7-i));
            mask = mask >> 1;
        }
        printf(" | ");   
    }
    
    printf ("\n");
}

void ourMalloc(int type, void **target, int *mem_location)
{
    int location;
    int i;
    if (type == TYPE_SMALL)
    {   
        bool noLargeSpace = true;
        bool noSmallSpace = true;
        for(i = 0; i < MULTIPLIER; i++)
        {
            if (byte_large_buf_mask[i] != 255)
                noLargeSpace = false;
            
            if (byte_small_buf_mask[i] != 255)
                noSmallSpace = false;
        }

        if (noSmallSpace){
            if (noLargeSpace)
            {
                return;
            }
            else
            {
                
                for(i = 0; i < MULTIPLIER; i++)
                {
                    if (byte_large_buf_mask[i] != 255)
                        break;
                }

                location = test_single_location(byte_large_buf_mask[i], NUM_LARGE_BYTE_BUF/MULTIPLIER);
                set_single_bit(&byte_large_buf_mask[i], location);
                *target = &buffer[LARGE_START + (8 * i + location) * LARGE_ELEMENT_SIZE];
                *mem_location = NUM_SMALL_BYTE_BUF + 8 * i + location;
            }
        }
        else
        {   
            for(i = 0; i < MULTIPLIER; i++)
            {
                if (byte_small_buf_mask[i] != 255)
                    break;
            }

            location = test_single_location(byte_small_buf_mask[i], NUM_SMALL_BYTE_BUF/MULTIPLIER);
            set_single_bit(&byte_small_buf_mask[i], location);
            *target = &buffer[(8 * i + location) * SMALL_ELEMENT_SIZE];
            *mem_location = 8 * i + location;
        }
    }
    else
    {

        bool noLargeSpace = true;
        bool noSmallSpace = true;
        for(int i = 0; i < MULTIPLIER; i++)
        {
            if (byte_large_buf_mask[i] != 255)
                noLargeSpace = false;
            
            if (byte_small_buf_mask[i] != 255)
                noSmallSpace = false;
        }

        if (noLargeSpace){
            if (noSmallSpace)
            {
                return;
            }
            else
            {
                for(i = 0; i < MULTIPLIER; i++)
                {
                    
                    if (byte_small_buf_mask[i] != 255)
                    {
                        location = test_dual_location(byte_small_buf_mask[i], NUM_SMALL_BYTE_BUF/MULTIPLIER);
                        if (location != -1)
                            break;
                        else // if location == -1 in this case means only have one slot at rear
                        // so need to check next mask have idx(0) slot or not.
                        {
                            if(i + 1 < MULTIPLIER)
                            {
                                int tmp_loc;
                                tmp_loc = test_single_location(byte_small_buf_mask[i + 1], NUM_SMALL_BYTE_BUF/MULTIPLIER);
                                if(tmp_loc == 0 && (1 & byte_small_buf_mask[i]>>7) == 0)
                                {
                                    set_single_bit(&byte_small_buf_mask[i], 7);
                                    set_single_bit(&byte_small_buf_mask[i + 1], tmp_loc);
                                    *target = &buffer[(8 * i + 7) * SMALL_ELEMENT_SIZE];
                                    *mem_location = 8 * i + 7;
                                }
                                else
                                    continue;
                            }
                            return;
                        }
                        
                    }
                        
                }
                if (location >= 0)
                {
                    set_dual_bit(&byte_small_buf_mask[i], location);
                    *target = &buffer[(8 * i + location) * SMALL_ELEMENT_SIZE];
                    *mem_location = 8 * i + location;
                }
                else
                {
                    return;
                }
            }
        }
        else
        {   

            for(i = 0; i < MULTIPLIER; i++)
            {
                if (byte_large_buf_mask[i] != 255)
                    break;
            }
            location = test_single_location(byte_large_buf_mask[i], NUM_LARGE_BYTE_BUF/MULTIPLIER);
            
            set_single_bit(&byte_large_buf_mask[i], location);
            
            *target = &buffer[LARGE_START + ((8 * i + location) * LARGE_ELEMENT_SIZE)];   
            *mem_location = NUM_SMALL_BYTE_BUF + 8 * i + location;
        }
    }
    
}

int test_single_location(int mask, int mask_length)
{
    int i;

  
    for (i=0; i<mask_length; i++)
    {
        if ((1 & mask>>i) == 0)
        {
            return i;
        }
    }

    
    return -1;
}

void set_single_bit(unsigned char *mask, int location)
{
    *mask = *mask | (1 << location);
}

int test_dual_location(int mask, int mask_length)
{
    int i;
    for (i=0; i<mask_length-1; i++)
    {
        if ((3 & mask>>i) == 0)
        {
            return i;
        }
    }
    return -1;
}

void set_dual_bit(unsigned char *mask, int location)
{
    *mask = *mask | (1 << location);
    *mask = *mask | (1 << (location+1));
}

void clear_single_bit(unsigned char *mask, int location)
{
    *mask = *mask & ~(1 << location);
}

void clear_dual_bit(unsigned char *mask, int location)
{
    *mask = *mask & ~(1 << location);
    *mask = *mask & ~(1 << (location+1));
}

void  ourFree(int type, int mem_location)
{
    if (type == TYPE_SMALL)
    {
        if (mem_location < NUM_SMALL_BYTE_BUF)
        {
            int maskIdx = mem_location / 8;
            clear_single_bit(&byte_small_buf_mask[maskIdx], mem_location % 8);
        }
        else
        {
            int maskIdx = (mem_location-NUM_SMALL_BYTE_BUF) / 8;
            clear_single_bit(&byte_large_buf_mask[maskIdx], (mem_location-NUM_SMALL_BYTE_BUF) % 8);
        }
    }
    if (type == TYPE_LARGE)
    {

        if (mem_location < NUM_SMALL_BYTE_BUF)
        {
            int maskIdx = mem_location / 8;
            if(mem_location - 8 * maskIdx == 7){
                clear_single_bit(&byte_small_buf_mask[maskIdx], mem_location - 8 * maskIdx);
                clear_single_bit(&byte_small_buf_mask[maskIdx + 1], 0);
            }
            else
                clear_dual_bit(&byte_small_buf_mask[maskIdx], mem_location - 8 * maskIdx);
        }
        else
        {
            int maskIdx = (mem_location-NUM_SMALL_BYTE_BUF) / 8;
            clear_single_bit(&byte_large_buf_mask[maskIdx], (mem_location-NUM_SMALL_BYTE_BUF) % 8);

        }
    }
}

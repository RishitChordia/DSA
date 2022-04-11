#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct strings{
    char string[25];
};

struct queue_struct{
    int queue_size;
    int index_tail;
    int index_head;
    struct strings arr[100000];
};

int index_increment(int index , int queue_size){
    // makes the head and tail increase in a cyclic manner within the array
    if (index <= queue_size-2)
    {
        return index+1;
    }
    else if (index == queue_size -1)
    {
        return 0;
    }
}

int QUEUEFULL(struct queue_struct *input_queue){
    if ((input_queue->index_tail == (input_queue->queue_size - 1)) && (input_queue->index_head == 0))
    {
        return -1;
    }
    else if (input_queue->index_head == input_queue->index_tail + 1)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

void QUEUEFULL_PRINT(struct queue_struct *input_queue){
    printf("%d\n" , QUEUEFULL(input_queue));
}

int QUEUEEMPTY(struct queue_struct *input_queue){
    if (input_queue->index_tail == input_queue->index_head)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

void QUEUEEMPTY_PRINT(struct queue_struct *input_queue){
    printf("%d\n" , QUEUEEMPTY(input_queue));
}


void ENQUEUE(struct queue_struct *input_queue , char new_element[]){
    if (QUEUEFULL(input_queue) == -1)
    {
        printf("-1\n");
        return;
    }
    else
    {
        strcpy(input_queue->arr[input_queue->index_tail].string , new_element);
        input_queue->index_tail = index_increment(input_queue->index_tail , input_queue->queue_size);
        return;
    }
}

void DEQUEUE(struct queue_struct *input_queue){
    if (QUEUEEMPTY(input_queue) == -1)
    {
        printf("-1\n");
        return;
    }
    else
    {
        printf("%s\n" , input_queue->arr[input_queue->index_head].string);
        input_queue->index_head = index_increment(input_queue->index_head , input_queue->queue_size);
        return;
    }
}

int main(){
    int queue_size;
    char input_char;
    char new_element[25];
    struct queue_struct *input_queue;
    input_queue = (struct queue_struct*)malloc(sizeof(struct queue_struct));
    scanf("%d" , &queue_size);
    input_queue->queue_size = queue_size;
    input_queue->index_head = 0;
    input_queue->index_tail = 0;
    scanf("%c" , &input_char);
    while (input_char != 't')
    {
        if (input_char == 'i')
        {
            scanf("%s" , &new_element);
            ENQUEUE(input_queue , new_element);
        }
        else if (input_char == 'd')
        {
            DEQUEUE(input_queue);
        }
        else if (input_char == 'f')
        {
            QUEUEFULL_PRINT(input_queue);
        }
        else if (input_char == 'e')
        {
            QUEUEEMPTY_PRINT(input_queue);
        }
        scanf("\n%c" , &input_char);
    }
    return 0;
}

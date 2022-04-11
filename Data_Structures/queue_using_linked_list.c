
#include <stdio.h>
#include <stdlib.h>

struct node { 
    int value; 
    struct node *next; 
};

typedef struct node *node;

struct queue
{
    node head;
    node tail;
};

typedef struct queue *queue;

int QUEUE_EMPTY(queue S){
    if(S->head == NULL){
        return -1;
    }
    else return 1;
}

node CREATE_NODE(int value) {
    node temp;
    temp = (node)malloc(sizeof(node));
    if(temp == NULL)
        exit(0);
    temp->value = value;
    temp->next = NULL;
    return temp;
}

void ENQUEUE(queue S, node x){
    if (QUEUE_EMPTY(S) == -1)
    {
        S->head = x;
        S->tail = x;
    }
    else{
        S->tail->next = x;
        S->tail = x;
        x->next = NULL;
    }
}

void DEQUEUE(queue S){
    if (QUEUE_EMPTY(S) == -1)
    {
        printf("-1\n");
    }
    else
    {
        printf("%d\n" , (S->head)->value);
        S->head = (S->head)->next;
    }
}

int main()
{
    int in1 , in2;
    char input_char;
    queue S;
    S = (queue)malloc(sizeof(struct queue));
    S->head = NULL;
    S->tail = NULL;
    scanf("%c" , &input_char);
    while (input_char != 't')
    {
        if (input_char == 'i')
        {
            scanf("%d" , &in1);
            ENQUEUE(S , CREATE_NODE(in1));
        }
        else if (input_char == 'd')
        {
            DEQUEUE(S);
        }
        else if (input_char == 'e')
        {
            printf("%d\n" , QUEUE_EMPTY(S));
        }
        scanf("\n%c" , &input_char);
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

struct node { 
    int value; 
    struct node *next; 
};

typedef struct node *node;

struct top
{
    node top;
};

typedef struct top *top;

int STACK_EMPTY(top S){
    if(S->top == NULL){
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

void PUSH(top S, node x){
    x->next = S->top;
    S->top = x;
}

void POP(top S){
    if (S->top == NULL)
    {
        printf("-1\n");
    }
    else
    {
        printf("%d\n" , (S->top)->value);
        S->top = (S->top)->next;
    }
}

int main()
{
    int in1 , in2;
    char input_char;
    top S;
    S = (top)malloc(sizeof(top));
    S->top = NULL;
    scanf("%c" , &input_char);
    while (input_char != 't')
    {
        if (input_char == 'i')
        {
            scanf("%d" , &in1);
            PUSH(S , CREATE_NODE(in1));
        }
        else if (input_char == 'd')
        {
            POP(S);
        }
        else if (input_char == 'e')
        {
            printf("%d\n" , STACK_EMPTY(S));
        }
        scanf("\n%c" , &input_char);
    }
    return 0;
}

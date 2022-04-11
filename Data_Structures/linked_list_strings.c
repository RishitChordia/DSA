#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node { 
    char value[300];
    struct node *next; 
};
typedef struct node *node;

struct head
{
    node head;
};
typedef struct head *head;

node CREATE_NODE(char value[]) {
    node temp;
    temp = (node)malloc(sizeof(struct node));
    if(temp == NULL)
        exit(0);
    strcpy(temp->value , value);
    temp->next = NULL;
    return temp;
}

void LIST_INSERT(head L , node x){
    if (L->head == NULL)
    {
        L->head = x;
    }
    else{
        node current;
        current = (node)malloc(sizeof(struct node));
        current = L->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = x;
    }
}

void PRINT_LIST(head L){
    node current;
    current = (node)malloc(sizeof(struct node));
    current = L->head;
    if (current != NULL)
    {
        printf("%s" , current->value);
        current = current->next;
    }
    while (current != NULL)
    {
        printf(" %s" , current->value);
        current = current->next;
    }
    printf("\n");
    free(current);
}

int main()
{
    return 0;
}
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
    // temp->value = value;
    temp->next = NULL;
    return temp;
}

void HASH_INSERT(head L , node x){
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
            if (strcmp(current->value , x->value) == 0)
            {
                return;
            }
            current = current->next;
        }
        current->next = x;
    }
}

void PRINT_LIST(head L){
    node current;
    current = (node)malloc(sizeof(struct node));
    current = L->head;
    if (current == NULL)
    {
        printf("null");
    }
    
    if (current != NULL)
    {
        printf("%s" , current->value);
        current = current->next;
    }
    while (current != NULL)
    {
        printf("-%s" , current->value);
        current = current->next;
    }
    free(current);
}

int main()
{
    int size_k , length , index;
    scanf("%d" , &size_k);
    head hash_table_arr[size_k];
    // arr = (head*)malloc(size_k * (sizeof(struct head)));
    for (int i = 0; i < size_k; i++)
    {
        head input;
        input = (head)malloc(sizeof(struct head));
        input->head = NULL;
        hash_table_arr[i] = input;
    }
    char value[300];
    // value = malloc(2000);
    while (scanf("%s" , value) && value[0] != '(')
    {
        length = strlen(value);
        index = (length*length)%size_k;
        HASH_INSERT(hash_table_arr[index] , CREATE_NODE(value));
        value[0] = '(';
    }
    for (int i = 0; i < size_k; i++)
    {
        printf("%d:" , i);
        PRINT_LIST(hash_table_arr[i]);
        if (i < size_k - 1)
        {
            printf("\n");
        }
    }
    
    return 0;
}
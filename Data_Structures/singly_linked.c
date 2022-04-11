#include <stdio.h>
#include <stdlib.h>

struct node { 
    char value; 
    struct node *next; 
};
typedef struct node *node;
struct head
{
    node head;
};
typedef struct head *head;

node CREATE_NODE(char value) {
    node temp;
    temp = (node)malloc(sizeof(node));
    if(temp == NULL)
        exit(0);
    temp->value = value;
    temp->next = NULL;
    return temp;
}

void LIST_INSERT_FRONT(head L, node x){
    x->next = L->head;
    L->head = x;
}

void LIST_INSERT_TAIL(head L , node x){
    if (L->head == NULL)
    {
        L->head = x;
    }
    else{
        node current;
        current = (node)malloc(sizeof(node));
        current = L->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = x;
    }
}

void LIST_INSERT_AFTER(head L , char key , char search_value){
    node current;
    current = (node)malloc(sizeof(node));
    current = L->head;
    node temp;
    temp = CREATE_NODE(key);
    while (current != NULL)
    {
        if (current->value == search_value)
        {
            temp->next = current->next;
            current->next = temp;
            return;
        }
        current = current->next;
    }
}

void LIST_INSERT_BEFORE(head L , char key , char search_value){
    node current;
    current = (node)malloc(sizeof(node));
    current = L->head;
    node temp;
    temp = CREATE_NODE(key);
    while (current != NULL)
    {
        if ((current->next)->value == search_value)
        {
            temp->next = current->next;
            current->next = temp;
            return;
        }
        current = current->next;
    }
}

void LIST_DELETE(head L , char search_value){
    node current;
    current = (node)malloc(sizeof(node));
    current = L->head;
    if (current->value == search_value)
    {
        L->head = current->next;
        if (current->next == NULL)
        {
            printf("-2\n");
        }
        else
        {
            printf("%c\n" , current->next->value);
        }
        return;
    }
    while (current->next != NULL)
    {
        if ((current->next)->value == search_value)
        {
            if((current->next)->next == NULL){
                current->next = NULL;
                printf("-2\n");
                return;
            }
            else
            {
                printf("%c\n" , current->next->next->value);
                current->next = (current->next)->next;
                return;
            }
        }
        current = current->next;
    }
    printf("-1\n");
}

void LIST_DELETE_FIRST(head L){
    if (L->head == NULL)
    {
        printf("-1\n");
    }
    else
    {
        printf("%c\n" , (L->head)->value);
        L->head = (L->head)->next;
    }
}

void LIST_DELETE_LAST(head L){
    if (L->head == NULL)
    {
        printf("-1\n");
        return;
    }
    if (L->head->next == NULL)
    {
        printf("%c\n" , (L->head)->value);
        L->head = NULL;
        return;
    }
    else{
        node current;
        current = (node)malloc(sizeof(node));
        current = L->head;
        while (current->next->next != NULL)
        {
            current = current->next;
        }
        printf("%c\n" , (current->next)->value);
        current->next = NULL;
        return;
    }
}

node LIST_SEARCH(head L , char search_value){
    node current;
    current = (node)malloc(sizeof(node));
    current = L->head;
    if (current == NULL)
    {
        current = NULL;
        return current;
    }
    else
    {
        while (current != NULL && current->value == search_value)
        {
            current = current->next;
        }
        return current;
    }
}

void PRINT_LIST(head L){
    node current;
    current = (node)malloc(sizeof(node));
    current = L->head;
    if (current != NULL)
    {
        printf("%c" , current->value);
        current = current->next;
    }
    while (current != NULL)
    {
        printf(" %c" , current->value);
        current = current->next;
    }
    printf("\n");
    free(current);
}

int main()
{
    char in1 , in2;
    char input_char;
    head input;
    input = (head)malloc(sizeof(head));
    input->head = NULL;
    scanf("%c" , &input_char);
    while (input_char != 'e')
    {
        if (input_char == 'f')
        {
            scanf(" %c" , &in1);
            LIST_INSERT_FRONT(input , CREATE_NODE(in1));
        }
        else if (input_char == 't')
        {
            scanf(" %c" , &in1);
            LIST_INSERT_TAIL(input , CREATE_NODE(in1));
        }
        else if (input_char == 'a')
        {
            scanf(" %c" , &in1);
            scanf(" %c" , &in2);
            LIST_INSERT_AFTER(input , in1 , in2);
        }
        else if (input_char == 'b')
        {
            scanf(" %c" , &in1);
            scanf(" %c" , &in2);
            LIST_INSERT_BEFORE(input , in1 , in2);
        }
        else if (input_char == 'd')
        {
            scanf(" %c" , &in1);
            LIST_DELETE(input , in1);
        }
        else if (input_char == 'i')
        {
            LIST_DELETE_FIRST(input);
        }
        else if (input_char == 'l')
        {
            LIST_DELETE_LAST(input);
        }
        else if (input_char == 'p')
        {
            PRINT_LIST(input);
        }
        scanf("\n%c" , &input_char);
    }
    return 0;
}

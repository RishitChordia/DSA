#include <stdio.h>
#include <stdlib.h>

struct tree
{
    int value;
    struct tree *left_child, *right_child, *parent;
};

typedef struct tree *tree_node;

struct tree_root
{
    tree_node root;
};

typedef struct tree_root *tree_root;


struct queue_node { 
    tree_node value; 
    struct queue_node *next;
};

typedef struct queue_node *queue_node;

struct queue
{
    queue_node head;
    queue_node tail;
};

typedef struct queue *queue;

int QUEUE_EMPTY(queue S){
    if(S->head == NULL){
        return -1;
    }
    else return 1;
}

queue_node CREATE_QUEUE_NODE(tree_node value) {
    queue_node temp;
    temp = (queue_node)malloc(sizeof(struct queue_node));
    if(temp == NULL)
        exit(0);
    temp->value = value;
    temp->next = NULL;
    return temp;
}

tree_node CREATE_TREE_NODE(int value)
{
    tree_node temp;
    temp = (tree_node)malloc(sizeof( struct tree));
    if (temp == NULL)
        exit(0);
    temp->value = value;
    temp->left_child = NULL;
    temp->right_child = NULL;
    temp->parent = NULL;
    return temp;
}

void ENQUEUE(queue S, queue_node x){
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
        // printf("-1\n");
    }
    else
    {
        // printf("%d\n" , (S->head)->value);
        S->head = (S->head)->next;
    }
}

tree_node QUEUE_PEEK(queue S){
    if (QUEUE_EMPTY(S) == -1)
    {
        // printf("-1\n");
    }
    else
    {
        return S->head->value;
    }
}

tree_root insert(tree_root root , int key){
    if (root->root == NULL)
    {
        root->root = CREATE_TREE_NODE(key);
        return root;
    }
    queue S;
    S = (queue)malloc(sizeof( struct queue));
    S->head = NULL;
    S->tail = NULL;
    ENQUEUE(S , CREATE_QUEUE_NODE(root->root));
    tree_node current_node;
    current_node = (tree_node)malloc(sizeof(struct tree));
    while (QUEUE_EMPTY(S) == 1)
    {
        current_node = QUEUE_PEEK(S);
        DEQUEUE(S);
        if (current_node->left_child != NULL) /* cant insert since left child is occupied */
        {
            ENQUEUE(S , CREATE_QUEUE_NODE(current_node->left_child));
        }
        else{
            current_node->left_child = CREATE_TREE_NODE(key);
            return root;
        }

        if (current_node->right_child != NULL) /* cant insert since right child is occupied */
        {
            ENQUEUE(S , CREATE_QUEUE_NODE(current_node->right_child));
        }
        else{
            current_node->right_child = CREATE_TREE_NODE(key);
            return root;
        }    
    }
}

void PRINT(tree_node node)
{
    if (node != NULL)
    {
        printf("( ");
        printf("%d ", node->value);
        PRINT(node->left_child);
        PRINT(node->right_child);
        printf(") ");
    }
    else{
        printf("( ) ");
    }
}

int main()
{
    int in1;
    char input_char;
    tree_root root;
    root = (tree_root)malloc(sizeof(struct tree_root));
    root->root = NULL;
    scanf("%c" , &input_char);
    while (input_char != 'e')
    {
        if (input_char == 'i')
        {
            scanf("%d" , &in1);
            insert(root , in1);
        }
        else if (input_char == 'p')
        {
            PRINT(root->root);
        }
        scanf("\n%c" , &input_char);
    }
    return 0;
}

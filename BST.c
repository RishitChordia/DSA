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

void insert(tree_root input_tree , tree_node new_node){
    tree_node temp;
    temp = (tree_node)malloc(sizeof( struct tree ));
    new_node->parent = NULL;
    new_node->right_child = NULL;
    new_node->left_child = NULL;
    if (input_tree->root == NULL)
    {
        input_tree->root = new_node;
        new_node->parent = NULL;
        return;
    }
    tree_node parent;
    parent = (tree_node)malloc(sizeof( struct tree ));
    temp = input_tree->root;
    while (1)
    {
        if (new_node->value > temp->value)
        {
            parent = temp;
            if (temp->right_child == NULL)
            {
                temp->right_child = new_node;
                new_node->parent = parent;
                return;
            }
            else
            {
                parent = temp;
                temp = temp->right_child;
                continue;
            }
        }
        else if (new_node->value <= temp->value)
        {
            parent = temp;
            if (temp->left_child == NULL)
            {
                temp->left_child = new_node;
                new_node->parent = parent;
                return;
            }
            else
            {
                parent = temp;
                temp = temp->left_child;
                continue;
            }
        }   
    }   
}

tree_node minimum(tree_node node_x){
    while(node_x->left_child != NULL){
        node_x = node_x->left_child;        
    }
    return node_x;
}

tree_node maximum(tree_node node_x){
    while(node_x->right_child != NULL){
        node_x = node_x->right_child;
    }
    return node_x;
}

tree_node search(tree_root input_tree , int data){
    if (input_tree->root == NULL)
    {
        return NULL;
    }
    tree_node temp;
    temp = (tree_node)malloc(sizeof( struct tree ));
    temp = input_tree->root;
    while (temp != NULL)
    {
        if (data == temp->value)
        {
            return temp;
        }
        
        else if (data > temp->value)
        {
            if (temp->right_child == NULL)
            {
                return NULL;
            }
            else
            {
                temp = temp->right_child;
                continue;
            }
        }
        else if (data < temp->value)
        {
            if (temp->left_child == NULL)
            {
                return NULL;
            }
            else
            {
                temp = temp->left_child;
                continue;
            }
        }   
    }   
}

void transplant(tree_root input_tree , tree_node prev , tree_node new){
    if (prev->parent == NULL)
    {
        input_tree->root = new;
    }
    else if(prev->parent->right_child == prev){
        prev->parent->right_child = new;        
    }
    else if(prev->parent->left_child == prev){
        prev->parent->left_child = new;
    }
    if(new != NULL){
        new->parent = prev->parent;
    }
}

tree_node successor(tree_root input_tree , tree_node node_x){
    if (node_x == NULL)
    {
        return NULL;
    }
    if (node_x->right_child != NULL)
    {
        return minimum(node_x->right_child);
    }
    tree_node temp;
    temp = (tree_node)malloc(sizeof( struct tree ));
    temp = node_x->parent;
    while (temp != NULL && node_x == temp->right_child)
    {
        node_x = temp;
        temp = temp->parent;
    }
    return temp;
}

tree_node predecessor(tree_root input_tree , tree_node node_x){
    if (node_x == NULL)
    {
        return NULL;
    }
    if (node_x->left_child != NULL)
    {
        return maximum(node_x->left_child);
    }
    tree_node temp;
    temp = (tree_node)malloc(sizeof( struct tree ));
    temp = node_x->parent;
    while (temp != NULL && node_x == temp->left_child)
    {
        node_x = temp;
        temp = temp->parent;
    }
    return temp;
    
}

void delete(tree_root input_tree , tree_node node_x){
    if (node_x->left_child == NULL)
    {
        transplant(input_tree , node_x , node_x->right_child);
    }
    else if (node_x->right_child == NULL)
    {
        transplant(input_tree , node_x , node_x->left_child);
    }
    else{
        tree_node temp;
        temp = (tree_node)malloc(sizeof( struct tree ));
        temp = successor(input_tree , node_x);
        node_x->value = temp->value;
        delete(input_tree , temp);
    }
}

int LEVEL(tree_root input_tree , int key){
    tree_node temp;
    temp = (tree_node)malloc(sizeof( struct tree ));
    temp = search(input_tree , key);
    if (temp == NULL)
    {
        return -1;
    }
    else{
        int i = 0;
        while (temp != NULL)
        {
            i++;
            temp = temp->parent;
        }
        return i;
    }
}

void INORDER(tree_node node)
{
    if (node != NULL)
    {
        printf("(");
        INORDER(node->left_child);
        printf("%d ", node->value);
        INORDER(node->right_child);
        printf(")");
    }
}

void PREORDER(tree_node node)
{
    if (node != NULL)
    {
        printf("%d ", node->value);
        PREORDER(node->left_child);
        PREORDER(node->right_child);
    }
}

void POSTORDER(tree_node node)
{
    if (node != NULL)
    {
        POSTORDER(node->left_child);
        POSTORDER(node->right_child);
        printf("%d ", node->value);
    }
}

int main()
{
    tree_root root;
    root = (tree_root)malloc(sizeof(struct tree_root));
    root->root = NULL;
    char input_char;
    tree_node buffer;
    buffer = (tree_node)malloc(sizeof( struct tree ));
    int inp , temp;
    scanf("%c " , &input_char);
    while (input_char!= 'e')
    {
        if(input_char == 'a'){
            scanf(" %d" , &inp);
            buffer = CREATE_TREE_NODE(inp);
            insert(root , buffer);
        }
        else if(input_char == 'd'){
            scanf(" %d" , &inp);
            buffer = search(root , inp);
            if (buffer == NULL)
            {
                printf("-1\n");
            }
            else{
                printf("%d\n" , buffer->value);
                delete(root , buffer);
            }    
        }
        else if(input_char == 's'){
            scanf(" %d" , &inp);
            buffer = search(root , inp);
            if (buffer == NULL)
            {
                printf("-1\n");
            }
            else
            {
                printf("1\n");
            }   
        }
        else if(input_char == 'c'){
            scanf(" %d" , &inp);
            buffer = successor(root , search(root , inp));
            if (buffer == NULL)
            {
                printf("-1\n");
            }
            else
            {
                printf("%d\n" , buffer->value);
            } 
        }
        else if(input_char == 'r'){
            scanf(" %d" , &inp);
            buffer = predecessor(root , search(root , inp));
            if (buffer == NULL)
            {
                printf("-1\n");
            }
            else
            {
                printf("%d\n" , buffer->value);
            }
        }
        else if(input_char == 'i'){
            INORDER(root->root);
            printf("\n");
        }
        else if(input_char == 'p'){
            PREORDER(root->root);
            printf("\n");
        }
        else if(input_char == 't'){
            POSTORDER(root->root);
            printf("\n");
        }
        scanf("\n%c" , &input_char);
    }
    return 0;
}



// send it to left if equal
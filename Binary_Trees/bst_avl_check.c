#include <stdio.h>
#include <stdlib.h>

struct tree
{
    int value;
    struct tree *left_child, *right_child;
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
    return temp;
}

int greater(int a, int b)
{
    if (a >= b)
    {
        return a;
    }
    return b;
}

void insert(tree_root input_tree , tree_node new_node){
    tree_node temp;
    temp = (tree_node)malloc(sizeof( struct tree ));
    new_node->right_child = NULL;
    new_node->left_child = NULL;
    if (input_tree->root == NULL)
    {
        input_tree->root = new_node;
        return;
    }

    temp = input_tree->root;
    while (1)
    {
        if (new_node->value > temp->value)
        {
            if (temp->right_child == NULL)
            {
                temp->right_child = new_node;
                return;
            }
            else
            {
                temp = temp->right_child;
                continue;
            }
        }
        else if (new_node->value < temp->value)
        {
            if (temp->left_child == NULL)
            {
                temp->left_child = new_node;
                return;
            }
            else
            {
                temp = temp->left_child;
                continue;
            }
        }   
    }   
}

int height_node(tree_node temp){
    if (temp == NULL)
    {
        return 0;
    }
    else{
        return (greater(height_node(temp->right_child) , height_node(temp->left_child)) + 1);
    }
}

int isavl(tree_node root){
    if (root == NULL)
    {
        return 1;
    }
    else{
        int balance = (height_node(root->left_child) - height_node(root->right_child));
        if (balance >= -1 && balance <= 1 && isavl(root->right_child) && isavl(root->left_child))
        {
            return 1;
        }
        else{
            return 0;
        } 
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
    while (input_char!= 't')
    {
        if(input_char == 'i'){
            scanf(" %d" , &inp);
            buffer = CREATE_TREE_NODE(inp);
            insert(root , buffer);
        }
        else if(input_char == 'c'){
            printf("%d\n" , isavl(root->root));
        }
        scanf("\n%c" , &input_char);
    }
    return 0;
}
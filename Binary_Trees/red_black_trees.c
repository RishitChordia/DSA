#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree
{
    int value;
    char colour;
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
    temp->colour = 'R';
    return temp;
}

int string_to_int(char x[], int n)
{
    int final_ans = 0;
    for (int i = 0; i < n; i++)
    {
        final_ans *= 10;
        final_ans += (x[i] - 48);
    }
    return final_ans;
}

char colour(tree_node temp){
    if (temp == NULL)
    {
        return 'B';
    }
    else{
        return temp->colour;
    }
}

void rightrotate(tree_node n , tree_root root)
{
    tree_node left;
    left = (tree_node)malloc(sizeof(struct tree));
    left = n->left_child;
    n->left_child = left->right_child;
    if (n->left_child != NULL)
        n->left_child->parent = n;
    left->parent = n->parent;

    // replacing left in place of n
    if (n->parent == NULL){
        root->root = left;
    }
    else if (n == n->parent->left_child){
        n->parent->left_child = left;
    }
    else{
        n->parent->right_child = left;
    }

    left->right_child = n;
    n->parent = left;
}

void leftrotate(tree_node n , tree_root root)
{
    tree_node right;
    right = (tree_node)malloc(sizeof(struct tree));
    right = n->right_child;
    n->right_child = right->left_child;

    if (n->right_child != NULL)
        n->right_child->parent = n;
    right->parent = n->parent;

    // replacing right in place of n
    if (n->parent == NULL){
        root->root = right;
    }
    else if (n == n->parent->left_child){
        n->parent->left_child = right;
    }
    else{
        n->parent->right_child = right;
    }

    right->left_child = n;
    n->parent = right;
}

void recolour(tree_node a , tree_node b){
    char a_copy = a->colour;
    a->colour = b->colour;
    b->colour = a_copy;
}

void fixup(tree_root root , tree_node temp){
    if (temp->parent == NULL)
    {
        temp->colour = 'B';
        return;
    }
    if (colour(temp->parent) == 'B')
    {
        return;
    }
    if (temp->parent->parent != NULL){
        tree_node uncle;
        uncle = (tree_node)malloc(sizeof( struct tree ));
        if (temp->parent == temp->parent->parent->left_child)
        {
            uncle = temp->parent->parent->right_child;
        }
        else{
            uncle = temp->parent->parent->left_child;
        }

        if (colour(uncle) == 'R')
        {
            temp->parent->colour = 'B';
            uncle->colour = 'B';
            temp->parent->parent->colour = 'R';
            return fixup(root , temp->parent->parent);
        }

        else if (colour(uncle) == 'B')
        {
            tree_node parent;
            parent = (tree_node)malloc(sizeof( struct tree ));
            tree_node grandparent;
            grandparent = (tree_node)malloc(sizeof( struct tree ));
            parent = temp->parent;
            grandparent = temp->parent->parent;
            // 4 possible cases, right and left triangle and right and left line 
            if (temp == temp->parent->left_child && temp->parent == temp->parent->parent->right_child)
            {
                // triangle case with right rotate 
                rightrotate(temp->parent , root);
                temp = parent;
                parent = temp->parent;
                // resetting temp for next fixup
                return fixup(root , temp);
            }
            else if (temp == temp->parent->right_child && temp->parent == temp->parent->parent->left_child)
            {
                // triangle case with left rotate 
                leftrotate(temp->parent , root);
                temp = parent;
                parent = temp->parent;
                // resetting temp for next fixup
                return fixup(root , temp);
            }
            else if (temp == temp->parent->left_child && temp->parent == temp->parent->parent->left_child)
            {
                // line case with right rotate
                rightrotate(grandparent , root);
                recolour(grandparent , parent);
                temp = parent;
                return fixup(root , temp);
            }
            else if (temp == temp->parent->right_child && temp->parent == temp->parent->parent->right_child)
            {
                // line case with left rotate
                leftrotate(grandparent , root);
                recolour(grandparent , parent);
                temp = parent;
                return fixup(root , temp);
            }
        }
    }
}

void PRINT(tree_node node)
{
    if (node != NULL)
    {
        printf("( ");
        printf("%d %c ", node->value , node->colour);
        PRINT(node->left_child);
        PRINT(node->right_child);
        printf(") ");
    }
    else
    {
        printf("( ) ");
    }
}

void insert_red_black(tree_root input_tree , tree_node new_node){
    tree_node temp;
    temp = (tree_node)malloc(sizeof( struct tree ));
    new_node->parent = NULL;
    new_node->right_child = NULL;
    new_node->left_child = NULL;
    new_node->colour = 'R';
    if (input_tree->root == NULL)
    {
        input_tree->root = new_node;
        new_node->parent = NULL;
        fixup(input_tree , new_node);
        return PRINT(input_tree->root);
    }
    tree_node parent;
    parent = (tree_node)malloc(sizeof( struct tree ));
    temp = input_tree->root;
    while (1)
    {
        if (new_node->value >= temp->value)
        {
            parent = temp;
            if (temp->right_child == NULL)
            {
                temp->right_child = new_node;
                new_node->parent = parent;
                fixup(input_tree , new_node);
                return PRINT(input_tree->root);
            }
            else
            {
                parent = temp;
                temp = temp->right_child;
                continue;
            }
        }
        else if (new_node->value < temp->value)
        {
            parent = temp;
            if (temp->left_child == NULL)
            {
                temp->left_child = new_node;
                new_node->parent = parent;
                fixup(input_tree , new_node);
                return PRINT(input_tree->root);
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

int main()
{
    tree_root root;
    root = (tree_root)malloc(sizeof(struct tree_root));
    root->root = NULL;
    char input_char , inp[50];
    tree_node buffer;
    buffer = (tree_node)malloc(sizeof( struct tree ));
    int temp , char_len;
    scanf("%s " , &inp);
    while (inp[0] != 't')
    {
        char_len = strlen(inp);
        temp = string_to_int(inp , char_len);
        insert_red_black(root , CREATE_TREE_NODE(temp));
        printf("\n");
        scanf("%s " , &inp);
    }
    return 0;
}
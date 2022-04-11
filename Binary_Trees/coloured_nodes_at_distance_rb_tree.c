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

void insert(tree_root input_tree , tree_node new_node){
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
        return;
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
                return;
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

tree_node search_node(tree_node root, int key)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->value == key)
    {
        return root;
    }
    else
    {
        tree_node x = search_node(root->left_child, key);
        if (x)
            return x;
        return search_node(root->right_child, key);
    }
}

int func_children(tree_node current_node , int distance){
    if (current_node == NULL)
    {
        return 0;
    }
    if (distance == 0)
    {
        if (current_node->colour == 'B')
        {
            return 1;
        }
        return 0;
    }
    return (func_children(current_node->left_child , distance-1)+func_children(current_node->right_child , distance-1));
}

int func_parents(tree_node current_node , int left , int distance){
    if (current_node == NULL)
    {
        return 0;
    }
    if (distance == 0)
    {
        if (current_node->colour == 'B')
        {
            return 1;
        }
        return 0;
    }
    tree_node temp;
    temp = (tree_node)malloc(sizeof(struct tree));
    temp = current_node->parent;
    int left_next;

    if (temp == NULL)
    {
        if (left)
        {
            return (func_children(current_node->left_child , distance - 1));
        }
        else {
            return (func_children(current_node->right_child , distance - 1));
        } 
    }
    else{
        if (temp->right_child->value == current_node->value)
        {
            left_next = 1;
        }
        else{
            left_next = 0;
        }
    }
    if (left)
    {
        return (func_children(current_node->left_child , distance - 1)+func_parents(current_node->parent , left_next , distance - 1));
    }
    else{
        return (func_children(current_node->right_child , distance - 1)+func_parents(current_node->parent , left_next , distance - 1));
    }
}

int func(tree_node current_node , int distance){
    // func returns 0 if the node is ugly and a positive number if it is beautiful 
    if (current_node == NULL)
    {
        return 0;
    }
    int final = 0;
    final += func_children(current_node , distance);
    tree_node temp;
    temp = (tree_node)malloc(sizeof(struct tree));
    temp = current_node->parent;
    if (temp == NULL)
    {
        return final;
    }
    else{
        if (temp->right_child->value == current_node->value)
        {
            final += func_parents(temp , 1 , distance-1);
        }
        else{
            final += func_parents(temp , 0 , distance-1);
        }  
    }
    return final;
}

int beautiful_counter(tree_node current , int distance){
    if (current == NULL)
    {
        return 0;
    }
    if (func(current , distance))
    {
        return (1 + beautiful_counter(current->left_child , distance) + beautiful_counter(current->right_child , distance));
    }
    else{
        return (beautiful_counter(current->left_child , distance) + beautiful_counter(current->right_child , distance));
    }
}

int main()
{
    tree_root root;
    root = (tree_root)malloc(sizeof(struct tree_root));
    root->root = NULL;
    int distance , n , inp;
    scanf("%d" , &distance);
    scanf("%d" , &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d" , &inp);
        insert(root , CREATE_TREE_NODE(inp));
    }
    printf("%d" , beautiful_counter(root->root , distance));
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

tree_node treeFromString(char str[], int current_index, int end, tree_node parent_node)
{
    char value[7];
    int number;
    if (current_index > end)
    {
        return NULL;
    }

    sscanf(&str[current_index], " %s ", value);
    current_index += (strlen(value) + 1);
    if (value[0] == ')')
    {
        return NULL;
    }
    else if ((value[0] > 47 && value[0] < 58) || (value[0] == '-') /*for negative numbers*/)
    {
        if (value[0] == '-')
        {
            number = -1 * (string_to_int(&value[1], strlen(value) - 1));
        }
        else
        {
            number = string_to_int(value, strlen(value));
        }
    }
    int i, open_count = 0, closed_count = 0;
    tree_node temp;
    temp = (tree_node)malloc(sizeof(struct tree));
    temp->value = number;
    temp->parent = parent_node;
    sscanf(&str[current_index], " %s ", value);
    current_index += (strlen(value) + 1);
    if (value[0] == ')')
    {
        return temp;
    }
    else if (value[0] == '(')
    {
        for (i = current_index; i < end; i++)
        {
            if (str[i] == '(')
            {
                open_count += 1;
            }
            else if (str[i] == ')')
            {
                closed_count += 1;
            }
            if (closed_count > open_count)
            {
                break;
            }
        }
        temp->left_child = treeFromString(str, current_index, i - 1, temp);
        temp->right_child = treeFromString(str, i + 3, end, temp);
        return temp;
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
    if (distance < 0)
    {
        return 0;
    }
    if (current_node == NULL)
    {
        return 0;
    }
    return (current_node->value + func_children(current_node->left_child , distance-1) + func_children(current_node->right_child , distance-1));
}

int func_parents(tree_node current_node , int left , int distance){
    if (current_node == NULL)
    {
        return 0;
    }
    if (distance < 0)
    {
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
            return (current_node->value + func_children(current_node->left_child , distance - 1));
        }
        else {
            return (current_node->value + func_children(current_node->right_child , distance - 1));
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
        return (current_node->value + func_children(current_node->left_child , distance - 1) + func_parents(current_node->parent , left_next , distance - 1));
    }
    else{
        return (current_node->value + func_children(current_node->right_child , distance - 1) + func_parents(current_node->parent , left_next , distance - 1));
    }
}

int func(tree_node current_node , int distance){
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
            final += func_parents(temp , 1 , distance);
        }
        else{
            final += func_parents(temp , 0 , distance-1);
        }  
    }
    return final;
}

int main()
{
    tree_node buffer;
    buffer = (tree_node)malloc(sizeof(struct tree));
    tree_node starting_node;
    starting_node = (tree_node)malloc(sizeof(struct tree));
    starting_node->parent = NULL;
    int inp, temp1 , temp2 , starting_number , distance;
    char string_inp[100000];
    scanf("%[^\n]%*c", string_inp);
    buffer = treeFromString(&string_inp[2], 0, strlen(string_inp) - 4, buffer);
    buffer->parent = NULL;
    scanf("%d" , &starting_number);
    scanf("%d" , &distance);
    starting_node = search_node(buffer , starting_number);
    temp1 = func(starting_node , distance);
    printf("%d" , temp1);
    return 0;
}
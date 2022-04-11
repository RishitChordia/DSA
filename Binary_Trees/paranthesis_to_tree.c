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

int bst_check(tree_node node)
{
    if (node == NULL)
    {
        return 1;
    }
    if (node->left_child != NULL && node->left_child->value > node->value)
    {
        return 0;
    }
    if (node->right_child != NULL && node->right_child->value < node->value)
    {
        return 0;
    }
    if (!bst_check(node->left_child) || !bst_check(node->right_child))
    {
        return 0;
    }
    return 1;
}

void postorder_space(tree_node node)
{
    if (node != NULL)
    {
        postorder_space(node->left_child);
        postorder_space(node->right_child);
        printf("%d ", node->value);
    }
}

// only done to avoid extra space at the end of output, no practical use
// youve got too much time on your hand
void postorder(tree_node node){
    if (node != NULL)
    {
        postorder_space(node->left_child);
        postorder_space(node->right_child);
        printf("%d", node->value);
    }
}

int main()
{
    tree_node buffer;
    buffer = (tree_node)malloc(sizeof(struct tree));
    buffer->parent = NULL;
    int inp, temp;
    char string_inp[100000];
    scanf("%[^\n]%*c", string_inp);
    buffer = treeFromString(&string_inp[2], 0, strlen(string_inp) - 4, buffer);
    postorder(buffer);
    return 0;
}
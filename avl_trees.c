#include <stdio.h>
#include <stdlib.h>

struct tree
{
    int value;
    struct tree *left_child, *right_child;
    int height;
};

typedef struct tree *tree_node;

struct tree_root
{
    tree_node root;
};

typedef struct tree_root *tree_root;

int height(tree_node temp)
{
    if (temp == NULL)
        return 0;
    return temp->height;
}

int greater(int a, int b)
{
    if (a >= b)
    {
        return a;
    }
    return b;
}

tree_node CREATE_TREE_NODE(int value)
{
    tree_node temp;
    temp = (tree_node)malloc(sizeof(struct tree));
    if (temp == NULL)
        exit(0);
    temp->value = value;
    temp->left_child = NULL;
    temp->right_child = NULL;
    temp->height = 1;
    return temp;
}

tree_node rightRotate(tree_node n)
{
    tree_node p;
    p = (tree_node)malloc(sizeof(struct tree));
    tree_node temp;
    temp = (tree_node)malloc(sizeof(struct tree));

    p = n->left_child;
    temp = p->right_child;
    //didnt work without temp using class algorithm :/
    p->right_child = n;
    n->left_child = temp;

    n->height = greater(height(n->left_child), height(n->right_child));
    n->height++;
    p->height = greater(height(p->left_child), height(p->right_child));
    p->height++;
    return p;
}

tree_node leftRotate(tree_node n)
{
    tree_node p;
    p = (tree_node)malloc(sizeof(struct tree));
    tree_node temp;
    temp = (tree_node)malloc(sizeof(struct tree));

    p = n->right_child;
    temp = p->left_child;
    p->left_child = n;
    n->right_child = temp;

    n->height = greater(height(n->left_child), height(n->right_child));
    n->height++;
    p->height = greater(height(p->left_child), height(p->right_child));
    p->height++;
    return p;
}

int balance_factor(tree_node temp)
{
    if (temp == NULL)
    {
        return 0;
    }
    return (height(temp->left_child) - height(temp->right_child));
}

tree_node insert(tree_node root, int key)
{
    if (root == NULL){
        return (CREATE_TREE_NODE(key));
    }
    if (key < root->value)
    {
        root->left_child = insert(root->left_child, key);
    }
    else if (key > root->value)
    {
        root->right_child = insert(root->right_child, key);
    }
    else
    {
        return root;
    }

    root->height = 1 + greater(height(root->left_child), height(root->right_child));

    int balance = balance_factor(root);
    if (balance >= 2 && key < root->left_child->value)
    {
        return rightRotate(root);
    }
    if (balance <= -2 && key > root->right_child->value)
    {
        return leftRotate(root);
    }
    if (balance > 1 && key > root->left_child->value)
    {
        // double rotation case
        root->left_child = leftRotate(root->left_child);
        return rightRotate(root);
    }

    if (balance < -1 && key < root->right_child->value)
    {
        root->right_child = rightRotate(root->right_child);
        return leftRotate(root);
    }

    return root;
}

tree_node maximum(tree_node node_x)
{
    while (node_x->right_child != NULL)
    {
        node_x = node_x->right_child;
    }
    return node_x;
    // does the job of predecessor since we only use predecessor when it has both children
}

tree_node search(tree_node root, int data)
{
    if (root == NULL)
    {
        return NULL;
    }
    tree_node temp;
    temp = (tree_node)malloc(sizeof(struct tree));
    // temp = input_tree->root;
    temp = root;
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
                // here issue
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

tree_node delete_node(tree_node root, int key, int check)
{
    if (root == NULL)
    {
        if (check)
        {
            printf("FALSE\n");
        }

        // entry here means key was not found
        return root;
    }
    if (key < root->value)
    {
        root->left_child = delete_node(root->left_child, key, check);
    }
    else if (key > root->value)
    {
        root->right_child = delete_node(root->right_child, key, check);
    }
    else
    {
        if (check)
        {
            printf("%d\n", key);
        }
        if ((root->left_child == NULL) || (root->right_child == NULL))
        {
            tree_node temp = root->left_child ? root->left_child : root->right_child;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
        }
        else
        {
            tree_node temp = maximum(root->left_child); // predecessor
            root->value = temp->value;
            root->right_child = delete_node(root->right_child, temp->value, 0);
        }
    }

    if (root == NULL){
        return root;
    }

    root->height = 1 + greater(height(root->left_child), height(root->right_child));

    int balance = balance_factor(root);
    if (balance > 1 && balance_factor(root->left_child) >= 0)
        return rightRotate(root);

    if (balance > 1 && balance_factor(root->left_child) < 0)
    {
        root->left_child = leftRotate(root->left_child);
        return rightRotate(root);
    }

    if (balance < -1 && balance_factor(root->right_child) <= 0)
        return leftRotate(root);

    if (balance < -1 && balance_factor(root->right_child) > 0)
    {
        root->right_child = rightRotate(root->right_child);
        return leftRotate(root);
    }

    return root;
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
    else
    {
        printf("( ) ");
    }
}

int get_balance(tree_root root, int key)
{
    tree_node buffer;
    buffer = (tree_node)malloc(sizeof(struct tree));
    buffer = search(root->root, key);
    if (buffer == NULL)
    {
        printf("FALSE\n");
    }
    else
    {
        printf("%d\n", balance_factor(buffer));
    }
}

int main()
{
    tree_root root;
    root = (tree_root)malloc(sizeof(struct tree_root));
    root->root = NULL;
    char input_char;
    tree_node buffer;
    buffer = (tree_node)malloc(sizeof(struct tree));
    int inp, temp;
    scanf("%c ", &input_char);
    while (input_char != 'e')
    {
        if (input_char == 'i')
        {
            scanf(" %d", &inp);
            root->root = insert(root->root, inp);
        }
        else if (input_char == 'd')
        {
            scanf(" %d", &inp);
            root->root = delete_node(root->root, inp, 1);
        }
        else if (input_char == 's')
        {
            scanf(" %d", &inp);
            buffer = search(root->root, inp);
            if (buffer == NULL)
            {
                printf("FALSE\n");
            }
            else
            {
                printf("TRUE\n");
            }
        }
        else if (input_char == 'p')
        {
            PRINT(root->root);
            printf("\n");
        }
        if (input_char == 'b')
        {
            scanf(" %d", &inp);
            get_balance(root, inp);
        }
        scanf("\n%c", &input_char);
    }
    return 0;
}
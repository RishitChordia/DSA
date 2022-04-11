#include <stdio.h>
#include <stdlib.h>

struct node { 
    int value; 
    struct node *next; 
};

typedef struct node *node;

struct top
{
    node top;
};

typedef struct top *top;

struct tree {
    char value;
    struct tree *left_child ,*right_child;
};
typedef struct tree *tree_node;

struct node_stack_tree { 
    tree_node value;
    struct node_stack_tree *next; 
};

typedef struct node_stack_tree *node_stack_tree;

struct tree_top
{
    node_stack_tree top;
};

typedef struct tree_top *tree_top;

int STACK_EMPTY_TREE(tree_top S){
    if(S->top == NULL){
        return -1;
    }
    else return 1;
}

node_stack_tree CREATE_NODE_TREE_STACK(tree_node value) {
    node_stack_tree temp;
    temp = (node_stack_tree)malloc(sizeof(node_stack_tree));
    if(temp == NULL)
        exit(0);
    temp->value = value;
    temp->next = NULL;
    return temp;
}

tree_node CREATE_TREE_NODE(char value , tree_node l , tree_node r) {
    tree_node temp;
    temp = (tree_node)malloc(sizeof(tree_node));
    if(temp == NULL)
        exit(0);
    temp->value = value;
    temp->left_child = l;
    temp->right_child = r;
    return temp;
}

void PUSH_TREE(tree_top S, node_stack_tree x){
    x->next = S->top;
    S->top = x;
}

tree_node POP_TREE(tree_top S){
    tree_node temp;
    temp = (tree_node)malloc(sizeof(tree_node));
    temp = S->top->value;
    S->top = (S->top)->next;
    return temp;
}

int STACK_EMPTY_NORMAL(top S){
    if(S->top == NULL){
        return -1;
    }
    else return 1;
}

node CREATE_NODE_NORMAL(int value) {
    node temp;
    temp = (node)malloc(sizeof(node));
    if(temp == NULL)
        exit(0);
    temp->value = value;
    temp->next = NULL;
    return temp;
}

void PUSH_NORMAL(top S, node x){
    x->next = S->top;
    S->top = x;
}

char POP_NORMAL(top S){
    char temp = (S->top)->value;
    S->top = (S->top)->next;
    return temp;
}

char PEEK_NORMAL(top S){
    char temp = S->top->value;
    return temp;
}

int operators(char operator){
    // returns 0 if character isnt an operator 
    // returns a number based on the priority of operator if it is one 
    if(operator == '*' || operator == '/')
	{
		return(2);
	}
	else if(operator == '+' || operator == '-')
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

tree_node CONSTRUCT_TREE(char input_postfix[] , int n){
    tree_top stack;
    stack = (tree_top)malloc(sizeof(tree_top));
    stack->top = NULL;

    tree_node left_temp;
    left_temp = (tree_node)malloc(sizeof(tree_node));

    tree_node right_temp;
    right_temp = (tree_node)malloc(sizeof(tree_node));

    tree_node node_temp;
    node_temp = (tree_node)malloc(sizeof(tree_node));

    int i = 0 , j = 0;
    for ( i = 0; i < n; i++)
    {
        if (operators(input_postfix[i]))
        {
            right_temp = POP_TREE(stack);
            left_temp = POP_TREE(stack);
            node_temp = CREATE_TREE_NODE(input_postfix[i] , left_temp , right_temp);
            PUSH_TREE(stack , CREATE_NODE_TREE_STACK(node_temp));
        }
        else if(input_postfix[i] > 96 && input_postfix[i] < 123)
        {
            node_temp = CREATE_TREE_NODE(input_postfix[i] , NULL , NULL);
            PUSH_TREE(stack , CREATE_NODE_TREE_STACK(node_temp));
        }   
    }
    return stack->top->value;
}

void PREORDER(tree_node node)
{
    if(node!=NULL)
    {
    printf("%c",node->value);
    PREORDER(node->left_child);
    PREORDER(node->right_child);
    }
}

void POSTORDER(tree_node node)
{
    if(node!=NULL)
    {
    POSTORDER(node->left_child);
    POSTORDER(node->right_child);
    printf("%c",node->value);
    }
}

tree_node CREATE_ASSIGNMENT_TREE(char input_infix[] , int n){
    top stack;
    stack = (top)malloc(sizeof(top));
    stack->top = NULL;
    char temp_char;
    char postfix[2000];
    int postfix_index = 0;
    int i = 0 , j = 0;
    for ( i = 0; i < n; i++)
    {
        if (input_infix[i] > 96 && input_infix[i] < 123)
        {
            postfix[postfix_index++] = input_infix[i];
        }
        else if (operators(input_infix[i]))
        {
            if (STACK_EMPTY_NORMAL(stack) == -1)
            {
                PUSH_NORMAL(stack , CREATE_NODE_NORMAL(input_infix[i]));
            }
            else
            {
                temp_char = PEEK_NORMAL(stack);
                while (operators(temp_char) && operators(temp_char) >= operators(input_infix[i]))
                {
                    postfix[postfix_index++] = temp_char;
                    POP_NORMAL(stack);
                    if (STACK_EMPTY_NORMAL(stack) == 1)
                    {
                        temp_char = PEEK_NORMAL(stack);
                        continue;
                    }
                    else if(STACK_EMPTY_NORMAL(stack) == -1)
                    {
                        break;
                    }
                }
                PUSH_NORMAL(stack , CREATE_NODE_NORMAL(input_infix[i]));
            }
        }
        else if(input_infix[i] == '('){
            PUSH_NORMAL(stack , CREATE_NODE_NORMAL(input_infix[i]));
        }
        else if(input_infix[i] == ')'){
            temp_char = POP_NORMAL(stack);
            while ( temp_char != '('){
                postfix[postfix_index++] = temp_char;
                temp_char = POP_NORMAL(stack);
            }
        }
    }

    while (STACK_EMPTY_NORMAL(stack) != -1)
    {
        temp_char = POP_NORMAL(stack);
        postfix[postfix_index++] = temp_char;
    }
    tree_node node_temp;
    node_temp = (tree_node)malloc(sizeof(tree_node));
    node_temp = CONSTRUCT_TREE(postfix , postfix_index);
    return node_temp;
}

int main(){
    char input_infix[20000];
    char temp_char;
    int i;
    scanf("%c" , &temp_char);
    printf("%c" , temp_char);
    scanf("%c" , &temp_char);
    scanf("%c" , &temp_char);
    for (i = 0; temp_char != ';'; i++)
    {
        input_infix[i] = temp_char;
        scanf("%c" , &temp_char);
    }
    input_infix[i++] = '\0';
    tree_node node_temp;
    node_temp = (tree_node)malloc(sizeof(tree_node));
    node_temp = CREATE_ASSIGNMENT_TREE(input_infix , i);
    POSTORDER(node_temp);
    printf("=");
    return 0;
}

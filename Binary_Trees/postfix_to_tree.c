#include <stdio.h>
#include <stdlib.h>

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
            right_temp = POP(stack);
            left_temp = POP(stack);
            node_temp = CREATE_TREE_NODE(input_postfix[i] , left_temp , right_temp);
            PUSH(stack , CREATE_NODE(node_temp));
        }
        else if(input_postfix[i] > 96 && input_postfix[i] < 123)
        {
            node_temp = CREATE_TREE_NODE(input_postfix[i] , NULL , NULL);
            PUSH(stack , CREATE_NODE(node_temp));
        }   
    }
    return stack->top->value;
}

void INORDER(tree_node node)
{
    if(node!=NULL)
    {
    INORDER(node->left_child);
    printf("%c",node->value);
    INORDER(node->right_child);
    }
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

int main(){
    char input_postfix[20000];
    char temp_char , input_char;
    int i;
    tree_node node_temp;
    node_temp = (tree_node)malloc(sizeof(tree_node));
    node_temp = NULL;
    scanf("%c" , &input_char);
    while (input_char != 't')
    {
        if (input_char == 'e')
        {
            scanf("%c" , &temp_char);
            for (i = 0; temp_char != '\n'; i++)
            {
                input_postfix[i] = temp_char;
                scanf("%c" , &temp_char);
            }
            node_temp = CONSTRUCT_TREE(input_postfix , i);
        }
        else if (input_char == 'i')
        {
            INORDER(node_temp);
            printf("\n");
        }
        else if (input_char == 'p')
        {
            PREORDER(node_temp);
            printf("\n");
        }
        else if (input_char == 's')
        {
            POSTORDER(node_temp);
            printf("\n");
        }
        scanf("%c" , &input_char); 
    }
    // if the size of string cant be passed to the array, we add an extra element '\0' at the end
    // and traverse using a loop with condition input_infix[i] != '\0' 

    return 0;
}
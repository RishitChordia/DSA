#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int STACK_EMPTY(top S){
    if(S->top == NULL){
        return -1;
    }
    else return 1;
}

node CREATE_NODE(int value) {
    node temp;
    temp = (node)malloc(sizeof(node));
    if(temp == NULL)
        exit(0);
    temp->value = value;
    temp->next = NULL;
    return temp;
}

void PUSH(top S, node x){
    x->next = S->top;
    S->top = x;
}

int POP(top S){
    int temp = (S->top)->value;
    S->top = (S->top)->next;
    return temp;
}

int PEEK(top S){
    int temp = S->top->value;
    return temp;
}

int string_to_int(char x[] , int n){
    int final_ans=0;
    for (int i = 0; i < n; i++)
    {
        final_ans *= 10;
        final_ans += (x[i] - 48);
    }
    return final_ans;   
}

int new_value(int operand1 , int operand2 , char value){
    if (value == '*')
    {
        return (operand1*operand2);
    }
    else if (value == '+')
    {
        return (operand1+operand2);
    }
    else if (value == '-')
    {
        return (operand1-operand2);
    }
    else if (value == '/')
    {
        return (operand1/operand2);
    }
    
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

void EVALUATEPOSTFIX(char input_infix[] , int n){
    top stack;
    stack = (top)malloc(sizeof(top));
    stack->top = NULL;
    char temp_char;
    char value[4];
    int temp , operand1 , operand2;
    int i = 0 , j = 0;
    for ( i = 0; i < n; )
    {
        sscanf(&input_infix[i] , " %s " , value);
        if (operators(value[0]))
        {
            operand2 = POP(stack);
            operand1 = POP(stack);
            temp = new_value(operand1 , operand2 , value[0]);
            PUSH(stack , CREATE_NODE(temp));
        }
        else if (value[0] > 47 && value[0] < 58)
        {
            temp = string_to_int(value , strlen(value));
            PUSH(stack , CREATE_NODE(temp));
        }
        i += (strlen(value)+1);
    }
    temp = POP(stack); // final answer remains as the single element at the top of stack
    printf("%d" , temp);
}

int main(){
    char input_infix[20000];
    char temp_char;
    int i;
    scanf("%c" , &temp_char);
    for (i = 0; temp_char != '\n'; i++)
    {
        input_infix[i] = temp_char;
        scanf("%c" , &temp_char);
    }
    // if the size of string cant be passed to the array, we traverse using a loop with condition 
    // input_infix[i] != '\0' 
    EVALUATEPOSTFIX(input_infix , i);
    
    return 0;
}
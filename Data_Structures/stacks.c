#include <stdio.h>
#include <stdlib.h>

struct arr_with_index {
    int stack_size;
    int index_top;
    char arr[200000];
};

int STACK_EMPTY(struct arr_with_index input_stack){
    if (input_stack.index_top == 0)
    {
        return -1;
    }
    return 1;
}

int STACK_FULL(struct arr_with_index input_stack){
    if (input_stack.stack_size == input_stack.index_top)
    {
        return -1;
    }
    return 1;
}

struct arr_with_index POP(struct arr_with_index input_stack){
    if (STACK_EMPTY(input_stack) == -1)
    {
        printf("-1\n");
        return input_stack;
    }
    else{
        printf("%c\n" , input_stack.arr[(input_stack.index_top) - 1]);
        input_stack.index_top -= 1;
        return input_stack;
    }
}

void PEEK(struct arr_with_index input_stack){
    if (STACK_EMPTY(input_stack) == -1)
    {
        printf("-1\n");
        return;
    }
    else{
        printf("%c\n" , input_stack.arr[(input_stack.index_top) - 1]);
    }
}

struct arr_with_index PUSH(struct arr_with_index input_stack , char new_element){
    if (STACK_FULL(input_stack) == -1)
    {
        printf("-1\n");
        return input_stack;
    }
    else
    {
        input_stack.arr[(input_stack.index_top)] = new_element;
        input_stack.index_top += 1;
        return input_stack;
    }  
}

int main(){
    int stack_size;
    char input_char , new_element;
    struct arr_with_index input_stack;
    scanf("%d" , &stack_size);
    input_stack.stack_size = stack_size;
    input_stack.index_top = 0;
    scanf("%c" , &input_char);
    while (input_char != 't')
    {
        if (input_char == 'i')
        {
            scanf(" %c" , &new_element);
            input_stack = PUSH(input_stack , new_element);
        }
        else if (input_char == 'd')
        {
            input_stack = POP(input_stack);
        }
        else if (input_char == 'p')
        {
            PEEK(input_stack);
        }
        scanf("\n%c" , &input_char);
    }
    return 0;
}

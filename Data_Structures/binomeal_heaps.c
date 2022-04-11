// parent child sibling value degree
// roots are siblings
// sibling to the right
// child to the left
#include <stdio.h>
#include <stdlib.h>

struct heap_node
{
    int value, degree;
    struct heap_node *parent;
    struct heap_node *child;
    struct heap_node *sibling;
};

typedef struct heap_node *node;

struct heap_head
{
    node head;
};

typedef struct heap_head *head;

head make_heap()
{
    node heap;
    heap = (node)malloc(sizeof(struct heap_node));
    heap->child = NULL;
    heap->parent = NULL;
    heap->sibling = NULL;
    heap->degree = -1;
    head h;
    h = (head)malloc(sizeof(struct heap_head));
    h->head = heap;
    // since technically degree=0 would be one element
    return h;
}

int degree(node h)
{
    if (h == NULL)
    {
        return -1;
    }

    else
        return h->degree;
}

head merge_heaps(head h1, head h2)
{

    head new_head;
    new_head = (head)malloc(sizeof(struct heap_head));
    new_head->head = NULL;
    
    node a,b,y,z;
    a = (node)(malloc)(sizeof(struct heap_node));
    b = (node)(malloc)(sizeof(struct heap_node));
    y = (node)(malloc)(sizeof(struct heap_node));
    z = (node)(malloc)(sizeof(struct heap_node));
    y = h1->head;
    z = h2->head;
    if (y != NULL)
    {
        if (z != NULL && y->degree <= z->degree)
            new_head->head = y;
        else if (z != NULL && y->degree > z->degree)
            new_head->head = z;
        else
            new_head->head = y;
    }
    else{
        new_head->head = z;
    }
    while (y != NULL && z != NULL)
    {
        if (y->degree < z->degree)
        {
            y = y->sibling;
        }
        else if (y->degree == z->degree)
        {
            a = y->sibling;
            y->sibling = z;
            y = a;
        }
        else
        {
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
    return new_head;
}

void binomial_link(node a, node b)
{
    // links a as the child of b
    a->parent = b;
    a->sibling = b->child;
    b->child = a;
    b->degree += 1;
}

head union_heaps(head h1, head h2)
{
    head new_heap;
    new_heap = (head)malloc(sizeof(struct heap_head));
    new_heap = merge_heaps(h1, h2);
    if (new_heap->head == NULL)
    {
        return new_heap;
    }
    
    node x, next, previous;
    x = (node)malloc(sizeof(struct heap_node));
    next = (node)malloc(sizeof(struct heap_node));
    previous = (node)malloc(sizeof(struct heap_node));
    

    if (new_heap == NULL)
        return new_heap;
    previous = NULL;
    x = new_heap->head;
    next = x->sibling;
    while (next != NULL)
    {
        if ((x->degree != next->degree) || ((next->sibling != NULL) && (next->sibling)->degree == x->degree))
        {
            previous = x;
            x = next;
        }
        else
        {
            if (x->value <= next->value)
            {
                x->sibling = next->sibling;
                binomial_link(next, x);
            }
            else
            {
                if (previous == NULL){
                    new_heap->head = next;}
                else{
                    previous->sibling = next;
                }
                binomial_link(x, next);
                x = next;
            }
        }
        next = x->sibling;
        // here since has to be done for each case
        // x = next not for each case
        // couldve done this line in each step and said continue but im fancy
    }
    return new_heap;
}

head insert(head h1, int key)
{
    head heap;
    heap = (head)malloc(sizeof(struct heap_head));
    heap = make_heap();
    heap->head->value = key;
    heap->head->degree = 0;
    heap->head->child = NULL;
    return union_heaps(h1, heap);
}

int minimum(head h1){
    node current;
    current = (node)malloc(sizeof(struct heap_node));
    current = h1->head;
    if (current == NULL)
    {
        return -1;
    }
    int min = current->value;
    while (current != NULL)
    {
        if (current->value < min)
        {
            min = current->value;
        }
        current = current->sibling;
    }
    return min;
    
}

node nth_child(node x , int n){
    for (int i = 0; i < n; i++)
    {
        x = x->child;
    }
    return x;
    
}

node search(node current, int k)
{
    node x,temp;
    x = (node)malloc(sizeof(struct heap_node));
    temp = (node)malloc(sizeof(struct heap_node));
    x = current;
    temp = NULL;
    if (x->value == k)
    {
        temp = x;
        return temp;
    }
    if (x->child != NULL && temp == NULL)
    {
        temp = search(x->child, k);
    }

    if (x->sibling != NULL && temp == NULL)
    {
        temp = search(x->sibling, k);
    }
    return temp;
}

int decrease_key(head h1, int key, int k)
{
    int temp,storage;
    node p,temp1,temp2;
    p = (node)malloc(sizeof(struct heap_node));
    temp1 = (node)malloc(sizeof(struct heap_node));
    temp2 = (node)malloc(sizeof(struct heap_node));

    p = search(h1->head, key);
    if (p == NULL)
    {
        return -1;
    }
    if (k > p->value)
    {
        // cant reduce
        return -1;
    }
    p->value -= k;
    storage = p->value;
    temp1 = p;
    temp2 = p->parent;
    while (temp2 != NULL && temp1->value < temp2->value)
    {
        temp = temp1->value;
        temp1->value = temp2->value;
        temp2->value = temp;
        temp1 = temp2;
        temp2 = temp2->parent;
    }
    return storage;
}

void reversal(head h1, node current){
    if (current->sibling != NULL)
    {
        reversal(h1 , current->sibling);
        current->sibling->sibling = current;
    }
    else{
        h1->head = current;
    }
}
// WOW

head extract_min(head h1){
    node min_node,temp,temp2,current;
    min_node = (node)malloc(sizeof(struct heap_node));
    temp = (node)malloc(sizeof(struct heap_node));
    temp2 = (node)malloc(sizeof(struct heap_node));
    current = (node)malloc(sizeof(struct heap_node));
    head heap;
    heap = (head)malloc(sizeof(struct heap_head));
    heap->head = NULL;
    int min,temp_num,i;


    current = h1->head;
    if (current == NULL)
    {
        return h1;
    }
    min = current->value;
    min_node = current;
    temp = NULL;
    temp2 = NULL;
    while (current != NULL)
    {
        if (current->value < min)
        {
            min = current->value;
            min_node = current;
            temp2 = temp;
        }
        temp = current;
        current = current->sibling;
    }
    if (temp2 == NULL && min_node->sibling == NULL)
    {
        h1->head = NULL;
    }
    else if (temp2 == NULL)
    {
        h1->head = min_node->sibling;
    }
    else if (temp2->sibling == NULL)
    {
        temp2 = NULL;
    }
    else{
        temp = min_node->sibling;
        temp2->sibling = temp;
    }
    
    temp_num = min_node->degree;
    if (temp_num == 0)
    {
        return h1;
    }
    if (min_node->child != NULL)
    {
        reversal(heap , min_node->child);
        min_node->child->sibling = NULL;
    }

    return union_heaps(h1,heap);
}

void print(head h1)
{
    // the approach by making arrays of the nodes hadnt worked 
    node current;
    current = (node)malloc(sizeof(struct heap_node));
    node temp;
    temp = (node)malloc(sizeof(struct heap_node));
    current = h1->head;
    while (current != NULL)
    {
        printf("%d ", current->value);
        current = current->sibling;
    }
    int i,check = 1;
    for ( i = 1; check ;i++)
    // cant start from 0 since the ones at the 0th level get printed multiple times 
    {
        check = 0;
        current = h1->head;
        while (current != NULL)
        {
            if (current->degree >= i)
            {
                check = 1;
                temp = nth_child(current , i);
                while (temp != NULL)
                {
                    printf("%d " , temp->value);
                    temp = temp->sibling;
                }
            }
            current = current->sibling;
        }
    }
    printf("\n");
}

int main()
{
    head heap;
    heap = (head)malloc(sizeof(struct heap_head));
    char input_char;
    node buffer;
    buffer = (node)malloc(sizeof( struct heap_node ));
    int inp , temp;
    scanf("%c " , &input_char);
    while (input_char!= 'e')
    {
        if(input_char == 'i'){
            scanf(" %d" , &inp);
            heap = insert(heap, inp);
        }
        else if(input_char == 'p'){
            print(heap); 
        }
        else if(input_char == 'm'){
            printf("%d\n" , minimum(heap));  
        }
        else if(input_char == 'r'){
            scanf(" %d" , &inp);
            scanf(" %d" , &temp);
            printf("%d\n" , decrease_key(heap , inp , temp));
        }
        else if(input_char == 'x'){
            heap = extract_min(heap);
        }
        else if(input_char == 'd'){
            scanf(" %d" , &inp);
        }
        scanf("\n%c" , &input_char);
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int value,rank;
    struct node *parent;
};
typedef struct node* node;


struct list{
    node curr;
    struct list* next;
};
typedef struct list* list;

struct head{
    list head;
};
typedef struct head* header;

struct cheaty_int{
    int num;
};
typedef struct cheaty_int* glbint;

void makeset(int value , header h){
    node x;
    x = (node)malloc(sizeof(struct node));
    x->value = value;
    x->rank = 0;
    x->parent = x;

    list l_x;
    l_x = (list)malloc(sizeof(struct list));
    list buffer;
    buffer = (list)malloc(sizeof(struct list));
    l_x->curr = x;
    l_x->next = NULL;
    buffer = h->head;
    if(buffer == NULL)
    {
        h->head = l_x;
        return;
    }
    while (buffer->next != NULL)
    {
        buffer = buffer->next;
    }
    buffer->next = l_x;
}

int link_ranked(node x , node y){

    if (x == NULL || y == NULL)
    {
        return -1;
    }
    if (x->value == y->value)
    {
        return x->value;
    }
    
    int ans;
    if(x->rank < y->rank){
        x->parent = y;
        ans = y->value;
    }
    else{
        y->parent = x;
        ans = x->value;
    }
    if (x->rank == y->rank)
    {
        x->rank++;
    } 
    return ans;
}

int link_unranked(node x , node y){
    if (x == NULL || y == NULL)
    {
        return -1;
    }
    if (x->value == y->value)
    {
        return x->value;
    }
    y->parent = x;
    return x->value;
}

node search_node(header h , int value){
    list buffer;
    buffer = (list)malloc(sizeof(struct list));
    buffer = h->head;
    if (buffer == NULL)
    {
        return NULL;
    }
    if (buffer->next == NULL)
    {
        if (buffer->curr->value == value)
        {
            return buffer->curr;
        }
        else{
            return NULL;
        }
    }
    
    while (buffer != NULL)
    {   
        if (buffer->curr->value == value)
        {
            return buffer->curr;
        }
        buffer = buffer->next;
    }
    return NULL;
}

node find_set_no_comp(int value , header h , glbint count){
    node x;
    x = (node)malloc(sizeof(struct node));
    node buffer;
    buffer = (node)malloc(sizeof(struct node));
    x = search_node(h , value);
    buffer = x;
    if (x == NULL)
    {
        return NULL;
    }
    while (buffer->parent != buffer)
    {
        count->num++;
        buffer = buffer->parent;
    }
    return buffer;
}

node find_set_comp(node x , header h , glbint count){
    node buffer;
    buffer = (node)malloc(sizeof(struct node));
    buffer = x;
    if (x == NULL)
    {
        return NULL;
    }
    if (x != x->parent)
    {
        count->num++;
        x->parent = find_set_comp(x->parent , h , count);
    }
    else{
        return x->parent;
    }
    
}

int main(){
    glbint a,b,c,d;
    a = (glbint)malloc(sizeof(struct cheaty_int));
    b = (glbint)malloc(sizeof(struct cheaty_int));
    c = (glbint)malloc(sizeof(struct cheaty_int));
    d = (glbint)malloc(sizeof(struct cheaty_int));
    a->num = 0;
    b->num = 0;
    c->num = 0;
    d->num = 0;

    node buffer1;
    buffer1 = (node)malloc(sizeof(struct node));
    node buffer2;
    buffer2 = (node)malloc(sizeof(struct node));
    header ha,hb,hc,hd;
    ha = (header)malloc(sizeof(struct head));
    ha->head = NULL;
    hb = (header)malloc(sizeof(struct head));
    hb->head = NULL;
    hc = (header)malloc(sizeof(struct head));
    hc->head = NULL;
    hd = (header)malloc(sizeof(struct head));
    hd->head = NULL;

    char input_char;
    int x,y;
    scanf("%c " , &input_char);
    while (input_char!= 's')
    {
        if (input_char == 'm')
        {
            scanf("%d" , &x);
            if (search_node(ha , x) != NULL)
            {
                printf("-1\n");
            }
            else{
                printf("%d\n" , x);
                makeset(x,ha);
                makeset(x,hb);
                makeset(x,hc);
                makeset(x,hd);
            }
        }
        else if(input_char == 'u'){
            scanf("%d" , &x);
            scanf("%d" , &y);
            if (search_node(ha , x) == NULL || search_node(ha , y) == NULL)
            {
                printf("-1\n");
            }
            else{
                printf("%d " ,link_unranked(find_set_no_comp(x,ha,a) , find_set_no_comp(y,ha,a)));
                printf("%d " ,link_ranked(find_set_no_comp(x,hb,b) , find_set_no_comp(y,hb,b)));
                printf("%d " ,link_unranked(find_set_comp(search_node(hc , x),hc,c) , find_set_comp(search_node(hc , y),hc,c)));
                printf("%d\n" ,link_ranked(find_set_comp(search_node(hd , x),hd,d) , find_set_comp(search_node(hd , y),hd,d)));
                a->num += 2;
                b->num += 2;
                c->num += 2;
                d->num += 2;
            }
        }
        else if(input_char == 'f'){
            scanf("%d" , &x);
            if (search_node(ha , x) == NULL)
            {
                printf("-1\n");
            }
            else{
                printf("%d ",find_set_no_comp(x,ha,a)->value);
                printf("%d ",find_set_no_comp(x,hb,b)->value);
                printf("%d ",find_set_comp(search_node(hc , x),hc,c)->value);
                printf("%d\n",find_set_comp(search_node(hd , x),hd,d)->value);
                a->num += 1;
                b->num += 1;
                c->num += 1;
                d->num += 1;
            }
        }
        scanf("\n%c" , &input_char);
    }
    printf("%d %d %d %d" , a->num , b->num , c->num , d->num);

    return 0;

}
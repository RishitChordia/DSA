#include <stdio.h>
#include <string.h>

int search_binary(int array_input[], int left_lim, int right_lim, int key)
{
    int index_mid = (left_lim+right_lim)/2;
    if (right_lim < left_lim)
    {
        printf("-1\n");
        return -1;
    }
    if (array_input[index_mid] == key)
    {
        return index_mid;
    }
    else if (key < array_input[index_mid])
    {
        return search_binary(array_input , left_lim , index_mid - 1 , key);
    }
    else if (key > array_input[index_mid])
    {
        return search_binary(array_input , index_mid +1 , right_lim , key);
    }
}

int main()
{
    int n , i , key , counter = 0;
    scanf("%d" , &n);
    int array_input[n];
    for ( i = 0; i < n; i++)
    {
        scanf("%d" , &array_input[i]);
    }
    scanf("%d" , &key);
    printf("%d" , search_binary(array_input , 0 , n-1 , key));
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
int heapify(int input_Arr[], int n, int i)
{
    int counter_comparisons = 0 , max_element = i , left_index = 2 * i + 1 , right_index = 2 * i + 2 , temp;

    if (left_index < n){
        counter_comparisons++;
        // comparison only occurs when left_index < n, hence count increases if the condition left_index < n is true 
        if(input_Arr[left_index] > input_Arr[max_element]){
            max_element = left_index;
    }
    }

    if (right_index < n){
        counter_comparisons++;
        // similar logic as previous if condititon 
        if(input_Arr[right_index] > input_Arr[max_element]){
            max_element = right_index;
    }
    }
    if (max_element != i)
    {
        temp = input_Arr[i];
        input_Arr[i] = input_Arr[max_element];
        input_Arr[max_element] = temp;
        counter_comparisons += heapify(input_Arr, n, max_element);
    }
    return counter_comparisons;
}

int heapSort(int input_Arr[], int n)
{
    int temp , counter_comparisons = 0 , i;
    for (i = n / 2 - 1; i > -1; i--){
        counter_comparisons +=  heapify(input_Arr, n, i);
    }
    for (i = n - 1; i > -1; i--)
    {
        temp = input_Arr[0];
        input_Arr[0] = input_Arr[i];
        input_Arr[i] = temp;
        counter_comparisons += heapify(input_Arr, i, 0);
    }

    return counter_comparisons;
}

void Arr_Printer(int Arr_inp[] , int n){
    if (n > 0)
    {
        int i;
        printf("%d" , Arr_inp[0]);
        for ( i = 1; i < n; i++)
        {
            printf(" %d" , Arr_inp[i]);
        }
        printf("\n");
    }
}

int main()
{
    int n , i;
    scanf("%d" , &n);
    int* input_Arr;
    input_Arr = (int*) malloc(n*4);

    for ( i = 0; i < n; i++)
    {
        scanf("%d" , &input_Arr[i]);
    }
    int counter_final = heapSort(input_Arr, n);
    Arr_Printer(input_Arr, n);
    printf("%d" , counter_final);
}
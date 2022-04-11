// Quick sort in C
#include <stdlib.h>
#include <stdio.h>
void printArray(int arr[], int size);
void interchange(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int array[], int lower, int higher , int* final_arr)
{
    int counter = 0;
    int pivot = array[higher];

    int i = (lower - 1);

    for (int j = lower; j < higher; j++)
    {
        if (array[j] <= pivot)
        {
            i++;
            interchange(&array[i], &array[j]);
            counter++;
        }
    }
    interchange(&array[i + 1], &array[higher]);
    final_arr[0] += counter;
    printArray(array , higher - lower + 1);
    return (i + 1);
}

void quickSort(int arr[], int lower, int higher , int* final_arr)
{
    if (lower < higher)
    {
        int new_index = partition(arr, lower, higher , final_arr);
        quickSort(arr, lower, new_index - 1 , final_arr);
        quickSort(arr, new_index + 1, higher , final_arr);
    }
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d  ", arr[i]);
    }
    printf("\n");
}
int main()
{
    int n;
    scanf("%d" , &n);
    int data[n] , i;
    for ( i = 0; i < n; i++)
    {
        scanf("%d" , &data[i]);
    }
    printArray(data, n);
    int* final_arr;
    final_arr = (int*) malloc(8);
    final_arr[0] = 0;
    quickSort(data, 0, n - 1, final_arr);
    printf("\n %d \n", final_arr[0]);
    printArray(data, n);
}

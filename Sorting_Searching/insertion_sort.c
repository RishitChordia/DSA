#include <stdio.h>
 
void printArray(int arr_inp[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr_inp[i]);
    printf("\n");
}

void insertionSort(int arr_inp[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr_inp[i];
        j = i - 1;
        while (j >= 0 && arr_inp[j] > key) {
            arr_inp[j + 1] = arr_inp[j];
            j = j - 1;
        }
        arr_inp[j + 1] = key;
    }
}

int main()
{
    int n;
    scanf("%d" , &n);
    int arr_inp[n] , i;
    for ( i = 0; i < n; i++)
    {
        scanf("%d" , &arr_inp[i]);
    }
    insertionSort(arr_inp, n);
    printarr_inpay(arr_inp, n);
 
    return 0;
}
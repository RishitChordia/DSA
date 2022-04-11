#include <stdio.h>
#include <stdlib.h>

int* Merge(int array_input[], int p, int q, int r)
{
    int counter = 0, inversions_count = 0, i , j , k , n_left = q - p + 1 , n_right = r - q;
    int left_part[n_left + 1] , right_part[n_right+1];
    int* arr_return;
    arr_return = (int*) malloc(8);

    for (i = 0; i < n_left; i++)
        left_part[i] = array_input[p + i];
    for (j = 0; j < n_right; j++)
        right_part[j] = array_input[q + j + 1];

    left_part[n_left] = 1000001;
    right_part[n_right] = 1000001;

    i = 0;
    j = 0;
    for (k = p; k <= r; k++)
    {
        counter++;
        if (left_part[i] <= right_part[j])
        {
            array_input[k] = left_part[i];
            i++;
        }
        else
        {
            array_input[k] = right_part[j];
            inversions_count+= (n_left - i);
            j++;
        }
    }
    arr_return[0] = counter;
    arr_return[1] = inversions_count;
    return arr_return;
}

int* Merge_Sort(int array_input[], int p, int r)
{
    int* arr_final;
    arr_final = (int*) malloc(8);
    arr_final[0] = 0;
    arr_final[1] = 0;
    int* temp;
    temp = (int*) malloc(8);
    if (p < r)
    {
        int q = (p + r) / 2;
        temp = Merge_Sort(array_input, p, q);
        arr_final[0] += temp[0];
        arr_final[1] += temp[1];
        temp = Merge_Sort(array_input, q + 1, r);
        arr_final[0] += temp[0];
        arr_final[1] += temp[1];
        temp = Merge(array_input, p, q, r);
        arr_final[0] += temp[0];
        arr_final[1] += temp[1];
    }
    return arr_final;
}

int main(){
    int n;
    int* final_ans;
    final_ans = (int*) malloc(8);
    scanf("%d" , &n);
    int array_input[n] , i;
    for ( i = 0; i < n; i++)
    {
        scanf("%d" , &array_input[i]);
    }
    final_ans = Merge_Sort(array_input , 0 , n-1);
    printf("%d\n%d" , final_ans[1] , final_ans[0]);
    return 0;
}
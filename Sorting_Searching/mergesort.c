#include <stdio.h>

int Merge(int array_input[], int p, int q, int r)
{
    int counter = 0 , i , j , k , n_left = q - p + 1 , n_right = r - q;
    int left_part[n_left + 1] , right_part[n_right+1];

    for (i = 0; i < n_left; i++)
        left_part[i] = array_input[p + i];
    for (j = 0; j < n_right; j++)
        right_part[j] = array_input[q + j + 1];

    left_part[n_left] = 1000000;
    right_part[n_right] = 1000000;

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
            // invert+= (n_left - i);
            j++;
        }
    }
    return counter;
}

int Merge_Sort(int array_input[], int p, int r)
{
    int counter = 0;
    if (p < r)
    {
        int q = (p + r) / 2;
        counter += Merge_Sort(array_input, p, q);
        counter += Merge_Sort(array_input, q + 1, r);
        counter += Merge(array_input, p, q, r);
    }
    return counter;
}

void Print(int array_input[] , int n){
    if (!n)
    {
        printf("\n");
    }
    else{
        int i;
        for ( i = 0; i < n-1; i++)
        {
            printf("%d " , array_input[i]);
        }
        printf("%d\n" , array_input[n-1]);
    }
}

int main(){
    int n , count_final;
    scanf("%d" , &n);
    int array_input[n] , i;
    for ( i = 0; i < n; i++)
    {
        scanf("%d" , &array_input[i]);
    }
    count_final = Merge_Sort(array_input , 0 , n-1);
    Print(array_input , n);
    printf("%d" , count_final);
    return 0;
}
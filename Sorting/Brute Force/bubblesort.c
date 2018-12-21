#include <stdio.h>

/* Selection Sort*/
void bubble_sort(int* p_array, int size)
{
    /* interator indexes */
    int i = 0;
    int j = 0;

    /* swaping variable*/
    int swap = 0;
    
    /* 1. for i <-0 to n-2 do */
    for (i = 0; i < size; i++)
    {
        /*2. for j <- 0 to n-2-i */
        for (j = 0; j < size-i; j++)
        {
            /* 4. if A[j+1] < A[j], swap A[j] and A[j+1]*/
            if (p_array[j+1] < p_array[j])
            {
                swap         = p_array[j];
                p_array[j]   = p_array[j+1];
                p_array[j+1] = swap;
            }
        }
    }
}

void print_array(int* p_array, int size)
{
    int i = 0;
    for (i = 0; i < size; i++)
    {
        printf(" Array value [%d]: %d\n", i, p_array[i]);
    }
}

int main(int argc, char const *argv[])
{
    /* Selection sort array */
    /* Input:  Unsorted array A[0..n-1] */
    /* Output: Sorted   array A[0..n-1] */
    int unsortedarray[5] = {45, 68, 89, 34, 29};
    
    /* Number of elements */
    int array_size = sizeof(unsortedarray) / sizeof(int);

    bubble_sort(unsortedarray, array_size);
    print_array(unsortedarray, array_size);

    return 0;
}

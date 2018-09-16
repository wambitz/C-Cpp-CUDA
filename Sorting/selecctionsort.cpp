#include <stdio.h>

/* Selection Sort*/
void selection_sort(int* p_array, int size)
{
    /* interator indexes */
    int i = 0;
    int j = 0;

    /* minimum value */
    int minimum_value_index = 0;
    /* swaping variable*/
    int swap = 0;
    
    /* 1. for i <-0 to n-2 do */
    for (i = 0; i < size-1; i++)
    {
        /* 2. min <- i*/
        minimum_value_index = i;
    
        /*3. for j <- i+1 to n-1 */
        for (j = i+1; j < size; j++)
        {
            /* 4. if A[j] < A[min], min <- j */
            if (p_array[j] < p_array[minimum_value_index])
            {
                minimum_value_index = j;
            }
        }
        /* 5. swap A[i] and A[min] */
        swap = p_array[i];
        p_array[i] = p_array[minimum_value_index];
        p_array[minimum_value_index] = swap;
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
    int unsortedarray[5] = {45, 37, 17, 3, 29};
    
    /* Number of elements */
    int array_size = sizeof(unsortedarray) / sizeof(int);

    selection_sort(unsortedarray, array_size);
    print_array(unsortedarray, array_size);

    return 0;
}

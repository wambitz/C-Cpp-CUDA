#include <iostream>

void merge(int * array, int lower_limit, int middle, int upper_limit)
{
    // In recursivity values are stored as 
    int i; // iterator for left array
    int j; // iterator for right array
    int k; // itertaro for tmp array

    int lower_mid = middle;
    int upper_mid = middle + 1;
    
    j = upper_mid;
    i = lower_limit;

    // dynamically store memory for tmp buffer for both sides
    // int * tmp_array = (int *) malloc(upper_limit+1); 
    int tmp_array[50];

    // This is more efficien, another possible implementations are two for loops 
    // one for each side of the array and then compare both sides
    while ( (i <= lower_mid) && (j <= upper_limit)  )
    {
        // compare values from both sides of the tmp splited arrays
        if (array[i] <= array[j])
        {
            tmp_array[k] = array[i];
            i++;
        }
        else
        {
            tmp_array[k] = array[j];
            j++;
        }
        // Increase tmp buffer after writting array value
        k++;
    }

    // Copy remaining values if one array doesn't have more values to compare
    if (i > lower_mid)
    {
        // if left array was depleted then copy the remaining values of right array
        // continue incresing the tmp buffer index k++;
        for (j = j; j <= upper_limit; j++, k++)
        {
            tmp_array[k] = array[j];
        }
    } 
    else 
    {
        // if right array was depleted then copy the remaining values of left array
        // continue incresing the tmp buffer index k++;
        for (i = i; i <= lower_mid; i++, k++)
        {
            tmp_array[k] = array[i];
        }
    } 

    // rewrite values of the original array
    for (k = lower_limit; k <= upper_limit; k++)    
    {
        array[k] = tmp_array[k];
    }
}

void mergesort(int * unsorted_array, int lower_limit, int upper_limit)
{
    int middle;
    // 1. if n > 1
    if (lower_limit < upper_limit)
    {
        middle = (upper_limit + lower_limit) / 2;
        // 2. copy A[0   .. ((n/2)-1)] to B[0..((n/2)-1)]
        // 3. copy A[n/2 ..  (n-1)   ] to C[0..((n/2)-1)]
        // 4. mergersort(B[0 .. ((n/2)-1)])
        mergesort(unsorted_array, lower_limit, middle);
        // 5. mergersort(C[0 .. ((n/2)-1)])
        mergesort(unsorted_array, middle+1, upper_limit);
        // 6. merge(B, C, A)
        merge(unsorted_array, lower_limit , middle, upper_limit);
    }
}

int main(int argc, char const *argv[])
{
    int unsorted_array[] = {8, 3, 2, 9, 7, 1, 5, 4};
    size_t size = sizeof(unsorted_array) / sizeof(int);

    mergesort(unsorted_array, 0, size-1);

    printf("============[SORTED ARRAY]============\n");
    for (int i = 0; i < (int)size; i++)
    {
        printf("Array[%d]: %d\n", i, unsorted_array[i]);
    }

    return 0;
}

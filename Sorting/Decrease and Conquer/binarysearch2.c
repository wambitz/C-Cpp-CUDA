#include <stdio.h>

int binarysearch(int * array, int target_val, int lower_lim, int upper_lim)
{
    while (lower_lim <= upper_lim)
    {
        int middle = (lower_lim + upper_lim) / 2;

        if (target_val == array[middle])
        {
            return middle;
        }

        if (array[middle] < target_val)
        {
            lower_lim = middle + 1;
        }
        else
        {
            upper_lim = middle - 1;
        }
    }
    return -1;
}


int main(int argc, char const *argv[])
{
    int array[] = {3, 14, 27, 31, 39, 42, 55, 70, 74, 81, 85};

    int left_limit = 0;
    int right_limit = sizeof(array) / sizeof(int);

    
    int target_value = 84;
    int result = binarysearch(array, target_value, left_limit, right_limit-1);

    if (array[result] != target_value)
    {
        printf("Value not found.\n");
    }
    else
    {
        printf("Value found at array[%d]: %d\n", result, array[result]);
    }
    
    return 0;
}
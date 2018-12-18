// sequential search algorithm
#include "stdio.h"

int main(int argc, char const *argv[])
{
    unsigned char array[7]   = {2, 3, 5, 8, 1, 9, 4} ;
    unsigned char array_size = sizeof(array);
    unsigned char key        = 3;
    int i = 0;

    while ((array[i] != key) && i < array_size)
    {
        i++;
    }
    
    printf("Value found in index: %d\n", i);

    return 0;
}

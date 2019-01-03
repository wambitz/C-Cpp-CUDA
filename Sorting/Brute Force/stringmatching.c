#include <stdio.h>

int main(int argc, char const *argv[])
{
    char * string = "Have a good day!";
    char * substr = "day";

    int string_size = 0;
    int substr_size = 0;

    int i  = 0;
    while (string[i] != '\0')
    {
        i++;
    }
   string_size = i;

    i = 0;
    while (substr[i] != '\0')
    {
        i++;
    }
    substr_size = i;

    for (i = 0; i < string_size - substr_size; i++)
    {
        int j = 0;
        while ((j < substr_size) && (substr[j] == string[i+j]))
        {
            j++;
            if (j == substr_size)
            {
                return i;
            }
        }
        // return -1;
    }
    return 0;
}

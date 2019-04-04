
#include <string>
#include <iostream>
#include "profiler.h"

bool checkPalindrome(std::string inputString) 
{
    PROFILE_FUNCTION;
    int i = 0;
    int j = inputString.size() - 1;
    
    while (j > i)
    {
        if (inputString[i] != inputString[j])
        {   
            return false;
        }
        i++;
        j--;
    }
    return true;
}

int main(int argc, char const *argv[])
{
    bool result;
    bool expected_val = true;

    // std::string str = "az";
    // std::string str = "aavvaa";
    // std::string str = "zzzazzazz";
    std::string str = "caac";
    // std::string str = "aaabaaaa"; 

    for (int i = 0; i < 10 ; i++)
    {
        result = checkPalindrome(str);
    }

    if (result == expected_val)
    {
        std::cout << "Test PASSED"<< std::endl;
        std::cout << "Result:   " << result << std:: endl;
        std::cout << "Expected: " << expected_val << std:: endl;
    }
    else
    {
        std::cout << "Test FAILED" << std::endl;
        std::cout << "Result:   " << result << std:: endl;
        std::cout << "Expected: " << expected_val << std:: endl;
    }
    return 0;
}

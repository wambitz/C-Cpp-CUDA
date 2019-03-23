
#include <string>
#include <iostream>

bool checkPalindrome(std::string inputString) 
{
    bool pair = inputString.size() % 2 == 0 ? true : false;
    int middle = pair ? (inputString.size() / 2) - 1 : inputString.size() / 2;
   
    if (pair)
    {
        for (int i = 0; i <= middle; i++)
        {
            if (inputString[middle-i] != inputString[middle+1+i])
            {
                return false;
            }
        }
    }
    else
    {
        for (int i = 0; i <= middle; i++)
        {
            if (inputString[middle-i] != inputString[middle+i])
            {   
                return false;
            }
        }
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

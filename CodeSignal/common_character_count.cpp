
#include <iostream>
#include <vector>
#include <string>

int commonCharacterCount(std::string s1, std::string s2) 
{
    auto accum = 0;
    if (s1.size() > s2.size())
    {
        for (auto i = 1; i <= s1.size(); i++)
        {
            for (auto j = i-1; j < s2.size(); j++)
            {
                if (s1[i] == s2[j])
                {
                    i++;
                    // j++;
                    accum++;
                }
            }
               
        }
    }
    else
    {
        for (auto i = 1; i <= s2.size(); i++)
        {
            for (auto j = i-1; j < s1.size(); j++)
            {
                if (s1[i+j] == s2[j])
                {
                    i++;
                    // j++;
                    accum++;
                }
            }
        }
    }
    
    return accum;
}

int main(int argc, char const *argv[])
{
    int result = 0;
    int expected_val = 3;
    std::string s1 = "aabcc";
    std::string s2 = "adcaa";
    result = commonCharacterCount(s1, s2);;
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

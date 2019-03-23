#include <iostream>
#include <vector>

int adjacentElementsProduct(std::vector<int> inputArray) 
{
    int max_product = -2147483647;
    int product = 0;
    for (int i = 0; i < inputArray.size()-1; i++)
    {
        product = inputArray[i] * inputArray[i+1];
        std::cout << product;
        if (product > max_product)
        {
            max_product = product;
        }
    }
    return max_product;
}

int main(int argc, char const *argv[])
{
    int result = 0;
    int expected_val = -12;
    std::vector<int> a = {-23, 4, -3, 8, -12};
    result = adjacentElementsProduct(a);
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
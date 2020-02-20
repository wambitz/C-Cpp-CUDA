#include <iostream>
#include <vector>

int matrixElementsSum(std::vector<std::vector<int>> matrix) 
{
    int accum = 0;
    std::vector<int> ghost;
    std::vector<std::vector<int>>::iterator row;
    std::vector<int>::iterator column;
    for (auto i = 0; i < matrix.size(); i++)
    {
        for (auto j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j] == 0)
            {
                ghost.push_back(j);
                continue;
            }
            if (ghost[j] != 0)
            {
                accum += matrix[i][j];    
            }
            
        }
    }
    return accum;
}

int main(int argc, char const *argv[])
{
    int result = 0;
    int expected_val = 9;
    std::vector<std::vector<int>> matrix = { {0,1,1,2}, {0,5,0,0}, {2,0,3,3} };
    result = matrixElementsSum(matrix);
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
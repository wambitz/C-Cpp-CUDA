#include <iostream>
#include <vector>

int makeArrayConsecutive2(std::vector<int> statues) 
{
    int aux;
    int min_val_index;
    int missing_stats = 0;
    
    for (int i = 0 ; i < statues.size()-1; i++)
    {
        min_val_index = i;
        
        for (int j = i+1; j < statues.size(); j++)
        {
            if (statues[j] < statues[min_val_index])
            {
                min_val_index = j;
            }
        }
        aux = statues[i];
        statues[i] = statues[min_val_index]; 
        statues[min_val_index] = aux;
    }
    
    for (auto i = 0; i != statues.size()-1; i++)
    {
        missing_stats += statues[i+1]-statues[i]-1;
    }
    return missing_stats;
}

int main(int argc, char const *argv[])
{
    int result = 0;
    int expected_val = 3;
    std::vector<int> a = {6, 2, 3, 8};
    result = makeArrayConsecutive2(a);
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

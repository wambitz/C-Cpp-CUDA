#include <iostream>
#include <vector>

int firstDuplicate(std::vector<int> a) 
{
  bool firstmatch = true;
  int match = 0;
  int distance = 0;
  int min_distance = a.size();
  int firstDuplicate = -1; 
  
  for (int i = 0; i < static_cast<int>(a.size())-1 ; i++)
  {
    for (int j = i; j < static_cast<int>(a.size())-1; j++)
    {
      if (a[i] == a[j+1])
      {
        match = a[i];
        distance = (j+1) - i;

        if (firstmatch || (distance < min_distance))
        {
          min_distance = distance;
          firstDuplicate = match;
          firstmatch = false;
        }
      }
    }
  }
  return firstDuplicate;
}

int main(int argc, char const *argv[])
{
    int result = 0;
    int expected_val = 1;
    std::vector<int> a = {1, 1, 2, 2, 1};
    result = firstDuplicate(a);
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

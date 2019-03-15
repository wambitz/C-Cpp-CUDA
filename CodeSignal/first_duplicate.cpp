#include <iostream>
#include <vector>

int firstDuplicate(std::vector<int> a) 
{
  bool firstmatch = true;
  unsigned char min_distance = a.size();
  int firstDuplicate = -1; 
  
  for (unsigned char i = 0; i < static_cast<unsigned char>(a.size())-1 ; i++)
  {
    for (unsigned char j = i; j < static_cast<unsigned char>(a.size())-1; j++)
    {
      if (a[i] == a[j+1])
      {
        if (firstmatch || ( ((j+1)-i) < min_distance))
        {
          min_distance = (j+1) - i;
          firstDuplicate = a[i];
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

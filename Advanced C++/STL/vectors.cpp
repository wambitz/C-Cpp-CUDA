#include <iostream>
#include <vector>

int main()
{
    std::vector<std::string> strings;    

    // dynamic memory
    strings.push_back("one");
    strings.push_back("two");
    strings.push_back("three");

    // array like notation
    std::cout << strings[1] << std::endl;
    // instead of sizeof
    std::cout << strings.size() << std::endl;

    for (int i = 0; i < strings.size(); i++)
    {
        std::cout << strings[i] << std::endl;
    }
    
    for (std::vector<std::string>::iterator it = strings.begin();
         it != strings.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    std::vector<std::string>::iterator it = strings.begin();
    it++;
    std::cout << *it << std::endl;

    return 0;

}
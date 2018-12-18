#include <iostream>
#include <list>

// Lists are different from vectors in the way that vectors allocates memory continuously.
// Lists are linked lists the values are linked by nodes (pointers). 
// You could access data to any point of the list, indexes are not valid, iterators can be used though.

int main(int argc, char const *argv[])
{
    std::list<int> numbers;
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);

    numbers.push_front(0);

    std::list<int>::iterator it = numbers.begin();
    std::cout << "Element: " << *it << std::endl;

    it++;;
    std::cout << "Element: " << *it << std::endl;

    numbers.insert(it, 100);
    std::cout << "Element: " << *it << std::endl; // add element to current iterator position

    std::list<int>::iterator eraseIt = numbers.begin();
    eraseIt++;
    numbers.erase(eraseIt);
    std::cout << "Element: " << *eraseIt << std::endl;

    for (std::list<int>::iterator it = numbers.begin(); it != numbers.end(); /*it++*/)
    {
        if (*it == 2)
        {
            numbers.insert(it, 1234);
        }
        if (*it == 1)
        {
            // numbers.erase(it);  // this invalidates the iterator
            it = numbers.erase(it);
        }
        else
        {
            it++;
        }
    }

    for (std::list<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
    {
        std::cout << *it << std::endl;
    }
    return 0;
}
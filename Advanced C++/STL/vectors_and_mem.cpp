#include <iostream>
#include <vector>

int main(int argc, char const *argv[])
{
    // Create vector with defualt size and initilize it with 1
    std::vector<double> numbers(0);
    std::cout << "Size: " << numbers.size() << std::endl;

    int capacity = numbers.capacity();
    std::cout << "Capacity: " << capacity << std::endl;

    for (int i = 0; i < 10000; i++)
    {
        if (numbers.capacity() != capacity)
        {
            capacity = numbers.capacity();
            std::cout << "Capacity: " << capacity << std::endl;
        }
        numbers.push_back(i);
    }
    
    // clears the elements but it doesn't reduce the capacity
    numbers.clear();
    std::cout << "Size: " << numbers.size() << std::endl;
    std::cout << "Capacity: " << capacity << std::endl;

    // update the intervnal variable that indictates the size
    //  but doesn't modify the real capacity
    numbers.resize(100);
    std::cout << "Size: " << numbers.size() << std::endl;
    std::cout << "Capacity: " << capacity << std::endl;

    // update the intervnal variable that indictates the size
    //  but doesn't modify the real capacity unless it's bigger the current
    numbers.reserve(100);
    std::cout << "Size: " << numbers.size() << std::endl;
    std::cout << "Capacity: " << capacity << std::endl;

    return 0;
}

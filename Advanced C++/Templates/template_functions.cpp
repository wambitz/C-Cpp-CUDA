#include <iostream>

using namespace std;

// could be a primitive type therefore typename
template <typename T> 
void print(T n)
{
    cout << "Template version: " << n << endl;
}

void print(int value) 
{
    cout << "Non-template version" << value << endl;
}

template <typename T> 
void show()
{
    cout << T() << endl;
}

int main()
{
    print<string>("Hello");
    print<int>(5);

    // Type inference
    print("Hi there!");
    print<>(6);

    // Overloading, might depend on the compiler
    print(6);

    // show(); -> This doesn't compile since no datatype can be infered
    show<double>();

    return 0;
}
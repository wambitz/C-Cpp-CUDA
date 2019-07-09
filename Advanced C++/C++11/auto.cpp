#include <iostream>
#include <typeinfo>

using namespace std;

// auto test() // -> Compiler error, cant' determine return type
// {
//     return 7;
// }

auto test() -> int 
{
    return 100;
}

template <class T>
// auto test2(T value) -> int // this doesn't work with other types then:
auto test2(T value) -> decltype(value)
{
    return value;
}


template <class T, class S>
auto test3(T value1, S value2) -> decltype(value1 + value2)
{
    return value1 + value2;
}

int get()
{
    return 999;
}

auto test4() -> decltype(get())
{
    return get();
}

int main(int argc, char const *argv[])
{
    auto value = 7;
    auto text  = "Hello";

    cout << value << endl;
    cout << test() << endl;

    cout << test2("Hello there") << endl;
    cout << test3(5, 6) << endl;

    cout << test4() << endl;

    return 0;
}
#include <iostream>
#include <typeinfo>

using namespace std;

int main(int argc, char const *argv[])
{
    int value;
    string value2;

    decltype(value2) name = "Bob";

    cout << "value: "  << typeid(value).name()  << endl;
    cout << "value2: " << typeid(value2).name() << endl;

    cout << name << endl;

    return 0;
}

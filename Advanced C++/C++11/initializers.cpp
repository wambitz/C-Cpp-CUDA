#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
    // NOTE: C++98
    int values[] = {1, 4, 5};

    cout << values[0] << endl;

    class C 
    {
    public:
        string text;
        int id;
    };

    C c1 = {"Hello", 7};
    
    cout << c1.text << endl;

    struct S 
    {
    public:
        string text;
        int id;
    };

    S s1 = {"Hello", 7};

    cout << s1.text << endl;

    struct R
    {
    public:
        string text;
        int id;
    } r1 = {"Hello", 7},  r2 = {"Hi", 9};

    // r1 = {"Hello", 7 } // -> Compiler error

    cout << r1.text << endl;
    cout << r2.text << endl;

    // C++11
    vector<string> strings;
    strings.push_back("One");
    strings.push_back("Two");
    strings.push_back("Three");

    int value[5];
    cout << value << endl;

    string text{"Hello"};
    cout << text << endl;

    int numbers[]{1, 2, 4};
    cout << numbers[1] << endl;

    int *pInts = new int[3]{1, 2, 3};
    cout << pInts[1] << endl;
    delete pInts;

    int value1{};
    cout << value1 << endl;

    int * pSomething



    return 0;
}

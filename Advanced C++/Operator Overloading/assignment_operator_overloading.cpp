#include <iostream>

using namespace std;

class Test 
{
private:

    string name;
    int id;

public:

    Test() = default;

    // Test(const Test &other)
    // {
    //     // cout << "Copy constructor running!" << endl;
    //     name = other.name;
    //     id  = other.id;
    // }

    Test(int id, string name) : id(id), name(name) {}
    
    Test(const Test &other)
    {
        cout << "Copy constructor running" << endl;

        id = other.id;
        name = other.name;
    }
    
    void print() const
    {
        cout << id << ": " << name << endl;
    }

    // bool operator < (const Test &other) const
    // {
    //     return name < other.name;
    // }
    const Test &operator = (const Test &other)
    {
        cout << "Assignment running" << endl;

        id = other.id;
        name = other.name;

        return *this;
    }
};

int main(int argc, char const *argv[])
{
    Test test1(30, "Julio");
    cout << "Print test1 -> " << flush;
    test1.print();

    Test test2(26, "Leti");
    test2 = test1;
    cout << "Print test2 -> " << flush;
    test2.print();

    Test test3;
    // test3= test2 = test1;
    test3.operator=(test2);
    cout << "Print test3 -> " << flush;
    test3.print();

    cout << endl;
    // Copy initialization -> No assigment running
    // Here the copy constructor is being running -> Deep copy
    // The copy constructor was created by default without defining it 
    // NOTE: Notice that here we are not creating/defining the object and then point to another object
    // Here we are copying an object since the declaration therefore initializing 
    Test test4 = test1; 
    test4.print();

    return 0;
}


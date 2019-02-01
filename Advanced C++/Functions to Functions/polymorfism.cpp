#include <iostream>

using namespace std;

class Parent
{
private: 
    int one;
public:
    Parent()=default;

    Parent(const Parent &parent)
    {
        cout << "Copy Parent" << endl;
        this->one = parent.one;
    }

    virtual void print()
    {
        cout << "parent" << endl;
    }

    virtual ~Parent() {}
};

class Child : public Parent 
{
private:
    int two;
public:
    void print()
    {
        cout << "child" << endl;
    }
};

int main(int argc, char const *argv[])
{
    Child child;
    Parent parent;

    child.print();
    parent.print();

    Child c1;
    Parent &p1 = c1; // -> without virtual parent implementation is called
    p1.print();

    // Slicing: This occurs if we copy by value and get a reference
    // This throws away all extra variables from derived class
    Parent p2 = Child(); // -> have to use pointer or reference to use derived class
    p2.print();

    return 0;
}

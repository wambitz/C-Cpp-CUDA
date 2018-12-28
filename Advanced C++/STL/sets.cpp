#include <iostream>
#include <set>

using namespace std;

class Test 
{
private:

    string name;
    int id;

public:

    Test() = default;

    Test(const Test &other)
    {
        // cout << "Copy constructor running!" << endl;
        name = other.name;
        id  = other.id;
    }

    Test(int id, string name) : id(id), name(name) {}
    
    void print() const
    {
        cout << id << ": " << name << endl;
    }

    bool operator < (const Test &other) const
    {
        return name < other.name;
    }
};

int main(int argc, char const *argv[])
{
    // Sets store only one instance of a value
    set<int> numbers;

    numbers.insert(50);
    numbers.insert(10);
    numbers.insert(30);
    numbers.insert(30); // This number wont be duplicated in th colllection
    numbers.insert(20);

    for (set<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
    {
        cout << *it << endl;
    }

    // Checks if element exist in a set
    set<int>::iterator itFind = numbers.find(30);

    if (itFind != numbers.end())
    {
        cout << "Found: " << *itFind << endl;
    }

    if (numbers.count(30))
    {
        cout << "Number found " << *itFind << endl;
    }

    set<Test> tests;
    tests.insert(Test(10, "Mike"));
    tests.insert(Test(30, "Joe"));
    tests.insert(Test(333, "Joe"));
    tests.insert(Test(20, "Sue"));

    for (set<Test>::iterator it = tests.begin(); it != tests.end(); it++)
    {
        it->print();
    }


    return 0;
}

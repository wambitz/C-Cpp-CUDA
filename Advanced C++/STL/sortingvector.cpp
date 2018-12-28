#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;

class Test
{
private:
    int _id;
    string _name;

public:
    Test(int id, string name): _id(id), _name(name) {}
    void print() { cout << _id << ": " << _name << endl; }
    bool operator < (const Test& test) const
    {
        return _id < test._id;
    }
    // Dont use this, better use getters and setters
    friend bool comp(const Test& a, const Test& b);
};

bool comp(const Test& a, const Test& b)
{
    return a._name < b._name;
}

int main(int argc, char const *argv[])
{
    vector<Test> tests;
    tests.push_back(Test( 5, "Mike"));
    tests.push_back(Test(10, "Sue"));
    tests.push_back(Test( 7, "Raj"));
    tests.push_back(Test( 3, "Vicky"));

    sort(tests.begin(), tests.end(), comp);

    for (int i = 0; i < static_cast<int>(tests.size()); i++)
    {
        tests[i].print();
    }

    return 0;
}

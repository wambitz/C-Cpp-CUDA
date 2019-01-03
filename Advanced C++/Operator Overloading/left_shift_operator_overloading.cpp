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
    
    friend ostream &operator << (ostream &out, const Test &test)
    {
        out << test.id << ": " << test.name;
    }

    // int get_id() { return id; }
    // string get_name() {return name; } 

    // ostream operator << (ostream out)
    // {
    //     out << get_id() << ": " << get_name();
    // }

};

int main(int argc, char const *argv[])
{
    Test test1(30, "Julio");
    cout << test1 << endl;

    return 0;
}

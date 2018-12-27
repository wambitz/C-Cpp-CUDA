#include <iostream>
#include <map>

using namespace std;

class Person 
{
private:

    string name;
    int age;

public:

    Person() = default;

    Person(const Person &other)
    {
        cout << "Copy constructor running!" << endl;
        name = other.name;
        age  = other.age;
    }

    Person(string name, int age) : name(name), age(age) {}
    
    void print() const
    {
        cout << name << ": " << age << flush;
    }

    bool operator < (const Person &other) const
    {
        // Key no updated otherwise, value is though
        if (name == other.name)
        {
            return age < other.age;
        }
        else
        {
            return name < other.name;
        }
    }
};

int main(int argc, char const *argv[])
{
    map<Person, int> people;

    people[Person("Mike" , 40)] = 40;
    people[Person("Mike" , 444)] = 123; 
    people[Person("Sue" , 30)] = 30;
    people[Person("Raj" , 20)] = 20;

    // people.insert(make_pair(55, Person("Bob", 45)));
    // people.insert(make_pair(55, Person("Sue", 24)));

    for (map<Person, int>::iterator it = people.begin(); it != people.end(); it++)
    {
        cout << it->second << ": " << flush;
        it->first.print();
        cout << endl;
    }

    return 0;
}

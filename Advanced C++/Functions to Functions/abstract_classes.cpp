#include <iostream>

using namespace std;

// Abstract class -> Can't be instantiated
class Animal
{
public: 
    // Pure virtual function
    virtual void run() = 0;
    virtual void speak() = 0;
};

class Dog : public Animal 
{
public:
    void speak() { cout << "Woof!" << endl;}
};

class Labrador : public Dog 
{
public:
    Labrador()
    {
        cout << "new labrador" << endl;
    }
    virtual void run()
    {
        cout << "Labrador running" << endl;
    }
};

void test(Animal &a)
{
    a.run();
}

int main(int argc, char const *argv[])
{
    // Animal animal; Error: Abstract class

    // Dog dog;
    // dog.speak(); -> This was ok until we added
    // run pure virtual function and therfore all
    // pure virtual functions have to be implemented

    Labrador lab;
    lab.run();
    lab.speak();

    // Animal animals[5]; -> Error this doesn't compile
    // since it's calling the Abstract class constructor

    // Instead we can implement polymofism
    Animal * animals[5];
    animals[0] = &lab;
    animals[0]->speak();

    test(lab);
    
    return 0;
}

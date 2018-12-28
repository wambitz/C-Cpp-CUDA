#include <iostream>
#include <stack>
#include <queue>

using namespace std;

class Test 
{
private:
    string _name;
public:
    Test(string name) : _name(name) {}
    ~Test() { /* cout << "Object destroyed" << endl; */ }

    void print () { cout << _name << endl
    ; }
};

int main(int argc, char const *argv[])
{
    // LIFO
    stack<Test> testStack;

    testStack.push(Test("Mike"));
    testStack.push(Test("Jhon"));
    testStack.push(Test("Sue"));

    cout << endl;
    // Here we are getting a reference not creating a new object
    // like the example below were we are getting a reference -> shallow copy
    /* This is invalid code since the object has been destroyed
    Test &test1 = testStack.top();
    testStack.pop();
    test1.print(); // Reference refers to destroyed objects
    */

    testStack.pop();
    Test test2 = testStack.top();
    test2.print();
    cout << endl;

    while (testStack.size() > 0)
    {
        Test &test = testStack.top();
        test.print();
        testStack.pop();
    }

    // Queue -> FIFO
    queue<Test> testQueue;

    testQueue.push(Test("Mike"));
    testQueue.push(Test("Jhon"));
    testQueue.push(Test("Sue"));

    cout << endl;

    testQueue.back().print();
    cout << endl;

    while (testQueue.size() > 0)
    {
        Test &test = testQueue.front();
        test.print();
        testQueue.pop();
    }

    return 0;
}

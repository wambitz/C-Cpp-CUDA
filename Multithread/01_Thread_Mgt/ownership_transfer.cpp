#include <thread>
#include <iostream>
#include <chrono> 

using namespace std;

void foo()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    cout << "Hello from foo" << endl;
}

void bar()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    cout << "Hello from bar" << endl;
}

void run()
{
    thread t1(foo);
    // thread bar_thread = foo_thread; //-> Compiler error
    thread t2 = move(t1); 
    
    t1 = thread(bar); // no explicit ownership move, this is not valid with variable names

    // thread t3(foo); 
    // t1 = move(t3); // runtime error

    t1.join();
    t2.join();
    // t3.join();
}

int main(int argc, char const *argv[])
{
    run();
    return 0;
}

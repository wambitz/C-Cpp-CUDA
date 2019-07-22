#include <thread>
#include <iostream>
#include <chrono> 
#include <vector>

using namespace std;

class thread_guard
{
public: 
    // explicit avoid any implicit conversions
    explicit thread_guard(thread & _t) : t(_t) {} 
    ~thread_guard()
    {
        if (t.joinable())
        {
            t.join();
        }
    }
    // explicitly delete copy constructor and copy assignment operator
    thread_guard(thread_guard & ) = delete;
    thread_guard & operator= (thread_guard & ) = delete;

private:
    thread & t;
};

void foo()
{
    // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    cout << "Hello from foo" << endl;
}

void other_operations()
{
    // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    cout << "This is an operation" << endl;
    throw std::runtime_error("This is a runtime error");
}

void run()
{
    thread foo_thread(foo);
    thread_guard tg(foo_thread);
    
    // this doesn't entirely prevent from running the thread
    // and when handling several threads can be cumbersome
    try
    {
        other_operations();
    }
    catch(const std::exception& e)
    {
        cerr << e.what() << '\n';
    }
}

int main(int argc, char const *argv[])
{
    run();
    return 0;
}
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
    std::thread foo_thread(foo);
    std::thread bar_thread(bar);
    bar_thread.detach();
    // foo_thread.detach();
    cout << "This after bar thread detach" << endl; 

    foo_thread.join();
    cout << "This is after foo thread join" << endl;
}

int main(int argc, char const *argv[])
{
    run();
    return 0;
}

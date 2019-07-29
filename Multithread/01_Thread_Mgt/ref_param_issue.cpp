#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void f2(int &x)
{
    // Exceptions occurs after 5 secods tread 1 in f1() goes at out scope and delete thread 2
    while(true)
    {
        try
        {
            cout << x << endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
        catch(const std::exception& e)
        {
            cerr << e.what() << '\n';
            throw runtime_error("This is a runtime error");
        }
        
    }
}

void f1()
{
    int x = 5;
    // f1() launches thread 2 and detach not blocking execution   
    thread t2(f2, ref(x));
    t2.detach();
    this_thread::sleep_for(chrono::milliseconds(5000));
    cout << "thread 1 finished execution" << endl;
}

void run()
{
    // thread 1 lanches f1()
    thread t1(f1);
    t1.join();
}


int main(int argc, char const *argv[])
{
    // main thread launch run()
    run();
    return 0;
}
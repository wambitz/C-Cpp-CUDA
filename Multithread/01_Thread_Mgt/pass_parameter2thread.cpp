#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void f1(int x, int y)
{
    cout << "X + Y = " << x + y << endl; 
}

void f2(int &x)
{
    while(true)
    {
        cout << "t1 value of x: " << x << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

}

void run()
{
    int x = 9;
    cout << "Main thread value of x: " << x << "; TID: " << std::this_thread::get_id() << endl;

    // std::ref() allows to update referenced values to the thread
    thread t1(f2, ref(x));
    this_thread::sleep_for(chrono::milliseconds(5000));

    x = 15;
    cout << "Main thread value of x has changed to: " << x << "; TID: " << std::this_thread::get_id() << endl;

    t1.join();
}


int main(int argc, char const *argv[])
{
    run();
    return 0;
}

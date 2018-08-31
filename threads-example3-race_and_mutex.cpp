#include <thread>
#include <string>
#include <mutex>
#include <iostream>

std::mutex mutx;

void shared_print(std::string msg, int id)
{
    mutx.lock();
    std::cout << msg << id << std::endl;
    mutx.unlock();
}

void function1()
{
    for (int i = 0; i > -100; i--)
    {
        shared_print(std::string("From t1: "), i);
    }
}

int main(int argc, char const *argv[])
{
    std::thread t1(function1);

    for (int i = 0; i < 100; i++)
    {
        shared_print(std::string("From main: "), i);
    }

    t1.join();

    return 0;
}

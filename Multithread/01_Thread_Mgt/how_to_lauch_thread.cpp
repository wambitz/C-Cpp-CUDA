// #include "thread_mgt.h"
// #pragma once

#include <iostream>
#include <thread>

void foo()
{
    printf("Hello from foo - %d \n", std::this_thread::get_id());
}

class callable_classx
{
public:
    void operator()()
    {
        printf("Hello from class with function call operator - %d \n", std::this_thread::get_id());
    }
};

void run()
{
    // NOTE: Calling default constructor from a thread return zero ID, same case after calling join on a thread
    std::thread t1(foo);
    callable_class obj;
    std::thread t2(obj);
    std::thread t3([]{ printf("Hello from lambda - %d \n",  std::this_thread::get_id()); });

    t1.join();
    t2.join();
    t3.join();

    printf("Hello from main - %d \n", std::this_thread::get_id());
}

int main(int argc, char const *argv[])
{
    run();
    return 0;
}

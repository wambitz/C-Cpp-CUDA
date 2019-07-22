#include <thread>
#include <iostream>

void test()
{
    printf("Hello from test\n");
}

int main(int argc, char const *argv[])
{
    std::thread t1(test); // std::termninate exception if join is not call

    if (t1.joinable())
    {
        printf("Thread 1 is joinable before join \n");
    }
    else
    {
        printf("Thread 1 is not joinable before join \n");
    }

    t1.join();

    if (t1.joinable())
    {
        printf("Thread 1 is joinable after join \n");
    }
    else
    {
        printf("Thread 1 is not joinable after join \n");
    }

    std::thread t2; // default constructor don't let join thread

    if (t2.joinable())
    {
        printf("Thread 2 is joinable \n");
    }
    else
    {
        printf("Thread 2 is not joinable \n");
    }
    
    return 0;
}

#include <iostream>
#include <thread>

void PrintMessage()
{
    std::cout << "Beaty is only skin-depp" << std::endl;
}

int main(int argc, char const *argv[])
{
    std::thread t1(PrintMessage);   // t1 starts running
    // t1.join();                   // main thread waits for t1 to finish
    t1.detach();                    // t1 will freely rumn on its own -- daemon process 

    //... later on

    // t1.join();                       // crash
    if (t1.joinable())
    {
        t1.join();
    }

    return 0;
}

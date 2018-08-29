#include <iostream>
#include <thread>

void PrintMessage()
{
    std::cout << "Beaty is only skin-depp" << std::endl;
}

class Functor 
{
public:
    // void operator()(std::string message)
    void operator()()
    {
        for (int i = 0; i > -100; i--)
        {
            std::cout << "from t1: " << i << std::endl;
        }
        // std::cout << "t1 says: " << msg << std::endl;
    }

};

int main(int argc, char const *argv[])
{
    Functor fct;
    // std::string s = "Where is no trust, there is no love";
    // std::thread t1((Functor()),s);   // t1 starts running
    std::thread t1(fct);   // t1 starts running
    // using RAII
    // Wrapper w(t1);

    try
    {
        for (int i = 0; i < 100; i++)
        {
            // std::cout << "from main: " << s << std::endl;
            std::cout << "from main: " << i << std::endl;
        }
    }
    catch (...)
    {
        t1.join();
        throw;
    }

    t1.join();

    return 0;
}

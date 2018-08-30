#include <iostream>
#include <thread>

void PrintMessage()
{
    std::cout << "Beaty is only skin-depp" << std::endl;
}

class Functor 
{
public:
    void operator()(std::string msg)
    {
        std::cout << "t1 says: " << msg << std::endl;
    }

};

int main(int argc, char const *argv[])
{
    std::string s = "Where is no trust, there is no love";
    std::thread t1((Functor()), s);   // t1 starts running
    
    try
    {
        std::cout << "from main: " << s << std::endl;
    }
    catch (...)
    {
        t1.join();
        throw;
    }

    t1.join();

    return 0;
}

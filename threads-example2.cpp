#include <iostream>
#include <thread>

void PrintMessage()
{
    std::cout << "Beaty is only skin-depp" << std::endl;
}

class Functor 
{
public:
    void operator()(std::string& msg)
    {
        std::cout << "t1 says: " << msg << std::endl;
        msg = "Trust is the mother of deceit.";
    }

};

int main(int argc, char const *argv[])
{
    std::string s = "Where is no trust, there is no love";
    std::cout << std::this_thread::get_id() << std::endl;

    std::thread t1((Functor()), std::move(s));   // t1 starts running
    // std::thread t2 = t1; // this won't compile, threads can not be copied
    std::cout << t1.get_id() << std::endl;
    
    std::thread t2 = std::move(t1); // this is ok but t1 will be empty
    
    t2.join();
    std::cout << "from main: " << s << std::endl;

    return 0;
}

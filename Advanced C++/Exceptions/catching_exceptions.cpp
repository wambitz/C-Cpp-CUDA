// #include <iostream>
#include <exception>

using namespace std;

void GoesWrong()
{
    bool error1Detected = true;
    bool error2Detected = false;

    if (error1Detected)
    {
        throw bad_alloc();
    }

    if (error2Detected)
    {
        throw exception();
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        GoesWrong();
    }
    // if a parent class is called before the exception
    // might not work as expected because of polymorfism
    // always call derived classes before.
    catch(bad_alloc &error)
    {
        cout << "Catching bad_alloc: " << error.what() << endl;
    }
    catch(exception &error)
    {
        cout << "Catching exception: " << error.what() << endl;
    }
    
    return 0;
}

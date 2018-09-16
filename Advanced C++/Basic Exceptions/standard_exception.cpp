#include <iostream>
using namespace std;

class CanGoWrong
{
public:
    CanGoWrong()
    {
        char * pMemory = new char[999999999999];
        delete [] pMemory;
    }
};

int main(int argc, char const *argv[])
{
    try
    {
        CanGoWrong wrong;
    }
    catch(bad_alloc &error)
    {
        cout << "Caught Exception: " << error.what() << endl;
    }
    
    cout << "Still running..." << endl;
    return 0;
}

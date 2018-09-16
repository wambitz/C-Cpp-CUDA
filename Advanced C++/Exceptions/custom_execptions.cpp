#include <iostream>
#include <exception>

using namespace std;

class CustomException : public exception
{
public:
    virtual const char* what() const throw()
    {
        return "Something bad happened!";
    }
};

class Test
{
public: 
    void GoesWrong()
    {
        throw CustomException();
    }
};

int main(int argc, char const *argv[])
{
    Test test;
    try
    {
        test.GoesWrong();
    }
    catch(CustomException &error)
    {
        cout << error.what() << endl;
    }
    return 0;
}

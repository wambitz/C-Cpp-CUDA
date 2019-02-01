#include <iostream>

using namespace std;

struct Test
{
    virtual bool operator () (string &text) = 0;
    virtual ~Test(){}
};

struct MatchTest : public Test
{
     bool operator () (string &text)
    {
        return text == "lion";
    }
};

void check(string text, Test &test)
{
    if (test(text))
    {
        cout << "Test matches!" << endl;
    }
    else
    {
        cout << "No match." << endl;
    }
}

int main(int argc, char const *argv[])
{
    MatchTest pred;
    string value = "lion";
    cout << pred(value) << endl;
    
    MatchTest m;
    check("lion", m);

    return 0;
}

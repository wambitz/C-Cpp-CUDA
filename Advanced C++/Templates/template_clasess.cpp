#include <iostream>

using namespace std;

template <class T, class K>
class Test
{
private:
    T obj;
public:
    Test(T obj) { this->obj = obj; }
    void print() { cout << obj << endl; }
};

int main(int argc, char const *argv[])
{
    Test<string, int> t("Julio");
    t.print();
    
    return 0;
}

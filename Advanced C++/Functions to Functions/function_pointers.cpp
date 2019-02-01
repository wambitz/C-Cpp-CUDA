#include <iostream>

using namespace std;

void test(int value)
{
    cout << "Hello: " << value << endl;
}

int main()
{
    cout << "First call test(): \t\t";
    test(7);
    
    // void * p_test(); -> this doesnt' work
    // due to operators precende, it's the same as a 
    // function declaration
    // void (*p_test)(int); 

    // p_test = &test -> ampersan not really needed,
    // the function name is already a pointer similar to arrays
    // p_test = test;
    void (*p_test)(int) =  test; // -> Same as 2 statements above;

    // *p_test() -> also this doesn't work
    // also for operators precedence
    // could be interpreter that the function returns 
    // a reference and the we are dereferencing it
    cout << "Second call (*p_test)(): \t";
    (*p_test)(8);

    // Since we are already pointing to the same address we dont need 
    // the dereference operator only to call the function
    cout << "Third call p_test(): \t\t";
    p_test(9); 
    

    return 0;
}
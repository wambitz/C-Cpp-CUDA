/* Excercise 1 - Instructions: 

Thread A should execute a function called function A and thread B should execute the function call function B.
From function A, you have to launch another thread called thread C which will run the function call test. All these
function should print out hello from particular function.

Then I want you to order the threads in the order they are going to finish the execution.
First thread in the order should be the first one to finish. Last thread in the order should be the last one to finish.
Consider the main thread as well. */

#include <iostream>
#include <thread>

void test()
{
    printf("Hello from test - %d \n", std::this_thread::get_id());
}

void functionB()
{
    printf("Hello from function B - %d \n", std::this_thread::get_id());
}

void functionA()
{
    std::thread tC(test);
    tC.join();
    printf("Hello from function A - %d \n", std::this_thread::get_id());
}

void run()
{
    std::thread tA(functionA);
    std::thread tB(functionB);

    tA.join();
    tB.join();

    printf("Hello from main - %d \n", std::this_thread::get_id());
}


int main(int argc, char const *argv[])
{
    run();    
    return 0;
}

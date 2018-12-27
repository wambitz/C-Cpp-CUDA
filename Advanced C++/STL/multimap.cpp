#include <iostream>
#include <map>

using namespace std;

int main(int argc, char const *argv[])
{
    // Multimap allows to have multiple equal keys 
    multimap<int, string> lookup;

    lookup.insert(make_pair(30, "Mike"));
    lookup.insert(make_pair(10, "Vicky"));
    lookup.insert(make_pair(30, "Raj"));
    lookup.insert(make_pair(20, "Bob"));

    // iterate through all values
    for (multimap<int, string>::iterator it = lookup.begin(); it != lookup.end(); it++)
    {
        cout << it->first << ": " << it->second << endl;
    }

    cout << "---------------------------------" << endl;

    // iterate through values after specified key
    for (multimap<int, string>::iterator it = lookup.find(20); it != lookup.end(); it++)
    {
        cout << it->first << ": " << it->second << endl;
    }


    cout << "---------[Pair of multimaps iterators]---------" << endl;

    // map of iterators
    pair<multimap<int, string>::iterator, multimap<int, string>::iterator> its = lookup.equal_range(30);

    // iterate through maps and find values that match specified value with equal_range()
    for (multimap<int, string>::iterator it = its.first; it != its.second; it++)
    {
        cout << it->first << ": " << it->second << endl;
    }

    cout << "--------------[C++11 Syntax]-------------------" << endl;
    // This can be reduced with C++11 syntax as follows:
    auto its2 = lookup.equal_range(30);

    // iterate through maps and find values that match specified value with equal_range()
    for (multimap<int, string>::iterator it = its2.first; it != its2.second; it++)
    {
        cout << it->first << ": " << it->second << endl;
    }


    return 0;
}


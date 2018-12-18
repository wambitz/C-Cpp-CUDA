#include <iostream>
#include <map>

using namespace std;

int main(int argc, char const *argv[])
{
    map<string, int> ages;
    
    ages["Raj"]   = 20;
    ages["Mike"]  = 40;
    ages["Vicky"] = 30;
    ages["Mike"]  = 70;
    
    cout << ages["Raj"] << endl;
    cout << ages["Sue"] << endl << endl;

    // pair<string, int> AddToMap("Peter", 100);
    // ages.insert(AddToMap);

    // Code from above is the same as:
    ages.insert(pair<string, int>("Peter", 100));

    if (ages.find("Vicky") != ages.end())
    {
        cout << "Found Vicky" << endl << endl;;
    }
    else
    {
        cout << "Ket not found" << endl;
    }

    for (map<string, int>::iterator it = ages.begin(); it != ages.end(); it++)
    {
        pair<string, int> age = *it;
        cout << age.first << ": " << age.second << endl;
    }

    cout << endl;
    for (map<string, int>::iterator it = ages.begin(); it != ages.end(); it++)
    {
        cout << it->first << ": " << it->second << endl;
    }
    return 0;
}

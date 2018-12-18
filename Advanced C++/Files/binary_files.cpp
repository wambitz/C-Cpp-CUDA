#include <iostream>
#include <fstream>

using namespace std;

// Disable padding for this struct
#pragma pack(push, 1)
struct Person
{
    char name[50];
    int age;
    double height;
};
#pragma pack(pop)

int main(int argc, char const *argv[])
{
    Person Frodo = {"Frodo", 220, 0.8};
    Person Sam = {"Sam", 420, 15.1};

    // cout << sizeof(Person) << endl;
    string filename = "Advanced C++/Files/test.bin";

    ///// Write binany file /////
    
    ofstream outputfile;
    outputfile.open(filename, ios::binary);

    if (outputfile.is_open())
    {
        // outputfile.write((char *)&someone, sizeof(Person));
        outputfile.write(reinterpret_cast<char *>(&Frodo), sizeof(Person));
        outputfile.write(reinterpret_cast<char *>(&Sam), sizeof(Person));
        outputfile.close();
    }
    else
    {
        cout << "Could not create file: " + filename << endl;
    }

    ///// Read binany file /////

    Person the_chose_one, someone_else;

    ifstream inputfile;
    inputfile.open(filename, ios::binary);

    if (inputfile.is_open())
    {
        // outputfile.write((char *)&someone, sizeof(Person));
        inputfile.read(reinterpret_cast<char *>(&the_chose_one), sizeof(Person));
        inputfile.read(reinterpret_cast<char *>(&someone_else), sizeof(Person));
        inputfile.close();
    }
    else
    {
        cout << "Could not create file: " + filename << endl;
    }

    cout << the_chose_one.name << ", " << the_chose_one.age << ", " << the_chose_one.height << endl;
    cout << someone_else.name << ", " << someone_else.age << ", " << someone_else.height << endl;
    
    return 0;
}

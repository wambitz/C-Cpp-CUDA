#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Disable padding for this struct
struct Student
{
    char name[10];
    unsigned short age;
};

int main(int argc, char const *argv[])
{
    Student apprentice[3] = {{"Jhon" , 21}, {"Jerry", 22}, {"Jimmy", 23}};
 
    // Serialization struct to student.data
    ofstream output_file("Tmp/students.data", ios::binary);
    output_file.write(reinterpret_cast<char*>(&apprentice), sizeof(apprentice));
    cout << "Size of apprentice: \t" << sizeof(apprentice) << " bytes" << endl;
    output_file.close();

    // Reading from it
    ifstream input_file("Tmp/students.data", ios::binary);
    Student master[3];
    input_file.read(reinterpret_cast<char*>(&master), sizeof(master));
    cout << "Size of master : \t" << sizeof(master) << " bytes" << endl << endl;  
    input_file.close();

    for (unsigned short idx = 0; idx < 3; idx++)
    {
        // If you wanted to search for specific records,
        // you should do it here! (if idx==2)
        cout << "Record #: \t" << idx                << endl;
        cout << "Name: \t\t"   << master[idx].name   << endl;
        cout << "Age: \t\t"    << master[idx].age    << endl;
        cout << endl;
    }
    return 0;
}

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{
    // ofstream file;
    fstream file;
    string output_file_name = "Advanced C++/Files/text.txt";

    // file.open(output_file_name);
    file.open(output_file_name, ios::out);

    if (file.is_open())
    {
        file << "Hello there" << endl;
        file << 123 << endl;
        file.close();
    }
    else
    {
        cout << "Could not create file: " << output_file_name << endl;
    }

    return 0;
}
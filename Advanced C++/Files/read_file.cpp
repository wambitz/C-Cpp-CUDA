#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream infile;
    // fstream file;
    string input_file_name = "Advanced C++/Files/test.txt";

    infile.open(input_file_name);
    // file.open(output_file_name, ios::out);

    if (infile.is_open())
    {
        string line;
        
        // while (!infile.eof())
        while (infile)
        {
            // infile >> line;
            getline(infile ,line);
            cout << line << endl;
        }
        infile.close();
    }
    else
    {
        cout << "Could not open file: " << input_file_name << endl;
    }
    
    return 0;
}
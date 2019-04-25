#include "file_hdl.h"

using namespace Utils;
using namespace std;

int main(int argc, char const *argv[])
{
    ////////////////////////////// TXT HANDLING /////////////////////////////
    // TODO: CSV and Text can be overloaded, furthermore can be default behaviour
    FileHdlTxt filehdl_txt("Tmp/test_txt.txt");
    filehdl_txt.Write("I'm writing");
    filehdl_txt.Write("I'm writing again");
    filehdl_txt.Read();
    // filehdl.Delete(); // -> Let user decide if want to delete file 

    ////////////////////////////// BIN HANDLING /////////////////////////////
    unsigned char a = 0x41;
    unsigned char a_mem_dump;
    unsigned int b = 0x42000000;
    unsigned int b_mem_dump;
    FileHdlBin filehdl_bin("Tmp/test_bin.data");
    filehdl_bin.Write(&a, sizeof(unsigned char));
    filehdl_bin.Read(&a_mem_dump, sizeof(unsigned char));
    cout << "Memdump a: " << a_mem_dump << endl;
    filehdl_bin.Write(&b, sizeof(unsigned int));
    filehdl_bin.Read(&b_mem_dump, sizeof(unsigned int));
    cout << "Memdump b: " << b_mem_dump << endl;

    ////////////////////////////// CSV HANDLING /////////////////////////////
    std::string header = "ID,Name,Age,e-mail";
    std::string values = "0,Julio Castillo,31,julio.castillo@continental-corporation.com";
    FileHdlCsv filehdl_csv("Tmp/test_csv.csv");
    filehdl_csv.Write(header);
    filehdl_csv.Write(values);
    filehdl_csv.Read();

    return 0;
}

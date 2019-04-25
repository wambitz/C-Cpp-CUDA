#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <vector>

namespace Utils
{
    enum class FileType
    {
        TXT,
        BIN,
        CSV,
    };

    // template <typename T>
    class IFileHdl
    {
    public:
        // IFileHdl(std::string path, std::string filename /*, std::fstream file*/): path(path), filename(filename) /*, file(file) */ {}
        // virtual ~IFileHdl() = 0;;

        virtual void Open()  = 0;
        virtual void Close() = 0;
        virtual void Read()  = 0;  // bool?
        virtual void Write() = 0;  // bool?
        virtual void Delete() = 0; // bool?

    private:
        virtual bool FileExist() = 0;
        virtual bool IsEmtpy() = 0;
        virtual bool IsEOF() = 0;
    };

    // Abstract class
    // template <typename T>
    class AbsFileHdl : public IFileHdl
    {
    public:
        AbsFileHdl(std::string filename /*, FileType type*/);
        virtual ~AbsFileHdl() = default;
        virtual void Open();
        virtual void Close();

        virtual void Read()  = 0 ; // bool?
        virtual void Write() = 0 ; // bool?
        // virtual void Write(T input) = 0 ; // bool?
        virtual void Delete(); // bool?
        
    private:
        bool         _file_exists;  // Flag to know if the database exists. 
        uint64_t     _size;	        // The size of the database file.
        std::fstream _file;
        std::string  _filename;
        FileType     _type;
        // std::ios_base::openmode _mode_in;
        // std::ios_base::openmode _mode_in;
        IFileHdl * _file_hdl;

        virtual bool FileExist();
        virtual bool IsEmtpy();
        virtual bool IsEOF();
    } ; 

    class FileHdlBin : public AbsFileHdl /* <FileType> */
    {
    public:
        FileHdlBin(std::string filename/*, FileType type*/) : AbsFileHdl(filename/*, type*/) {}
        virtual ~FileHdlBin() = default;

        virtual void Read();
        template<typename T> void Read(T* data, uint32_t size)
        {
            std::fstream file;
            file.open("Tmp/test_bin.data");
            file.read(reinterpret_cast<char *>(data), size);
            file.close();
            std::cout << ">>[INFO] BIN file Read() file OK." << std::endl;
        }
        virtual void Write();
        template<typename T> void Write(T* data, uint32_t size)
        {
            std::fstream file;
            file.open("Tmp/test_bin.data", std::ios::app);
            file.write(reinterpret_cast<char *>(data), size);
            file.close();
            std::cout << ">>[INFO] BIN file Write() file OK." << std::endl;
        } 

    private:
        std::vector<std::fstream> files;
        // void SetPath();

    };

    class FileHdlCsv : public AbsFileHdl /* <FileType> */ 
    {
    public:
        FileHdlCsv(std::string filename/*, FileType type*/) : AbsFileHdl(filename/*, type*/) {}
        virtual ~FileHdlCsv() = default;

        // TODO: A vector of variabels can be created and iterated to store values from CSV
        virtual void Read();  // bool?
        virtual void Write(); // bool?
        virtual void Write(std::string input);  // bool?

    private:
        std::vector<std::ofstream> files;
    };

    class FileHdlTxt : public AbsFileHdl /* <std::string> */
    {
    public:
        FileHdlTxt(std::string filename/*, FileType type*/) : AbsFileHdl(filename /*, type*/) {}
        virtual ~FileHdlTxt() = default;

        virtual void Read();  // bool?
        virtual void Write();  // bool?
        virtual void Write(std::string input);  // bool?

    private:
        std::vector<std::fstream> files;
    };

    // class Database : FileHdlBin
    // {
    //     void Read();
    //     void CleanName();
    // };
}


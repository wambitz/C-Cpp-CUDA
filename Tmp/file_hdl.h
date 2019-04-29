#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <vector>

namespace Utils
{
    enum class FileType {TXT, BIN, CSV,};

    // template <typename T>
    class IFileHdl
    {
    public:
        virtual void Create()= 0;
        virtual void Open()  = 0;
        virtual void Close() = 0;
        virtual void Read()  = 0;  // bool?
        virtual void Write() = 0;  // bool?
        virtual void Write(std::string) = 0;  // bool?
        virtual void Delete() = 0; // bool?
        virtual void SetMode(std::ios_base::openmode mode) = 0;

    private:
        virtual bool FileExist() = 0;
        virtual bool IsEmtpy() = 0;
        virtual bool IsEOF() = 0;
    };

    class FileHdl
    {
    public:
        
        FileHdl(FileType type, std::string filename);
        void Read();
        void Write();
        void Write(std::string input);
    private:
        IFileHdl * _file_hdl;
    };

    // Abstract class
    // template <typename T>
    class AbsFileHdl : public IFileHdl
    {
    public:
        AbsFileHdl(std::string filename);
        virtual ~AbsFileHdl() = default;
        virtual void Create();
        virtual void Open();
        virtual void Close();

        virtual void Read()  = 0 ; // bool?
        virtual void Write() = 0 ; // bool?
        // virtual void Write(T input) = 0 ; // bool?
        virtual void Write(std::string) = 0;  // bool?
        virtual void Delete(); // bool?

        std::fstream & GetFile() { return _file; }
        void SetMode(std::ios_base::openmode mode) { _mode =  mode;}
        
    private:
        bool                        _file_exists;  // Flag to know if the database exists. 
        uint64_t                    _size;	        // The size of the database file.
        std::fstream                _file;
        std::string                 _filename;
        std::ios_base::openmode     _mode;
        
        virtual bool FileExist();
        virtual bool IsEmtpy();
        virtual bool IsEOF();
    }; 

    class FileHdlBin : public AbsFileHdl /* <FileType> */
    {
    public:
        FileHdlBin(std::string filename) : AbsFileHdl(filename) {}
        virtual ~FileHdlBin() = default;

        virtual void Read();
        template<typename T> void Read(T* data, uint32_t size)
        {
            Open();
            GetFile().read(reinterpret_cast<char *>(data), size);
            std::cout << ">>[INFO] BIN file Read() file OK." << std::endl;
            Close();
            
        }
        virtual void Write();
        // FIXME: This shouldn't be here
        virtual void Write(std::string input);
        template<typename T> void Write(T* data, uint32_t size)
        {
            Open();
            GetFile().write(reinterpret_cast<char *>(data), size);
            std::cout << ">>[INFO] BIN file Write() file OK." << std::endl;
            Close();
            
        } 

    private:
        std::vector<std::fstream> files;
        // void SetPath();
    };

    class FileHdlCsv : public AbsFileHdl /* <FileType> */ 
    {
    public:
        FileHdlCsv(std::string filename) : AbsFileHdl(filename) {}
        virtual ~FileHdlCsv() = default;

        // TODO: A vector of variabels can be created and iterated to store values from CSV
        virtual void Read();  // bool?
        virtual void Write(); // bool?
        virtual void Write(std::string input);  // bool?

    private:
        std::vector<std::fstream> files;
    };

    class FileHdlTxt : public AbsFileHdl /* <std::string> */
    {
    public:
        FileHdlTxt(std::string filename) : AbsFileHdl(filename) {}
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


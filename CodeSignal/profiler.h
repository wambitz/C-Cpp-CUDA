// Enablers from Outside
// Use the below settings as a Compile Time Definition if you would like to profile.
// #define _PROFILER_FILE_LOG 0

//Private Impl
#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>

// using namespace std;
#ifdef _PROFILER_FILE_LOG
#define _PROFILER_FILE_LOGGER
#else
#undef _PROFILER_FILE_LOGGER
#endif // _LOG_TO_FILE

struct profiler
{
    std::string name;
    std::chrono::high_resolution_clock::time_point p;
    profiler(std::string const &n) :
        name(n), p(std::chrono::high_resolution_clock::now()) { }
    ~profiler()
    {
        using dura = std::chrono::duration<double>;
        auto d = std::chrono::high_resolution_clock::now() - p;
        std::stringstream stream;
        stream<< name << ": "
            << std::chrono::duration_cast<dura>(d).count()
            << std::endl;

        #ifdef _PROFILER_FILE_LOGGER
            std::ofstream logfile;
            logfile.open ("profile_data.log", std::ios::app);
            logfile << stream.str();
            logfile.close();
        #else
            std::cout <<stream.str();
        #endif // _PRO
    }
};

// Profiler Macros
// Use this Macro to add CustomComments
#define PROFILE_FUNCTION_WITHCOMMENTS(comments) profiler _pfinstance(comments)
//By Default this macro will print the function name.
#define PROFILE_FUNCTION profiler _pfinstance(__FUNCTION__)

//Example Usage
/*
int main()
{
 PROFILE_FUNCTION_WITHCOMMENTS("Main Function");
 PROFILE_FUNCTION;
}
*/
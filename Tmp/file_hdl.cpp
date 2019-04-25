#include "file_hdl.h"

using namespace std;

////////////////////////////// ABS HANDLING /////////////////////////////

Utils::AbsFileHdl::AbsFileHdl(std::string filename) : _filename(filename)
{
    Open();
    if (!FileExist())
	{
		cout << ">>[WARN] File: " + _filename + " does not exists." << endl;
	}
    if (IsEmtpy())
    {
        cout << ">>[WARN] File: " + _filename + " is empty" << endl;
    }
    Close();
}

// FIXME: Warning message should be only displayed once in the constructor
void Utils::AbsFileHdl::Open()
{
    // This always truncate file which is expected behavior
    std::ios::open_mode mode = std::ios_base::out /* | std::ios_base::in */; //-> in/out mode does not work for creating files
    try
        {
             /*, std::ios::out | std::ios::binary | std::ios::app*/
            _file.open(_filename, mode);
        }
        catch (std::ofstream::failure error) 
        {
        // TODO: Do this for all messages
        #ifdef LINUX
            m_ig->notify(vig::ImageGenerator::VIGNFL_FATAL,"Exception opening/reading/closing binary DB.");
            std::cerr << error.what() << std::endl;
        #else
            // FIXME: This should be done with the log functtionality
            cout << ">>[WARN] Exception opening: " + _filename << endl;
        #endif
        }
        
        if (_file.is_open())
        {
            // FIXME: Warning messages should be done once in the constructor
            cout << ">>[INFO] File: " + _filename + " sucessfully created" << endl;
            // FIXME: Warning messages should be only displayed once in the constructor
            cout << ">>[INFO] File: " + _filename + " openned succesfully \n";
            _file.seekg(0, _file.end);
            _size = _file.tellg();
            cout << ">>[INFO] Database size = " + std::to_string(_size) + " bytes \n";
            _file.seekg(0, _file.beg);
            _file_exists = true;
            // binary_db_.close();
        }
        else
        {
            cout << ">>[WARN] File: " + _filename + " is not open" << endl;
        }
}

void Utils::AbsFileHdl::Close()
{
    _file.close();
}

void Utils::AbsFileHdl::Delete()
{
    remove(_filename.c_str());
} 

bool Utils::AbsFileHdl::FileExist()
{
    return _file_exists;
}

bool Utils::AbsFileHdl::IsEmtpy()
{
    bool is_empty = true;
	if (0 < _size)
	{
		is_empty = false;
	}
	return is_empty;
}

bool Utils::AbsFileHdl::IsEOF()
{
    bool end_of_file = true;

	if (EOF != _file.peek())
	{
		end_of_file = false;
	}
	return end_of_file;
}
////////////////////////////// BIN HANDLING /////////////////////////////

void Utils::FileHdlBin::Read() 
{

} 

void Utils::FileHdlBin::Write()
{

}  

////////////////////////////// CSV HANDLING /////////////////////////////

void Utils::FileHdlCsv::Read()
{
    string cell;
    // TODO: This should be called from abstract class and mode should be updted to append and in
    fstream file;
    file.open ("Tmp/test_csv.csv");
    // getline(file, cell);
    // TODO: Consider store in variables iterating throug vector or map -> getline(file, it++?, ',')
    while ( getline(file, cell, ',') )
    {
      cout << cell << ", ";
    }
    file.close();
    cout << ">>[INFO] CSV file Read() OK." << endl;

    // std::ifstream config_file;
    // std::string path = "../../../../Develop/IG64/Plugins/HFL_HW/data/sensors_config.csv";
    
    // config_file.open(path.c_str(), std::ios::in);
    // if (!config_file.is_open())
    // {
    //     m_ig->notify(vig::ImageGenerator::VIGNFL_FATAL ,"The file %s could not be find\n",path.c_str());
    // }

    // std::string line;
    // std::getline(config_file, line);
    // while(getline(config_file, line))
    // {
    //     std::stringstream line_strm(line);
    //     std::string cell;
    //     getline(line_strm, cell,',');
    //     std::string sensor_name = cell;
    //     getline(line_strm, cell,',');
    //     SensorType sensor_type = (SensorType)atoi(cell.c_str());
    //     TODO: Split context to store first parameters, then use them in object instantiation
    //     FIXME: Casting can be done internally once parameters are stored or directly in constructor
    //     SensorSimulation_t * HFL = new SensorSimulation_t(sensor_type,sensor_name,line_strm);
    //     m_HFLSensors.push_back(HFL);
    // }
    // config_file.close();
} 

void Utils::FileHdlCsv::Write()
{

}

void Utils::FileHdlCsv::Write(std::string input)
{
    fstream file;
    // TODO: This should be called from abstract class and mode should be updted to append and out
    file.open ("Tmp/test_csv.csv", ios::app);
    file << input << endl ;
    file.close();
    cout << ">>[INFO] CSV file Write() OK." << endl;
}

////////////////////////////// TXT HANDLING /////////////////////////////

void Utils::FileHdlTxt::Read()
{
    string line;
    // TODO: This should be called from abstract class and mode should be updted to append and in
    fstream file;
    file.open ("Tmp/test_txt.txt" );
    while ( getline(file, line) )
    {
      cout << line << '\n';
    }
    file.close();
    cout << ">>[INFO] Text file Read() OK." << endl;
} 

void Utils::FileHdlTxt::Write()
{

}  

void Utils::FileHdlTxt::Write(std::string input)
{
    fstream file;
    // TODO: This should be called from abstract class and mode should be updted to append and out
    file.open ("Tmp/test_txt.txt", ios::app);
    file << input << endl ;
    file.close();
    cout << ">>[INFO] Text file Write() OK." << endl;
}
    
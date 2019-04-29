#include "file_hdl.h"

using namespace std;


////////////////////////////// FILE HANDLING /////////////////////////////
Utils::FileHdl::FileHdl(Utils::FileType type, std::string filename)
{
    if (type == FileType::BIN)
    {
        _file_hdl = new FileHdlBin(filename);
    }
    if (type == FileType::CSV)
    {
        _file_hdl = new FileHdlCsv(filename);
    }
    if (type == FileType::TXT)
    {
        _file_hdl = new FileHdlTxt(filename);
    }

}

void Utils::FileHdl::Read()
{
    _file_hdl->SetMode(ios_base::in);
    _file_hdl->Read();
}

void Utils::FileHdl::Write()
{
    _file_hdl->SetMode(ios_base::out | ios_base::app);
    _file_hdl->Write();
}

void Utils::FileHdl::Write(std::string input)
{
    _file_hdl->SetMode(ios_base::out | ios_base::app);
    _file_hdl->Write(input);
}

////////////////////////////// ABS HANDLING /////////////////////////////

Utils::AbsFileHdl::AbsFileHdl(std::string filename) : _filename(filename),
                                                      _file_exists(false),
                                                      _size(0)
{
    // Open();
    Create();
    if (IsEmtpy())
    {
        cout << ">>[WARN] File: " + _filename + " is empty" << endl;
    }
    // Close();
}

void Utils::AbsFileHdl::Create()
{
    _mode = std::ios_base::out /* | std::ios_base::in */; //-> in/out mode does not work for creating files
    try
    {
        /*, std::ios::out | std::ios::binary | std::ios::app*/
        _file.open(_filename, _mode);
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
        cout << ">>[INFO] File: " + _filename + " sucessfully created" << endl;
        // FIXME: Warning messages should be only displayed once in the constructor
        _file_exists = true;
        Close();
    }
    else
    {
        cout << ">>[WARN] File: " + _filename + " was not created" << endl;
    }
}

// FIXME: Warning message should be only displayed once in the constructor
void Utils::AbsFileHdl::Open()
{
    try
    {
        /*, std::ios::out | std::ios::binary | std::ios::app*/
        _file.open(_filename, _mode);
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

    if (!FileExist())
	{
		cout << ">>[WARN] File: " + _filename + " does not exists." << endl;
	}

    if (_file.is_open())
    {
        cout << ">>[INFO] File: " + _filename + " openned succesfully \n";
        _file.seekg(0, _file.end);
        _size = _file.tellg();
        cout << ">>[INFO] File size = " + std::to_string(_size) + " bytes \n";
        _file.seekg(0, _file.beg);
    }
    else
    {
        cout << ">>[WARN] File: " + _filename + " is not open" << endl;
    }
}

void Utils::AbsFileHdl::Close()
{
    _file.close();
    cout << ">>[INFO] File: " + _filename + " closed"  << endl;
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
    cout << ">>[DEBUG]: Default Bin Read" << endl;
} 

void Utils::FileHdlBin::Write()
{
    cout << ">>[DEBUG]: Default Bin Write" << endl;
}  
//FIXME: This shoudln't be here
void Utils::FileHdlBin::Write(std::string input)
{
    cout << ">>[DEBUG]: Default Bin Write with string param" << endl;
}

////////////////////////////// CSV HANDLING /////////////////////////////

void Utils::FileHdlCsv::Read()
{
    string cell;
    // TODO: This should be called from abstract class and mode should be updted to append and in

    Open();
    // getline(file, cell);
    // TODO: Consider store in variables iterating throug vector or map -> getline(file, it++?, ',')
    while ( getline(GetFile(), cell, ',') )
    {
      cout << cell << ", ";
    }
    cout << ">>[INFO] CSV file Read() OK." << endl;
    Close();
    
} 

void Utils::FileHdlCsv::Write()
{
    cout << ">>[DEBUG]: Default CSV Write" << endl;
}

void Utils::FileHdlCsv::Write(std::string input)
{
    // TODO: This should be called from abstract class and mode should be updted to append and out
    Open();
    GetFile() << input << endl ;
    cout << ">>[INFO] CSV file Write() OK." << endl;
    Close();
    
}

////////////////////////////// TXT HANDLING /////////////////////////////

void Utils::FileHdlTxt::Read()
{
    string line;
    Open();
    while ( getline(GetFile(), line) )
    {
      cout << line << '\n';
    }
    cout << ">>[INFO] Text file Read() OK." << endl;
    Close();
    
} 

void Utils::FileHdlTxt::Write()
{
    cout << ">>[DEBUG]: Default Txt Write" << endl;
}  

void Utils::FileHdlTxt::Write(std::string input)
{
    // TODO: This should be called from abstract class and mode should be updted to append and out
    Open();
    GetFile() << input << endl ;
    cout << ">>[INFO] Text file Write() OK." << endl;
    Close();
}

/*
void Utils::FileHdlCsv::Read()
{
    string cell;
    // TODO: This should be called from abstract class and mode should be updted to append and in

    Open();
    // getline(file, cell);
    // TODO: Consider store in variables iterating throug vector or map -> getline(file, it++?, ',')
    while ( getline(GetFile(), cell, ',') )
    {
      cout << cell << ", ";
    }
    Close();
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
} */
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <functional>
#include <cmath>
#include <chrono>

// using namespace std; 
#define N_SLICES (128u)
#define RAW_DATA_SIZE (32 * 128 * 128)
// Private method to read test pattern
void LoadTestPattern(const std::string filename, std::array<short int, N_SLICES>& testpattern)
{
    // FILE handling
    std::ifstream testpattern_file;
    testpattern_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    // Data
    std::string slice; 
    unsigned short i = 0;

    try 
    {
        testpattern_file.open(filename);
        while (testpattern_file.good())
        {
            std::getline(testpattern_file, slice);
            testpattern[i] = static_cast<short int>(std::stoi(slice));
            i++;
        }
        testpattern_file.close();
    }
    catch (std::ifstream::failure& error)
    {
        std::cerr << "[EXCEPTION]: " << error.what() << std::endl;
    }
}

// unsigned char RandomRotation(std::array<short int, N_SLICES>& ref_test_pattern)
void RandomRotation(std::array<short int, N_SLICES>& ref_test_pattern)
{
    
    // Define random generator with uniform integer distribution
    const int lower_limit = 0;
    const int upper_limit = 127;


    uint64_t seed = std::random_device{}() | std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 eng(seed);                        // seed the generator
    std::uniform_int_distribution<> distr(lower_limit, upper_limit); // define the range
    unsigned char offset = distr(eng);

    // simple rotation to the left
    std::rotate(std::begin(ref_test_pattern), begin(ref_test_pattern) + offset, std::end(ref_test_pattern));
    // return offset;
}

void PixelRotation(std::array<short int, 1>::iterator pixel_array, unsigned char offset)
{
    // simple rotation to the right
    std::rotate(pixel_array, pixel_array+N_SLICES - offset, pixel_array+N_SLICES);
}

// template<std::size_t SIZE>
// void AddGaussianNoiseToArcPixels(std::array<short int, SIZE>& pixel_array, const std::array<short int, N_SLICES>& reference_pixel)
void AddGaussianNoiseToArcPixels(std::array<short int, 1>::iterator pixel_array, const std::array<short int, N_SLICES>& reference_pixel)
{
    // Define random generator with Gaussian distribution
    const float mean    {0.0};
    const float stddev  {2.0};

    // auto distr = std::bind(std::normal_distribution<float>{mean, stddev},
    //                        std::mt19937(std::random_device{}()));

    uint64_t seed = std::random_device{}() | std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 eng(seed);                              // seed the generator
    std::normal_distribution<float> distr(mean, stddev); // define the range
    // unsigned char offset = distr(eng);

    for (const auto& slice : reference_pixel) 
    {
        // pixel_array[(&slice-&reference_pixel[0])+(N_SLICES*0)] = rint(slice+distr(eng));
        // pixel_array[(&slice-&reference_pixel[0])+(N_SLICES*1)] = rint(slice+distr(eng));
        // pixel_array[(&slice-&reference_pixel[0])+(N_SLICES*2)] = rint(slice+distr(eng));
        // pixel_array[(&slice-&reference_pixel[0])+(N_SLICES*3)] = rint(slice+distr(eng));
        *(pixel_array+(N_SLICES*0)) = rint(slice+distr(eng));
        *(pixel_array+(N_SLICES*1)) = rint(slice+distr(eng));
        *(pixel_array+(N_SLICES*2)) = rint(slice+distr(eng));
        *(pixel_array+(N_SLICES*3)) = rint(slice+distr(eng));
        pixel_array++;
    }
}

// test function
void WriteToStandardPixel(short int * pixel_array)
{
    // FILE handling
    std::ifstream stdpixel_file;
    stdpixel_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    // Data
    std::string slice; 
    unsigned short i = 0;

    try 
    {
        stdpixel_file.open("Tmp/StdPixel1.csv");
        while (stdpixel_file.good())
        {
            std::getline(stdpixel_file, slice);
            pixel_array[i] = static_cast<short int>(std::stoi(slice));
            i++;
        }
        stdpixel_file.close();
    }
    catch (std::ifstream::failure& error)
    {
        std::cerr << "[EXCEPTION]: " << error.what() << std::endl;
    }
}

std::array<short int, 1>::iterator FindMinElementInPixel(std::array<short int, 1>::iterator pixel_array)
{
    return std::min_element(pixel_array, pixel_array+N_SLICES);
}

std::array<short int, 1>::iterator FindMaxElementInPixel(std::array<short int, 1>::iterator pixel_array)
{
    return std::max_element(pixel_array, pixel_array+N_SLICES);
}

unsigned char GetOffset(std::array<short int, 1>::iterator pixel_array, std::array<short int, 1>::iterator it)
{
    return std::distance(pixel_array, it);
}


int main(int argc, char const *argv[])
{
    // Data cube
    // unsinged int data_cube[DATA_CUBE_SIZE];
    std::array<short int, RAW_DATA_SIZE> raw_data{0};
    std::array<short int, N_SLICES> test_pattern{0};
    std::string filename = "Tmp/ArcPixelTestPattern.csv";
    
    // arc pixels from special pixels
    std::array<short int, N_SLICES> arc_pixel1{0};
    std::array<short int, N_SLICES> arc_pixel2{0};
    std::array<short int, N_SLICES> arc_pixel3{0};
    std::array<short int, N_SLICES> arc_pixel4{0};

    std::array<short int, N_SLICES*4> arc_pixels;
    

    // Find min values for each arc_pixel 
    // array of iterators
    std::array<std::array<short int, 1>::iterator, 4> peaks{0};
    std::array<short int, 4>		                  offset{0};
    // unsigned char offset = 0;
        
    LoadTestPattern(filename, test_pattern);
    WriteToStandardPixel(raw_data.data());

    // unsigned short offset = RandomRotation(test_pattern);
    RandomRotation(test_pattern);
   
    AddGaussianNoiseToArcPixels(std::begin(arc_pixels), test_pattern);

    for (auto const& i : {0, 1, 2, 3} )
    {
        peaks[i] = FindMinElementInPixel(std::begin(arc_pixels)+(N_SLICES*i));
        std::cout << "Minumum value in arc_pixel["<< i<< "]: " << *peaks[i] << std::endl;
        // std::cout << "Index of arc_pixel[" << i << "]: " << 
    }

    for (auto const& i : {0, 1, 2, 3} )
    {
        // peaks[i] = FindMinElementInPixel(arc_pixels.data()+(N_SLICES*i));
        offset[i] = GetOffset(std::begin(arc_pixels) + (i * N_SLICES), peaks[i]);
        std::cout << "Offset in arc_pixel["<< i<< "]: " << offset[i] << std::endl;
        // std::cout << "Index of arc_pixel[" << i << "]: " << 
    }

    // offset and rotation for S1 only
    // offset = GetOffset(arc_pixels, peaks[0]);
    // std:: cout << "Shift offset: " << static_cast<unsigned short int>(offset) << std::endl;
    PixelRotation(std::begin(raw_data), offset[0]);
        
    //  Write array elements to file for testing porpuses     
    for (unsigned int i = 0; i < N_SLICES; i++)
    {
        arc_pixel1[i] = arc_pixels[i+(N_SLICES*0)];
        arc_pixel2[i] = arc_pixels[i+(N_SLICES*1)];
        arc_pixel3[i] = arc_pixels[i+(N_SLICES*2)];
        arc_pixel4[i] = arc_pixels[i+(N_SLICES*3)];
    }

    // Arcpixels wiht noise Write vector elements to file for testing porpuses
    std::ofstream output_file[4];

    for (int i : {0, 1, 2, 3})
    { 
        output_file[i].open ("Tmp/arc_pixel" + std::to_string(i+1) + ".csv");
    }

    for (unsigned int j = 0; j < static_cast<unsigned int>(test_pattern.size()); j++)
    {
        output_file[0] << arc_pixel1[j] << std::endl;
        output_file[1] << arc_pixel2[j] << std::endl;
        output_file[2] << arc_pixel3[j] << std::endl;
        output_file[3] << arc_pixel4[j] << std::endl;
    }

    for (int i : {0, 1, 2, 3})
    { 
        output_file[i].close();
    }

    // Shifted Std pixels Write array elements to file for testing porpuses
    std::ofstream stdpixels_output_file;
    stdpixels_output_file.open ("Tmp/stdpixel1_shifted.csv");
    
    for (unsigned int j = 0; j < N_SLICES; j++)
    {
        stdpixels_output_file << raw_data[j] << std::endl;
    }

    return 0;
}

// template<std::size_t SIZE>
// short int FindMinElementInPixel(std::array<short int, SIZE>* pixel_array)
// {
//     return *(std::min_element(pixel_array, pixel_array+N_SLICES));
// }

// short int FindMinElementInPixel(std::vector<short int>::iterator iter)
// {
//     return *(std::min_element(iter, iter+N_SLICES));
// }

// short int FindMinElementInPixel(const std::array<short int, N_SLICES>& pixel_array)
// {
//     return *(std::min_element(std::begin(pixel_array), std::begin(pixel_array)+N_SLICES));
// }

// Define random generator with Gaussian distribution
// std::random_device rd;                         // obtain a random number from hardware
// std::mt19937 eng(rd());                        // seed the generator
// std::uniform_int_distribution<> distr(0, 127); // define the range

// for (unsigned char i = 0; i < N_SLICES; i++) 
// {
//     pixel_array[i] = distr(eng);
// }

// float GetGaussianNoise()
// {
//     // Define random generator with Gaussian distribution
//     const float mean   = 0.0;
//     const float stddev = 2.0;
//     auto dist = std::bind(std::normal_distribution<float>{mean, stddev},
//                           std::mt19937(std::random_device{}()));

//     return dist();
// }

// std::default_random_engine generator;
// std::normal_distribution<float> distribution(mean, stddev);

// Define random generator with Gaussian distribution
// const float mean   = 0.0;
// const float stddev = 2.0;
// auto dist = std::bind(std::normal_distribution<float>{mean, stddev},
//                       std::mt19937(std::random_device{}()));

// for (const auto& slice : test_pattern) 
// {
//     arc_pixel1[&slice-&test_pattern[0]] = rint(slice+GetGaussianNoise());
//     arc_pixel2[&slice-&test_pattern[0]] = rint(slice+GetGaussianNoise());
//     arc_pixel3[&slice-&test_pattern[0]] = rint(slice+GetGaussianNoise());
//     arc_pixel4[&slice-&test_pattern[0]] = rint(slice+GetGaussianNoise());
// }

// Set peak boundaries
// bool is_lower_set = false;
// for (const auto& slice : test_pattern)
// {
//      if (slice >= -1 && slice <= 2)
//      {
//          lower_boundarie = slice;
//          is_lower_set = true;
//      }
//      if ((is_lower_set) && (slice >= -10 && slice <= 0))
//      {
//          upper_boundarie = slice
//      }
// }

// round shift
// unsigned int lower_boundarie = 0;
// unsigned int upper_boundarie = 0;
// bool flag_lower_boundarie = false;
// bool flag_upper_boundarie = false;

// for (const auto& slice : test_pattern)
// {
//     if(slice )
// }
// rand() for left shift have to be lower than lower boundarie index 
// rand() for right shift have to be loweer upper boundarie
// if rand() is +pos shift right if rand() is -neg shift left
// shift_val = abs(rand())
// test_pattern << rand()*16; 
// Mantain upper and lower boundaries when shifting
// constraint shift betweeen slice 0 to 128

// AddGaussianNoiseToPixel(arc_pixel1, test_pattern);
// AddGaussianNoiseToPixel(arc_pixel2, test_pattern);
// AddGaussianNoiseToPixel(arc_pixel3, test_pattern);
// AddGaussianNoiseToPixel(arc_pixel4, test_pattern);

// for (const auto& slice : test_pattern) 
// {
//     arc_pixel1[&slice-&test_pattern[0]] = rint(slice+dist());
//     arc_pixel2[&slice-&test_pattern[0]] = rint(slice+dist());
//     arc_pixel3[&slice-&test_pattern[0]] = rint(slice+dist());
//     arc_pixel4[&slice-&test_pattern[0]] = rint(slice+dist());
// }



// std::ofstream standard_pixels_file;
// standard_pixels_file.open("Tmp/StdPixel1.csv");
// for (unsigned int j = 0; j < N_SLICES; j++)
// {
//     standard_pixels_file << raw_data[j] << std::endl;
// }
// standard_pixels_file.close();



// peaks[0] = FindMinElementInPixel(arc_pixel1.data());
// peaks[1] = FindMinElementInPixel(arc_pixel2.data());
// peaks[2] = FindMinElementInPixel(arc_pixel3.data());
// peaks[3] = FindMinElementInPixel(arc_pixel4.data());

// // Print min value    
// for (auto i : {0, 1, 2, 3} )
// {
//     std::cout << "Minumum value in arc_pixel["<< i<< "]: " << peaks[i] << std::endl;
// }

// This can be done in one for loop and in wrapped in one function
// Print min value    

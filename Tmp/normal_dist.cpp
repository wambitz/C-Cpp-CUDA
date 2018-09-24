// #include <iostream>
// #include <iterator>
// #include <random>

// int main()
// {
//     std::random_device rd; // obtain a random number from hardware
//     std::mt19937 eng(rd()); // seed the generator
//     std::uniform_int_distribution<> distr(25, 63); // define the range

//     for(int n=0; n<40; ++n)
//         std::cout << distr(eng) << ' '; // generate numbers
// }

// int main() {
//     // Example data
//     std::vector<double> data1 = {1., 2., 3., 4., 5., 6.};
//     std::vector<double> data2 = {1., 2., 3., 4., 5., 6.};

//     // Define random generator with Gaussian distribution
//     const double mean = 0.0;
//     const double stddev = 0.1;
//     std::default_random_engine generator;
//     std::normal_distribution<double> dist(mean, stddev);

//     // Add Gaussian noise
//     for (auto& x : data1) {
//         x = x + dist(generator);
//     }

//     for (auto& x : data2) {
//         x = x + dist(generator);
//     }

//     // Output the result, for demonstration purposes
//     std::copy(begin(data1), end(data1), std::ostream_iterator<double>(std::cout, " "));
//     std::cout << "\n";

//     std::copy(begin(data2), end(data2), std::ostream_iterator<double>(std::cout, " "));
//     std::cout << "\n";

//     return 0;
// }

// **********************************************************************************
// normal_distribution
#include <iostream>
#include <string>
#include <random>

int main()
{
  const int nrolls=10;  // number of experiments
  const int nstars=10;    // maximum number of stars to distribute

  std::default_random_engine generator;
  std::normal_distribution<double> distribution(5.0,2.0);

  int p[10]={};

  for (int i=0; i<nrolls; ++i) {
    double number = distribution(generator);
    if ((number>=0.0)&&(number<10.0)) ++p[int(number)];
    // std::cout << number << std::endl ;
  }

  std::cout << "normal_distribution (5.0,2.0):" << std::endl;

  for (int i=0; i<128; ++i) {
    std::cout << i << "-" << (i+1) << ": ";
    std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
  }

  return 0;
}

// **********************************************************************************
// #include <iostream>
// #include <iomanip>
// #include <string>
// #include <map>
// #include <random>

// int main()
// {
//     std::random_device rd;

//     std::mt19937 e2(rd());

//     std::normal_distribution<> dist(70, 10);

//     std::map<int, int> hist;
//     for (int n = 0; n < 100000; ++n) {
//         ++hist[std::round(dist(e2))];
//     }

//     for (auto p : hist) {
//         std::cout << std::fixed << std::setprecision(1) << std::setw(2)
//                   << p.first << ' ' << std::string(p.second/200, '*') << '\n';
//     }
// }
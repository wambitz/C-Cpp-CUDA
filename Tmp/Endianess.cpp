#include <iostream>
#include <array>

int main() {
    // constexpr const int N = 4;
    // std::array<int, 6> arr{ 0, 1, 2, 3, 4, 5 };
    // for (std::array<int, 1>::iterator it = std::begin(arr); it != std::begin(arr) + N && it != std::end(arr); ++it)
    //     std::cout << *it << std::endl;
    int num = 1;

    if (*(char *)&num == 1)
    {
        printf("Little-Endian\n");
    }
    else
    {
        printf("Big-Endian\n");
    }
}
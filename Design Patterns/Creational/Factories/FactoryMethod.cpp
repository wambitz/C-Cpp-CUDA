#include <cmath>
#include <iostream>

enum class PointType
{
    cartesian,
    polar
};

class Point
{
private:
    Point(const float x, const float y) : x{x}, y{y}
    {
    }

public:
    float x, y;

    static Point NewCartesian(const float x, const float y)
    {
        return {x, y};
    }

    static Point NewPolar(const float r, const float theta)
    {
        return {r * cos(theta), r * sin(theta)};
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& obj)
    {
        return os << "x: " << obj.x << " y: " << obj.y;
    }

};

int main(int argc, char const *argv[])
{
    // Point p{1, 2}; // -> Compiler error

    auto c = Point::NewCartesian(1, 2);
    std::cout << c << std::endl;

    auto p = Point::NewPolar(5, M_PI_4);
    std::cout << p << std::endl;

    // getchar();
    return 0;
}

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

    friend std::ostream& operator<<(std::ostream& os, const Point& obj)
    {
        return os << "x: " << obj.x << " y: " << obj.y;
    }

    friend class PointFactory;
};

class PointFactory
{
public:
    static Point NewCartesian(const float x, const float y)
    {
        return {x, y};
    }

    static Point NewPolar(const float r, const float theta)
    {
        return {r * cos(theta), r * sin(theta)};
    }

};

int main(int argc, char const *argv[])
{
    // Point p{1, 2}; // -> Compiler error

    auto c = PointFactory::NewCartesian(1, 2);
    std::cout << c << std::endl;

    auto p = PointFactory::NewPolar(5, M_PI_4);
    std::cout << p << std::endl;

    // getchar();
    return 0;
}

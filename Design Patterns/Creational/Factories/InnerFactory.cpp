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

    class PointFactory;

public:
    float x, y;

    friend std::ostream& operator<<(std::ostream& os, const Point& obj)
    {
        return os << "x: " << obj.x << " y: " << obj.y;
    }

    static PointFactory Factory;
};

class Point::PointFactory
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

    auto c = Point::Factory.NewCartesian(1, 2);
    std::cout << c << std::endl;

    auto p = Point::Factory.NewPolar(2, 3);
    std::cout << p << std::endl;

    // getchar();
    return 0;
}

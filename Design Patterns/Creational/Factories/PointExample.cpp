#include <cmath>
#include <iostream>

enum class PointType
{
    cartesian,
    polar
};

class Point
{
public:
    float x, y;

    // What if we want more types, then maybe we can try overload anotehr constructor but that casuses
    // compiler errors, then we can use enums like the examxple below
    // Point(const float x, const float y):
    //     x{x},
    //     y{y}
    // {

    // }

    Point(const float a, const float b, PointType type = PointType::cartesian)
    {
        if (type == PointType::cartesian)
        {
            x = a;
            y = b;
        }
        else
        {
            x = a * cos(b);
            y = a * sin(b);
        }
    }
};
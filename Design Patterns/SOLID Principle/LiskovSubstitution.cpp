#include <iostream>

using namespace std;

class Rectangle 
{
protected:
    
    int width, height;

public:

    Rectangle (int width, int height) : width(width), height(height) {}

    int getWidth()  const { return width;  }
    int getHeight() const { return height; }

    virtual void setWidth(int witdth)  { Rectangle::width  = width;  }
    virtual void setHeight(int height) { Rectangle::height = height; }

    int area() const { return width * height; }
};

class Square : public Rectangle
{
public:
    Square(int size): Rectangle(size, size) {}

    void setWidth(int width) override 
    {
        this->width = this->height = width;
    }

    void setHeight(int height) override 
    {
        this->width = this->height = height;
    }
};

void process (Rectangle& r)
{
    int w = r.getWidth();

    r.setHeight(10);

    cout << "Expected area = "   << (w*10)
         << ", got " << r.area() << endl;
}

// posible solution
struct RectangleFactory
{
    static Rectangle create_rectangle(int w, int h);
    static Rectangle create_square(int size);
};

int main(int argc, char const *argv[])
{
    Rectangle r{3, 4};
    process(r);

    Square sq{5};
    process(sq);

    return 0;
}

#include <iostream>
// #include "ring_buffer.h"

using namespace std;

template <typename T>
class ring 
{
public:
    // Attributes
    class iterator;

    // Methods
    ring(int size) : _pos(0), _size(size), _values(nullptr)
    {
        _values = new T[size];
    }

    ~ring()
    {
        delete [] _values;
    }

    void add(T value)
    {
        _values[_pos++] = value;
        
        if (_pos == _size)
        {
            _pos = 0;
        }
    }

    int size() { return _size; }

    iterator begin() { return iterator(0, *this); }

    iterator end() { return iterator(_size, *this); }

    T & get(int pos) { return _values[pos]; } 
    
private:
    //  Attributes
    int _pos;
    int _size;
    T * _values;
};

template <typename T>
class ring<T>::iterator
{
public:
    iterator(int pos, ring &r): _pos(pos), _ring(r)
    {   

    }

    iterator & operator ++ (int)
    {
        _pos++;
        return *this;
    }

    iterator & operator ++ ()
    {
        _pos++;
        return *this;
    }

    T & operator * ()
    {
        return _ring.get(_pos);
    }

    bool operator != (const iterator & it) const
    {
        return _pos != it._pos;
    }

private:
    int _pos;
    ring & _ring;
};

int main(int argc, char const *argv[])
{
    ring<string> textstring(3);
    
    textstring.add("one");
    textstring.add("two");
    textstring.add("three");
    textstring.add("four");
    
    for (int i = 0; i < textstring.size(); i++)
    {
        cout << textstring.get(i) << endl;
    }
    cout << endl;

    // C++ 98
    for (ring<string>::iterator it = textstring.begin(); it != textstring.end(); it++)
    {
        cout << *it << endl;
    }
    cout << endl;

    // C++ 11
    for (string value: textstring)
    {
        cout << value << endl;
    }

    return 0;
}

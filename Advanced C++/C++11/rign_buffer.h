#pragma once

#include <iostream>

template <typename T>
class Ring 
{
public:
    // Attributes
    class Iterator;

    // Methods
    Ring(int size) : _pos(0), _size(size), _values(nullptr)
    {
        _values = new T[size];
    }

    ~Ring()
    {
        delete [] _values;
    }

    int size() { return _size; }

    void add(T value)
    {
        _values[_pos++] = value;
        
        if (_pos == _size)
        {
            _pos = 0;
        }
    }

    T & get(int pos) { return _values[pos]; } 
    
private:
    //  Attributes
    int _pos;
    int _size;
    T * _values;
};

template <typename T>
class Ring<T>::Iterator
{
public:
    void print()
    {
        std::cout << "Hello from iterator: " << T() << std::endl;
    }
};
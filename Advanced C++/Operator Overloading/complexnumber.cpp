#ifndef COMPLX_H_
#define COMPLX_H_

#include <iostream>
using namespace std;

namespace ComplexNumbers
{
    class Complex 
    {
    private:

        double _real;
        double _imaginary;

    public:

        Complex()=default;
        Complex(double real, double imaginary): _real(real), _imaginary(imaginary) {}
        Complex(const Complex &complex)
        {
            cout << "Copy constructor" << endl;
            this->_real = complex._real;
            this->_imaginary = complex._imaginary;
        }

        const Complex &operator = (const Complex &complex) 
        {
            cout << "Assignment overloading" << endl;

            this->_real = complex._real;
            this->_imaginary = complex._imaginary;
            return *this;
        }


        double getReal() const {return _real; }
        double getImaginary() const {return _imaginary; }
    };

    ostream &operator << (ostream &out, const Complex &complex) 
    {
        out << "(" << complex.getReal() << "," << complex.getImaginary() << ")";
        return out;
    }
}

#endif /* COMPLEX_H_ */

// ComplexNumbers::Complex::Complex
using namespace ComplexNumbers;

int main(int argc, char const *argv[])
{
    
    Complex c1(2, 3);
    Complex c2 = c1;
    Complex c3 = c2;

    cout << c2 << ": " << c3 << endl;
    return 0;
}

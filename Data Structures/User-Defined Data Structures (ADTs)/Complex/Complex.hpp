#pragma once
#include <iostream>
#include <cmath>
#include <complex>
#include <limits>

using namespace std;
template <typename T>
class Complex
{
    T real, imag;
    static_assert(std::numeric_limits<T>::is_specialized, "Type T must be numeric");
    // static_assert is in older versions of C++ that doesn't allow std::string to be as a template for this Complex class
public:
    Complex(T r = 0, T i = 0)
    {
        real = r;
        imag = i;
    }
    void set_real(T r)
    {
        real = r;
    }

    void set_imaginary(T i)
    {
        imag = i;
    }

    T get_real() const
    {
        return real;
    }

    T get_imag() const
    {
        return imag;
    }

    Complex<T> operator+(const Complex<T> &o1)
    {
        return Complex(this->real + o1.real, this->imag + o1.imag);
    }

    Complex<T> operator-(const Complex<T> &o1)
    {
        return Complex(this->real - o1.real, this->imag - o1.imag);
    }

    Complex<T> operator*(const Complex<T> &o1)
    {
        return Complex((this->real * o1.real) - (this->imag * o1.imag), (this->real * o1.imag) + (this->imag * o1.real));
    }

    Complex<T> operator/(const Complex<T> &o1)
    {
        double den = (o1.real * o1.real) + (o1.imag * o1.imag);
        if (den == 0)
        {
            return Complex(0, 0);
            // Division by Zero Case
        }
        return Complex(((this->real * o1.real) + (this->imag * o1.imag)) / den, ((this->imag * o1.real) - (this->real * o1.imag)) / den);
    }

    void display() const
    {
        cout << *this;
    }

    friend ostream &operator<<(ostream &out, const Complex<T> &o)
    {
        if (o.real == 0 && o.imag == 0)
        {
            return out << "0";
        }
        if (o.real != 0)
        {
            out << o.real;
        }

        if (o.imag != 0)
        {
            if (o.real != 0 && o.imag > 0)
            {
                out << "+";
            }

            // To Handle cases like 'i' or '-i' instead of '1i' or '-1i'
            if (o.imag == 1)
            {
                out << "i";
            }
            else if (o.imag == -1)
            {
                out << "-i";
            }
            else
            {
                out << o.imag << "i";
            }
        }

        return out;
    }

    bool operator==(const Complex<T> &o) const
    {
        // Don't use direct equality
        // It might fail if you are adding two complex nos and then checking it with a previous one
        // Because C++ stores the double as Binary base-2 so they are not stored exactly like they are , some precision is left
        // Like 0.1 + 0.2 = Very Close to 0.3 but not 0.3.
        // For such cases , we find distance between two numbers and check if they are smaller
        // even than the 1e-9 = 0.000000001
        // We check that : Is the gap between these numbers smaller than a billionth?
        // If the gap is that tiny, we assume any difference is just a "rounding ghost" created by the CPU's binary math and treat them as equal

        if (abs(real - o.real) < 1e-9 && abs(imag - o.imag) < 1e-9)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    bool operator!=(const Complex<T> &o) const
    {
        return !(*this == o);
    }

    // No need for copy constructor and copy assignment operator for this

    // In += , -= , *= , = operators overloading ,
    // we can do code reusability in these from  +,*,/,- doing temporary copies
    // But this slows down performance as this creates a temporary object as well
    // We can just write these compound assignment operators in the same way as arithmetic ones leaving code reusability over speed
    // Or we can first define the compound assignment operators and then reuse them in arithmetic ones

    // Here arithmetic ones have been reused as compound assignment , making code a little slow for very large objects
    Complex<T> &operator+=(const Complex<T> &o)
    {
        *this = *this + o;
        return *this;
    }

    Complex<T> &operator-=(const Complex<T> &o)
    {
        *this = *this - o;
        return *this;
    }

    Complex<T> &operator*=(const Complex<T> &o)
    {
        *this = *this * o;
        return *this;
    }

    Complex<T> &operator/=(const Complex<T> &o)
    {
        *this = *this / o;
        return *this;
    }

    double magnitude() const
    {
        return sqrt(real * real + imag * imag);
        // We can also use here hypot function for big values incase (in cmath)
        // return hypot(real , imag) , this is used to calculate hypotenuse
    }

    void conjugate_inplace()
    {
        if (imag != 0)
        {
            imag = -imag;
        }
    }

    Complex<T> conjugate() const
    {
        return Complex(real, -imag);
    }

    double argument() const
    {
        return atan2(imag, real);
    }

    // This function is static just to make a Complex number without having to call from a Complex Number
    // E.g : Complex z = Complex::from_polar(10 , 20)   //A complex number with magniute 10 and argument 20

    // Otherwise we would have to do : Complex z ; Complex z = z.from_polar(10 , 20); which feels awkward here

    static Complex<T> from_polar(double r, double theta)
    {
        return Complex(r * cos(theta), r * sin(theta)); // z = rCos(theta) + irSin(theta)
    }

    static Complex<T>** sortbyMagnitude(Complex<T> **arr, int SIZE)
    {
        Complex<T> **temp = arr;
        for (int i = 0; i < SIZE - 1; i++)
        {
            int minIdx = i;
            for (int j = i + 1; j < SIZE; j++)
            {
                // Compare magnitudes directly using the pointer
                if (temp[j]->magnitude() < temp[minIdx]->magnitude())
                {
                    minIdx = j;
                }
            }
            // Swap the pointers directly in the array
            Complex<T> *temp1 = temp[i];
            temp[i] = temp[minIdx];
            temp[minIdx] = temp1;
        }
            return temp;
    }
};

// Complex number we handled above has three forms :
// 1) z = a + bi
// 2) Coordinates Form (a,b) , similar to first one
// 3) z = rCos(theta) + irSin(theta)

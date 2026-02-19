#pragma once
#include <iostream>
#include <initializer_list>
#include <limits>
#include <windows.h>
using namespace std;

template <typename T>
class Polynomial
{
    T *coefficients;  // Data Inside a Vector
    int CAPACITY = 1; // Total allocated size like a Vector
    int degree;       // Current Size like a Vector
    static_assert(std::numeric_limits<T>::is_specialized, "Type T must be numeric");

public:
    Polynomial(int deg = 0)
    {
        if (deg < 0)
        {
            throw runtime_error("Degree cannot be Negative\n");
        }
        else if (deg == 0)
        {
            degree = 0;
            // CAPACITY = 1;
        }
        else // deg > 0
        {
            CAPACITY = deg + 1;
            degree = deg;
        }

        coefficients = new T[CAPACITY];
        for (int i = 0; i < CAPACITY; i++)
        {
            coefficients[i] = 0;
        }

        if (deg > 0)
        {
            coefficients[degree] = 1;
        }
    }

    // We used initializer_list to be able to give items like 1,2,3 like that
    // We can also use dynamic array but for that we need to make one in the main() first
    // and then pass it as arguments here with size also.
    Polynomial(initializer_list<T> list)
    {
        degree = list.size() - 1;
        CAPACITY = list.size();

        coefficients = new T[CAPACITY];

        int i = 0;

        for (const T &item : list)
        {
            coefficients[i++] = item;
        }
    }

    Polynomial(const Polynomial<T> &p)
    {
        this->degree = p.degree;
        this->CAPACITY = p.CAPACITY;

        this->coefficients = new T[this->CAPACITY];
        for (int i = 0; i < this->CAPACITY; i++)
        {
            this->coefficients[i] = p.coefficients[i];
        }
    }

    Polynomial<T> &operator=(const Polynomial<T> &p)
    {
        if (this != &p)
        {
            delete[] this->coefficients;

            this->degree = p.degree;
            this->CAPACITY = p.CAPACITY;

            this->coefficients = new T[this->CAPACITY];
            for (int i = 0; i < this->CAPACITY; i++)
            {
                this->coefficients[i] = p.coefficients[i];
            }
        }
        return (*this);
    }

    void set_coefficient(int ind, T val) // Like [] operator without const
    {
        if (ind < 0 || ind > degree)
        {
            throw out_of_range("Out of Range (Not Possible)\n");
        }
        coefficients[ind] = val;
    }

    T get_coefficient(int ind) const // Like [] operator with const
    {
        if (ind < 0 || ind > degree)
        {
            throw out_of_range("Out of Range (Not Possible)\n");
        }
        return coefficients[ind];
    }

    T &operator[](int ind)  // Like get but non-const
    {
        if (ind < 0 || ind > degree)
        {
            throw out_of_range("Out of Range (Not Possible)\n");
        }
        return coefficients[ind];
    }

    const T &operator[](int ind) const // Like get but const
    {
        if (ind < 0 || ind > degree)
        {
            throw out_of_range("Out of Range (Not Possible)\n");
        }
        return coefficients[ind];
    }

    void add_new_term(T val) // Like Push_Back
    {
        if ((degree + 1) >= CAPACITY)
        {
            CAPACITY *= 2;
            T *temp = new T[CAPACITY];
            for (int i = 0; i <= degree; i++)
            {
                temp[i] = coefficients[i];
            }
            delete[] coefficients;
            coefficients = temp;
        }
        coefficients[degree++] = val;
    }

    void remove_last_term() // Like Pop_Back
    {
        if (degree < 0)
        {
            throw out_of_range("No Term to Remove\n");
        }
        coefficients[degree] = 0;
        degree--;
    }

    void remove_any_term(int ind) // Index is actually degree
    {
        if (degree < 0)
        {
            throw out_of_range("No Term to Remove\n");
        }
        coefficients[ind] = 0;
        degree--;
    }

    void display()
    {
        cout << *this;
    }

    // Helper function to convert power to superscript string
    static string toSuperscript(int n)
    {
        if (n == 0)
        {
            return "⁰";
        }
        if (n == 1)
        {
            return ""; // We don't write X¹
        }
        string res = "";
        string normal = to_string(n);
        string supers[] = {"⁰", "¹", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "⁹"};

        for (char c : normal)
        {
            res += supers[c - '0'];
        }
        return res;
    }
    // For displaying a polynomial , we handle :
    // 1) Value there or not
    // 2) First Value or Second
    // 3) Sign (Positive / Negative Value)
    // 4) Number itself
    // 5) Power of X

    friend ostream &operator<<(ostream &out, const Polynomial<T> &p)
    {
        bool isFirst = true;

        for (int i = p.degree; i >= 0; i--)
        {
            T val = p.coefficients[i];

            if (val == 0)
            {
                continue; // Value there or not
            }

            // First Value or not and Sign handling
            if (!isFirst && val > 0)
            {
                out << " + ";
            }
            else if (!isFirst && val < 0)
            {
                out << " ";
            }

            // Number Itself
            // Hiding 1 / -1 logic
            if (val == 1 && i > 0)
            {
            }
            else if (val == -1 && i > 0)
            {
                out << "-";
            }
            else
            {
                out << val;
            }

            // Superscript Logic : X^2 , X , Const
            if (i > 0)
            {
                out << "x";
                if (i > 1)
                {
                    out << Polynomial::toSuperscript(i);
                }
            }
            isFirst = false;
        }

        if (isFirst) // Empty Polynomial
        {
            out << "0";
        }
        return out;
    }

    bool operator==(const Polynomial<T> &p)
    {
        if (degree != p.degree)
        {
            return 0;
        }
        for (int i = 0; i < degree; i++)
        {
            if (coefficients[i] != p.coefficients[i])
            {
                return 0;
            }
        }
        return 1;
    }

    bool isEmpty() const
    {
        int deg = degree;
        while (deg > 0 && coefficients[deg] == 0)
        {
            deg--;
        }
        if (deg == 0)
        {
            return 1;
        }
        return 0;
    }

    Polynomial<T> operator+(const Polynomial<T> &p)
    {
        int max_deg = degree;

        if (max_deg < p.degree)
        {
            max_deg = p.degree;
        }
        Polynomial<T> temp(max_deg);

        for (int i = 0; i <= temp.degree; i++)
        {
            int sum = 0;

            if (i <= degree)
            {
                sum += coefficients[i];
            }

            if (i <= p.degree)
            {
                sum += p.coefficients[i];
            }

            temp.coefficients[i] = sum;
        }
        return temp;
    }

    Polynomial<T> operator-(const Polynomial<T> &p)
    {
        Polynomial<T> temp;
        int max_deg = degree;
        if (max_deg < p.degree)
        {
            max_deg = p.degree;
        }
        for (int i = 0; i <= max_deg; i++)
        {
            T diff = 0;

            if (i <= degree)
            {
                diff += coefficients[i];
            }

            if (i <= p.degree)
            {
                diff -= p.coefficients[i];
            }

            if (diff != 0)
            {
                temp.add_new_term(diff);
            }
            else
            {
                temp.add_new_term(0);
            }
        }
        return temp;
    }

    Polynomial<T> operator*(const Polynomial<T> &p)
    {
        if (p.isEmpty())
        {
            return Polynomial(0);
        }
        int deg = degree + p.degree;

        Polynomial<T> temp(deg);
        temp.coefficients[degree + p.degree] = 0;

        for (int i = 0; i <= degree; i++)
        {
            for (int j = 0; j <= p.degree; j++)
            {
                temp.coefficients[i + j] += coefficients[i] * p.coefficients[j];
            }
        }
        return temp;
    }

    Polynomial<T> Derivative() const
    {
        if (degree == 0)
        {
            return Polynomial<T>(0); // Derivative of a constant is 0
        }

        Polynomial<T> temp(degree - 1);

        for (int i = 1; i <= degree; i++)
        {
            temp.coefficients[i - 1] = coefficients[i] * i;
        }
        return temp;
    }

    // Division is Possible only if the Degree(Dividend) >= Degree(Divisor)
    // LONG DIVISION METHOD
    Polynomial<T> operator/(const Polynomial<T> &p)
    {
        if (degree < p.degree)
        {
            return Polynomial<T>(0);
        }

        // We can also check p.isEmpty()
        // Keep copy of the two polynomials so that original ones are not changed
        // We do : remainder / p = q ;

        int q_deg = degree - p.degree;
        Polynomial<T> q(q_deg); // The Resulting Polynomial
        q.coefficients[q_deg] = 0;

        Polynomial<T> remainder = *this;

        // Divide leading coefficients and subtracting from the remainder (LONG DIVISION)
        for (int i = q_deg; i >= 0; i--)
        {
            // Dividing the current leading coefficients
            T factor = remainder.coefficients[i + p.degree] / p.coefficients[p.degree];

            q.coefficients[i] = factor;

            for (int j = 0; j <= p.degree; j++)
            {
                remainder.coefficients[i + j] -= factor * p.coefficients[j];
            }
        }

        return q;
    }

    // To Solve a Polynomial , we put x and solve it to get the answer at x
    // Horner's Method (unlike usual putting , we choose efficient way that even saves us finding powers )
    T solve(T x) const
    {
        if (isEmpty())
            return T(0);

        T result = coefficients[degree];

        // Work backwards from the second-to-last coefficient
        for (int i = degree - 1; i >= 0; i--)
        {
            result = result * x + coefficients[i];
        }

        return result;
    }

    Polynomial<T> compose(const Polynomial<T> &q) const
    {
        if (isEmpty())
        {
            return Polynomial<T>(0);
        }

        // Initial value is the coefficient of the highest power
        // Almost same formulas as Horner's : result = result * Q then + coefficients[i]
        Polynomial<T> result;
        result.set_coefficient(0, coefficients[degree]);

        for (int i = degree - 1; i >= 0; i--)
        {
            result = result * q;                       
            result.coefficients[0] += coefficients[i]; 
        }
        return result;
    }

    T operator()(T x) const
    {
        return solve(x);
    }

    Polynomial<T> operator()(const Polynomial<T>& q) const 
    { 
        return compose(q); 
    }

    T highdegree()
    {
        if(degree == 0 && coefficients[0] == 0)
        {
            return 0;
        }
        return degree;
    }

    ~Polynomial()
    {
        delete[] coefficients;
    }
};

/*
int main()
{
    SetConsoleOutputCP(65001); // Set terminal to UTF-8
    try
    {
        // --- Test 1: Integer Polynomials ---
        cout << "--- Integer Polynomial Test ---" << endl;
        // (x + 1) * (x + 1) = x² + 2x + 1
        Polynomial<int> p1 = {1, 1}; // x + 1
        Polynomial<int> p2 = {1, 1}; // x + 1

        Polynomial<int> p3 = p1 * p2;
        cout << "P1: " << p1 << endl;
        cout << "P1 * P2 = " << p3 << endl;

        // --- Test 2: Double Polynomials (Decimals) ---
        cout << "\n--- Double Polynomial Test ---" << endl;
        // 0.5x² + 2.5
        Polynomial<double> pDouble = {2.5, 0.0, 0.5};
        cout << "P_double: " << pDouble << endl;

        // --- Test 3: Derivative ---
        // (x² + 2x + 1)' = 2x + 2
        cout << "\n--- Derivative Test ---" << endl;
        Polynomial<int> pDeriv = p3.Derivative();
        cout << "(" << p3 << ")' = " << pDeriv << endl;

        // --- Test 4: Division ---
        // (x² + 2x + 1) / (x + 1) = x + 1
        cout << "\n--- Division Test ---" << endl;
        Polynomial<int> q = p3 / p1;
        cout << "(" << p3 << ") / (" << p1 << ") = " << q << endl;

        // --- Test 5: Edge Case (Empty/Zero) ---
        cout << "\n--- Edge Case Test ---" << endl;
        Polynomial<int> zero;
        cout << "Default Polynomial: " << zero << endl;
        cout << "Is empty? " << (zero.isEmpty() ? "Yes" : "No") << endl;
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
*/
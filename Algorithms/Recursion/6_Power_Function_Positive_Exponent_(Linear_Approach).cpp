#include <iostream>

using namespace std;

// Will calculate only int exponents
// You may use long double with all variables for higher precision and large numbers

// Base Case : When exponent becomes 0.
// Pow(2,0) = 1
// Pow(2,1) = 2 * Pow(2,0) = 2 * 1 = 2
// Pow(2,2) = 2 * Pow(2,1) = 2 * 2 = 4
// Pow(2,3) = 2 * Pow(2,2) = 2 * 4 = 8
// Pow(2,4) = 2 * Pow(2,3) = 2 * 8 = 16
// Pow(2,5) = 2 * Pow(2,4) = 2 * 16 = 32

// Pow(2,-5) = (1 / Pow(2,-5)) = 1 / 32
// Pow(2,5) = 2 * Pow(2,4) = 2 * 16 = 32
// Pow(2,4) = 2 * Pow(2,3) = 2 * 8 = 16
// Pow(2,3) = 2 * Pow(2,2) = 2 * 4 = 8
// Pow(2,2) = 2 * Pow(2,1) = 2 * 2 = 4
// Pow(2,1) = 2 * Pow(2,0) = 2 * 1 = 2
// Pow(2,0) = 1
// Top-Down
double power(int a, int b)
{
    if (b == 0)
    {
        return 1;
    }
    else if (b > 0) // Positive Exponents
    {
        int rec = a * power(a, b - 1);
        return rec;
    }
    else // Negative Exponents , can be in decimal so choose double for them
    {
        double rec = (1.0 / power(a, -b));
        return rec;
    }
}

int main()
{
    // You may keep the number as float , but int exponent always
    int a, b;
    cout << "Enter the number : ";
    cin >> a;
    cout << "Enter the power : ";
    cin >> b;
    cout << a << " raised to the power " << b << " is : " << (power(a, b)) << endl;

    return 0;
}

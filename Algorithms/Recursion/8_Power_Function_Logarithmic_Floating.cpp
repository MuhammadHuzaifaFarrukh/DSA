#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Time : O(logb) , Space : O(logb)
double myPow(double a, int b)
{
    long long N = b;

    if (N < 0)
    {
        a = 1 / a;
        N = -N;
    }
    // This handles negative exponents because a^(-b) = 1/(a^b)
    // If any exponent is negative , it is converted into positive here and we take base as its reciprocal.

    return helper(a, N);
}

// Recursive Function that runs in logartihmic time.
double helper(double a, long long b)
{
    if (b == 0)
    {
        return 1;
    }
    if (b == 1)
    {
        return a;
    }

    double x = helper(a, b / 2);

    if (b % 2 == 0)
    {
        return x * x;
    }
    else
    {
        return x * x * a;
    }
}

int main()
{
    double a = 2.1, b = 1;
    cout << " Answer : " << myPow(a, b) << endl;
    return 0;
}
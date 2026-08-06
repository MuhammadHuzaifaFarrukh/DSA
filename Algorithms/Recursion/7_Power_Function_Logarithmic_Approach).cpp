#include <iostream>

using namespace std;

// This is called as Binary Exponentiation
/*
How Binary Exponentiation Works
Normally, calculating a raised to power b takes b minus 1 multiplications (a multiplied by a multiplied by a...).
That takes O(b) linear time.
Binary exponentiation speeds this up by halving the exponent b at every step:
If b is even: a raised to b = (a raised to b/2) squared
If b is odd: a raised to b = (a raised to b/2) squared, multiplied by a

Because we calculate x = a raised to b/2 only once, we do just 1 multiplication (x times x) or 2 multiplications (x times x times a) per recursive call, skipping half the exponent every single time!
*/

// The initution comes when we try to multiply e.g : 7^6 = 7*7*7*7*7*7 (6 times ).
// So if we divide this into 2 parts , we have 7*7*7 * 7*7*7 = 7^3 * 7^3 (Dividing power 6 by 2).
// Now if we divide it further taking 7^3 = 7*7*7 = 7*7 * 7 = 7^2 * 7^1 (Dividing power 3 by 2).
// Now if we divide it further taking 7^2 =  7*7 = 7^1 * 7^1 = (Dividing power 2 by 1).
// We can see that our base case comes down when power reaches 1.
// So when our power reaches 1 , we just return the same value.
// One more thing , when our power is in even number we can just multiply the same answers i.e if we have found 7^3 , we don't need to find it again , we just multiply it by same 7^3 * 7^3 where n = 6 (Even).
// However if power is odd number say 5 , then we break it into 2*2*1 that means we find answer of power 2 and multiply it with 2 again and then with 1 to make it upto 5.

// E.g : Power (7,6)
// Calls Power (7,3)
// Calls Power (7,1)
// (7,1) gives 7 so we get this (7,3) x = 7.
// Now for (7,3) 3 is odd so power is odd so we have to do x*x*a meaning (7*7) * 7 = 7^2 * 7 = 7^3.
// Now we've got this answer for (7,6) x = 7^3.
// Now for (7,6) , 6 is even , power  is even , so we just do x*x = 7^3 * 7^3 = 7^6.

// Total stacks of the recursive tree is the number of divisions by 2 until 'b' becomes 1.
// So we can say it as log of b base 2.
// Time : O(logb)

// Since the maximum depth of the recursion tree is the number of divisions by 2, the call stack reaches a height of log2(b).
// Space : O(logb)
int power(int a, int b)
{
    if (b == 0)
    {
        return 1;
    }
    if (b == 1)
    {
        return a;
    }
    int x = power(a, b / 2);
    if (b % 2 == 0)
    {
        return x * x;
    }
    else
    {
        return x * x * a;
    }
}

/*
A recurrence relation expresses the time T(b) taken for power b in terms of T(b/2):
T(b) = T(b / 2) + O(1)
T(b / 2): We make one single recursive call with half the exponent.

O(1): Checking even or odd, doing x times x or x times x times a, and returning takes constant time.
Base Case: T(0) = O(1) or T(1) = O(1).
*/

int main()
{
    // Here exponent must be int , base can be float as well
    int a, b;
    cout << "Enter the number : ";
    cin >> a;
    cout << "Enter the power : ";
    cin >> b;
    if (b >= 0)
    {
        cout << a << " raised to the power " << b << " is : " << (power(a, b)) << endl;
    }
    else // Handle Negative int Exponents
    {
        cout << a << " raised to the power " << b << " is : " << 1.0 / (power(a, b)) << endl;
    }

    return 0;
}

// Here is its iterative solution :
// Time : O(log b) and Space : O(1)
long long iterativePower(long long a, long long b)
{
    long long res = 1;
    long long base = a;

    while (b > 0)
    {
        // If the exponent is odd, multiply the result by the current base
        if (b % 2 == 1)
        {
            res = res * base;
        }
        // Square the base for the next power of 2
        base = base * base;
        // Divide the exponent by 2
        b /= 2;
    }
    return res;
}
// If any question asks to perform power() but taking modulo of some number like 10^9+7 usually then just add (% mod) in 2 lines
// res = (res*base) % modulo
// base = (base*base) % modulo where modulo is 10^9+7 or any large number
// This is usually done to keep the answer in limits.
#include <iostream>
#include <string>

using namespace std;

// Base Case : Power of any number raised to 0 is 1.
// Pow(2,0) = 1
// Pow(2,1) = 2 * Pow(2,0) = 2 * 1 = 2
// Pow(2,2) = 2 * Pow(2,1) = 2 * 2 = 4
// Pow(2,3) = 2 * Pow(2,2) = 2 * 4 = 8
// Pow(2,4) = 2 * Pow(2,3) = 2 * 8 = 16
// Pow(2,5) = 2 * Pow(2,4) = 2 * 16 = 32

// Time : O(n+1) = O(n) , Space : O(n+1) = O(n)
// This one is actually efficient because now we don't take the extra argument. (Top-Down)
int pow(int base, int exp)
{
    if (exp == 0)
    {
        return 1;
    }
    return base * pow(base, exp - 1);
}

int main()
{
    int n;
    cout << "Enter n : ";
    cin >> n;
    cout << "Answer : " << pow(2, n) << endl;
    return 0;
}
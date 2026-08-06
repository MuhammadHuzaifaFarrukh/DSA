#include <iostream>

using namespace std;

// Bottom-Up :
// Base Case : When i becomes greater than n.
// Sum(1,5) = 1 + Sum(2,5) = 1 + 14 = 15
// Sum(2,5) = 1 + Sum(3,5) = 2 + 12 = 14
// Sum(3,5) = 1 + Sum(4,5) = 3 + 9 = 12
// Sum(4,5) = 4 + Sum(5,5) = 4 + 5 = 9
// Sum(5,5) = 5 + Sum(6,5) = 5 + 0 = 5
// Sum(6,5) = 0

// Time : O(n+1) = O(n) , Space : O(n+1) = O(n)
int sum(int i, int n)
{
    if (i > n)
    {
        return 0;
    }
    return i + sum(i + 1, n);
}

// Top-Down :
// Base Case : Sum(1) = 1
// Sum(5) = 5 + Sum(4) = 5 + 10 = 15
// Sum(4) = 4 + Sum(3) = 4 + 6 = 10
// Sum(3) = 3 + Sum(2) = 3 + 3 = 6
// Sum(2) = 2 + Sum(1) = 2 + 1 = 3
// Sum(1) = 1
// Sum(n) = n + Sum(n-1)
// More Efficient Approach

// Time : O(n+1) = O(n) , Space : O(n+1) = O(n)
int sum2(int n)
{
    if (n == 1)
    {
        return 1;
    }
    return n + sum2(n - 1);
}

int main()
{
    int n;
    cout << "Enter n : ";
    cin >> n;
    cout << " Sum : " << sum(1, n) << endl;
    return 0;
}
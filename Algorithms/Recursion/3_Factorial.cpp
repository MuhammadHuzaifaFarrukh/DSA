#include <iostream>
#include <vector>

using namespace std;

// Factorial of a number 'n' :
// n! = n*(n-1)*(n-2)*(n-3)*(n-4)...3*2*1.
// 0! and 1! = 1

// Bottom-Up:
// Base Case : When i becomes greater than n.
// Fact(1,5) = 1 * Fact(2,5) = 1 * 120 = 120
// Fact(2,5) = 1 * Fact(3,5) = 2 * 60 = 120
// Fact(3,5) = 1 * Fact(4,5) = 3 * 20 = 60
// Fact(4,5) = 4 * Fact(5,5) = 4 * 5 = 20
// Fact(5,5) = 5 * Fact(6,5) = 5 * 1 = 5
// Fact(6,5) = 1

// Time : O(n+1) = O(n) , Space : O(n+1) = O(n)
long long factorial(long long i, long long n)
{
    if (i > n)
    {
        return 1;
    }

    return i * factorial(i + 1, n);
}

// Top-Down :
// Base Case : 0 or 1 ! = 1
// Fact(5) = 5 * Fact(4) = 5 * 24 = 120
// Fact(4) = 4 * Fact(3) = 4 * 6 = 24
// Fact(3) = 3 * Fact(2) = 3 * 2 = 6
// Fact(2) = 2 * Fact(1) = 2 * 1 = 2
// Fact(1) = 1 * Fact(0) = 1 * 1 = 1
// Fact(0) = 1
// Fact(n) = n * Fact(n-1)

// Time : O(n+1) = O(n) , Space : O(n+1) = O(n)
// This one is actually efficient because now we don't take the extra argument.
long long factorial2(long long n)
{
    if (n == 0)
    {
        return 1;
    }
    return n * factorial2(n - 1);
}

// Another Approach (Using either reference / global variable while returning any calculation value) :
// However this may be avoided because it breaks the concept of recursion and should be done only when recursion is unable to give answer.
// This breaks the concept of divide and conquer and just makes it as iterative version.
// We will also have to reset it each time used , because it is not a copied variable.

// Time : O(n-1) = O(n) , Space : O(n-1) = O(n)
/*
void factorial3(long long n, long long &ans)
{
    if (n <= 1)
    {
        return;
    }
    ans *= n;
    factorial3(n - 1, ans);
}
*/

int main()
{
    int n;
    cout << "Enter n : ";
    cin >> n;
    long long result = factorial(1, n);
    cout << "Result : " << result << endl;

    // long long int ans = 1 ;
    // factorial3(n,ans);
    // cout << "Ans : "<<ans<<endl;
    return 0;
}
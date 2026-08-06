#include <iostream>

using namespace std;

// Base Case : Natural Number N >= 1
// squareSum(1) = 1
// squareSum(2) = (2*2) + squareSum(1) = 4 + 1 = 5
// squareSum(3) = (3*3) + squareSum(2) = 9 + 5 = 14
// squareSum(4) = (4*4) + squareSum(3) = 16 + 14 = 30

// Time : O(n+1) = O(n) , Space : O(n+1) = O(n)
// This one is actually efficient because now we don't take the extra argument (Bottom-Up)
int squareSum(int n)
{
    if (n == 1)
    {
        return 1;
    }
    return (n * n) + squareSum(n - 1);
}

int main()
{
    int n;
    cout << "Enter n : ";
    cin >> n;
    cout << "Answer : " << squareSum(n) << endl;
    return 0;
}
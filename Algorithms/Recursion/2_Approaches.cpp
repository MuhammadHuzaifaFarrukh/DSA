#include <iostream>
#include <vector>

using namespace std;

// Recursion has 2 approaches :
// We solve problem into sub-problems and solve for only 1 , which handles the rest of the cases also.
// We need to print numbers from 1 to 'n'.
// For printing  1 to 5 numbers we divide printing 5 into -> 1,2,3,4,5
// So we take by printing 1 and this will handle the other cases also.
// These are Top-Bottom and Bottom-Up (not to be mixed with approaches of DP , Purely Recursion).

// 1) Bottom-Up :
// We print 1 , and then we print the next until num > n.
// Our Base Case is when number becomes greater than the 'n'.
// We went from 1 ------- 5 , where our base case was at 5.

// Mathematically :
// Print(6) = Return
// Print(5) = 5 + Print(6)
// Print(4) = 4 + Print(5)
// Print(3) = 3 + Print(4)
// Print(2) = 2 + Print(3)
// Print(1) = 1 + Print(2)
// Print(n) = n + Print(n+1)

// Time : O(n+1) = O(n) and Space : O(n+1) = O(n)
void print(int num, int n)
{
    if (num > n)
    {
        return;
    }
    cout << num << endl;
    print(num + 1, n);
}

// 2) Top-Down :
// Now we say that we print 5 , but before doing that , we print all numbers before 5.
// Then we print 4 , but before doing that , we print all numbers before 4.
// Then we print 3 , but before doing that , we print all numbers before 3.
// Then we print 2 , but before doing that , we print all numbers before 2.
// Then we print 1 , but before doing that , we print all numbers before 1.
// Our Base Case is when 'n' reaches 1.
// We went from 1 ------- 5 , where our base case is now at 1.

// Mathematically :
// Print(0) = Return
// Print(1) = Print(0) + 1
// Print(2) = Print(1) + 2
// Print(3) = Print(2) + 3
// Print(4) = Print(3) + 4
// Print(5) = Print(4) + 5
// Print(n) = Print(n-1) + n

// Time : O(n+1) = O(n) and Space : O(n+1) = O(n)
// This one is actually efficient because now we don't take the extra argument.
void print2(int n)
{
    if (n < 1)
    {
        return;
    }
    print2(n - 1);
    cout << n << endl;
}

int main()
{
    int n;
    cout << "Enter n : ";
    cin >> n;
    // print(1, n);
    // print2(n);

    return 0;
}
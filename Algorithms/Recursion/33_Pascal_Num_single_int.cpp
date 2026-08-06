#include <iostream>
using namespace std;

// Pascal Identity :
// Pascal's triangle is directly equal to combinations nCr.
// The value at row n and columnr (using 0-based indexing) represents:
// Value (n,r)= nCr = n! / (r!(n-r)!)
// This measures the number of ways to choose r items from a set of n items where order does NOT matter.

// For Example for n=4,r=3
// Row 0:           1
// Row 1:         1   1
// Row 2:       1   2   1
// Row 3:     1   3   3   1
// Row 4:   1   4   6   4   1
//          ^   ^   ^   ^   ^
// Col:     0   1   2   3   4

// 4C3 : Means that ways of choosing 3 out of 4 items.
// Row 0:   1
// Row 1:   1   1
// Row 2:   1   2   1
// Row 3:   1   3   3   1
// Row 4:   1   4   6   4   1
//          ^   ^   ^   ^   ^
// Col:     0   1   2   3   4

// 1) Pascal's Identity :
// nCr = (n-1)C(r-1) + (n-1)Cr
// (n-1)C(r-1) denotes the count of combinations if we include the current item.
// (n-1)Cr denotes the count of combinations if we exclude the current item.
// nCr is symmetric i.e 4C3 = 4C1 = 4 , 4C0 = 4C4 = 1
// Sum of all nCr = nC0 + nC1 + ... + nCn = 2^n = All Possible Subsets (Subsequences)

// Time Complexity :
/*
Each non-base call splits into 2 recursive sub-problems: helper(row - 1, col - 1) and helper(row - 1, col).
This creates a binary recursion tree of height r (the row number):
Level 0 (Root): 1 call (helper(r, c))
Level 1: 2 calls
Level 2: 4 calls
...
Level r: up to 2^r base-case calls
Because it re-computes overlapping subproblems repeatedly without saving (memoizing) results, the total number of function calls grows exponentially.
Time : O(2^r)
// However the exact time complexity is : O(nCr) because of our pruning conditions.
*/

// Space Complexity :
/*
The space complexity is determined entirely by the Auxiliary Call Stack Space used by recursion.
Explicit Data Structures: O(1) i.e no vectors, arrays, or extra memory are allocated.
Call Stack Depth: The maximum depth of the active recursion stack corresponds to descending row-by-row from row = r down to row = 0.
At any given moment, there are at most r+1 stack frames stored in memory.
*/
int pascalNumber(int row, int col) // n = row , r = col
{
    if (col < 0 || col > row)
    {
        return 0;
    }
    if (col == 0 || row == col) // row = 0 is fulfilled already
    {
        return 1;
    }

    return pascalNumber(row - 1, col - 1) + pascalNumber(row - 1, col);
}

int main()
{
    int r = 4;
    int c = 3;

    int result = pascalNumber(r, c);

    cout << "Value at row " << r << ", col " << c << " is: " << result << endl;

    return 0;
}

// 2) The Iterative Version :
// We can compute Pascal Number nCr , quickly iteratively.
// If the 'r' == 0 or if r == 'n' then it is always 1.
// We know that nCr is symmetric meaning 5C2 is the same as 5C3 or 5C1 is the same as 5C4.
// So if this difference n-r is larger than 'r'  , then it means that we are at right end of the symmetry and we go to the left end for decreasing our iterative cycles.
// Now comes the main part :

// nCr = n!/r!(n-r)! = n*(n-1)*(n-2)*...*(n-r+1)*(n-r)*(n-r-1)*...*1 / r!(n-r)!
// We have broken the n! into this long series and we can see that (n-r)! is common so they are cancelled out.
// If we have 'n' numbers and we take out 'n-r' then we are left with 'r' numbers.
// So we get nCr = n*(n-1)*(n-2)*...*(n-r+1) / 1*2*3*...*r.
// We have total 'r' terms in the numerator and r terms in the denominator since we cancelled out n-r terms in the numerator and denominator.
// So we can see that :
// nCr = (n-0)*(n-1)*(n-2)*...*(n-r+1) / 1*2*3*...*r.
// OR nCr = (n-i) / (1+i) where i goes from 0 to (r-1).

// Time : O(r) , Space : O(1) Extra space
/*
long long nCr(int n, int r)
{
    if (r < 0 || r > n)
    {
        return 0;
    }
    if (r == 0 || r == n)
    {
        return 1;
    }

    // Symmetry optimization: choose the smaller r to minimize loop steps
    if (r > n - r)
    {
        r = n - r;
    }

    long long ans = 1;

    // Perform multiplication and division step-by-step
    for (int i = 0; i < r; ++i)
    {
        ans = ans * (n - i);
        ans = ans / (i + 1);
    }

    return ans;
}
*/

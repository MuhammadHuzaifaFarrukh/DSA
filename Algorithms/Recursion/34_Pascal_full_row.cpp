#include <iostream>
#include <vector>
using namespace std;

// Pascal Identity :
// Pascal's triangle is directly equal to combinations nCr.
// The value at row n and columnr (using 0-based indexing) represents:
// Value (n,r)= nCr = n! / (r!(n-r)!)
// This measures the number of ways to choose r items from a set of n items where order does NOT matter.

// 4C3 : Means that ways of choosing 3 out of 4 items.
// Row 0:   1
// Row 1:   1   1
// Row 2:   1   2   1
// Row 3:   1   3   3   1
// Row 4:   1   4   6   4   1
//          ^   ^   ^   ^   ^
// Col:     0   1   2   3   4

// Pascal's Identity :
// nCr = (n-1)C(r-1) + (n-1)Cr
// (n-1)C(r-1) denotes the count of combinations if we include the current item.
// (n-1)Cr denotes the count of combinations if we exclude the current item.
// nCr is symmetric i.e 4C3 = 4C1 = 4 , 4C0 = 4C4 = 1
// Sum of all nCr = nC0 + nC1 + ... + nCn = 2^n = All Possible Subsets (Subsequences)

// Time Complexity :
// Here we are finding the complete row of nCr
// So if we take Sum of all nCr , this equals 2^n.
// Time : O(2^n)

// Space Complexity :
// The Call Space can get r+1 for any number and when r=n , it becomes n+1.
// So for the last number it is O(n+1) = O(n)
// Space : O(n)
// To store the answer , vector is of space O(n+1).
// Total Space : O(n+1)+O(n+1) = O(n)

int pascalNumber(int row, int col) // n = row , r = col
{
    if (row == 0 || col == 0 || row == col)
    {
        return 1;
    }
    return pascalNumber(row - 1, col - 1) + pascalNumber(row - 1, col);
}

vector<int> pascalRow(int rowind)
{
    vector<int> nums;
    int row = rowind;
    for (int col = 0; col <= rowind; col++)
    {
        nums.push_back(pascalNumber(row, col));
    }
    return nums;
}

int main()
{
    vector<int> res = pascalRow(4);

    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
    return 0;
}

// 2) Using the Iterative Version (ans * (n-i)/(1+i)) where we derive single nCr , we call the same function n+1 times.
// In this Time becomes : O(n^2).
// Space : O(1) or O(n+1) ~ O(n)

// 3) Another mathematical relation :
// The Mathematical Relation Between Consecutive Elements
// Look at two consecutive elements in row n:

// Element k = C(n, k) = n! / (k! * (n - k)!)
// Element (k - 1) = C(n, k - 1) = n! / ((k - 1)! * (n - k + 1)!)
// Dividing C(n, k) by C(n, k - 1) gives:
// C(n, k) / C(n, k - 1) = (n - k + 1) / k
// Next Element / Previous Element (k-1)  = (n - k + 1)/k
// This gives us the recurrence relation to compute the next element from the current element in O(1) time:
// Element k = Element (k - 1) * (n - k + 1) / k

// Time : O(n) , Space : O(n) due to answer space.
/*
vector<long long> getPascalRow(int n)
{
    vector<long long> ans;
    ans.reserve(n + 1); // Pre-allocate memory to avoid reallocation overhead

    long long current = 1;
    ans.push_back(current); // First element is always 1 (nC0)

    for (int i = 1; i <= n; ++k)
    {
        // Compute next element using: current = current * (n - k + 1) / k
        current = current * (n - i + 1) / i;
        ans.push_back(current);
    }

    return row;
}
*/
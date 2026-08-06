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

// 1) Recursive Way :
// Finding nCr for a single number using recursion O(nCr) and then for full row -> O(2^n) , then for all n rows.
// So it takes time : 2^0 + 2^1 + 2^2 +...+ 2^n = 2^(n+1) - 1 = O(2^n)
// While finding the last row , the recursive stack goes upto r+1 where r = n so n+1 and answer space is (n+1)(n+2)/2.
// Time : O(2^n)
// Space : O(n) due to recursive stack or storing temp rows (or total space : O(n^2) )
/*
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

vector<vector<int>> pascalAllRows(int rows)
{
    vector<vector<int>> ans;
    for(int i = 0 ; i<=rows ; i++)
    {
        vector<int> temp = pascalRow(i);
        ans.push_back(temp);
    }
    return ans;
}
*/

// 2) Using the iterative one by formula : ans*(n-i)/(i+1)
// Time : O(n^3)
// Space : O(n) for storing temp rows (or total space : O(n^2))
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

vector<int> pascalRow(int rowind)
{
    vector<int> nums;
    int row = rowind;
    for (int col = 0; col <= rowind; col++)
    {
        nums.push_back(nCr(row, col));
    }
    return nums;
}

vector<vector<int>> pascalAllRows(int rows)
{
    vector<vector<int>> ans;
    for(int i = 0 ; i<=rows ; i++)
    {
        vector<int> temp = pascalRow(i);
        ans.push_back(temp);
    }
    return ans;
}
*/

// 3) By using the relation between each row elements using formula element = element * (n-k+1)/k:
// Time : O(n^2)
// Space : O(n) for storing temp row (or total space : O(n^2) due to answer).
/*
vector<long long> getPascalRow(int n)
{
    vector<long long> ans;
    ans.reserve(n + 1); // Pre-allocate memory to avoid reallocation overhead

    long long current = 1;
    ans.push_back(current); // First element is always 1 (nC0)

    for (int k = 1; k <= n; ++k)
    {
        // Compute next element using: current = current * (n - k + 1) / k
        current = current * (n - k + 1) / k;
        ans.push_back(current);
    }

    return row;
}

vector<vector<int>> pascalAllRows(int rows)
{
    vector<vector<int>> ans;
    for(int i = 0 ; i<=rows ; i++)
    {
        vector<int> temp = getPascalRow(i);
        ans.push_back(temp);
    }
    return ans;
}
*/

// 4) DP
// Time : O(n^2)
// Extra Space : O(n) used for row vector.
// Total Space : O(n^2)
/*
vector<vector<int>> pascalAllRowsDP(int numRows)
{
    vector<vector<int>> ans;

    for (int i = 0; i <= numRows; i++)
    {
        // Allocate current row of size (i + 1) filled with 1s
        vector<int> row(i + 1, 1);

        // Fill inner elements using previous row's results
        for (int j = 1; j < i; j++)
        {
            row[j] = ans[i - 1][j - 1] + ans[i - 1][j]; // O(1) DP transition
        }

        ans.push_back(row);
    }

    return ans;
}
*/
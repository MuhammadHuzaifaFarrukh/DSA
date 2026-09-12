#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
Given an integer n, return the number of distinct solutions to the n-queens puzzle.
Input: n = 4
Output: 2
*/
// This is permutation without reptition with some extra constraints.

// 1) We can solve this by using our same N-Queens method and just returning ans.size() or by using an ans variable and then just updating it when we reach the base case.
// This would take Time O(n!) (or O(n!*n^2) if we are storing and then counting the time taken in push_back() of 1D vector into 2D)
// and Space : O(S*n^2) where S<=n! or O(n^2) if we remove the answer 2D vector.

// 2) Same Method but now we use the ans variable for storing counts and no temp vector this time.
// Time : O(n!) , Space : O(n)

// Forward Declaration :
int helper(int rows, int n, vector<bool> &cols, vector<bool> &leftDig, vector<bool> &rightDig);
int totalNQueens(int n)
{
    int ans = 0;
    // We use the column vector so that we know to put the queen at that column or not in O(1)
    // We also use the right left Diagonals so that we can find answer in O(1)
    vector<bool> cols(n, 0);
    vector<bool> rightDig(2 * n - 1, 0);
    vector<bool> leftDig(2 * n - 1, 0);

    ans = helper(0, n, cols, leftDig, rightDig);
    return ans;
}

int helper(int rows, int n, vector<bool> &cols, vector<bool> &leftDig, vector<bool> &rightDig)
{
    if (rows == n)
    {
        return 1;
    }

    int ans = 0;
    for (int j = 0; j < n; j++)
    {
        if (cols[j] == 0 && rightDig[j + rows] == 0 && leftDig[(n - 1) + j - rows] == 0)
        {
            cols[j] = 1;
            rightDig[j + rows] = 1;
            leftDig[(n - 1) + j - rows] = 1;

            ans += helper(rows + 1, n, cols, leftDig, rightDig);
            cols[j] = 0;
            rightDig[j + rows] = 0;
            leftDig[(n - 1) + j - rows] = 0;
        }
    }
    return ans;
}

int main()
{
    int n;
    cout << "Enter n (1-9) : ";
    cin >> n;
    cout << "Total Distinct N-Queens Solution for " << n << " Queens : " << totalNQueens(n) << endl;
    return 0;
}
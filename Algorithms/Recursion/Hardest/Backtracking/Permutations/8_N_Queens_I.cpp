#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other (horizontally , vertically , diagonally).
Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.
Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.
Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above
*/
// This is like permutation without repetition with some constraints.

// Forward Declarations :
void helper(int rows, int n, vector<vector<string>> &ans, vector<string> &temp, vector<bool> &cols);
bool diagonals(vector<string> &temp, int i, int j, int n);

// 1) We know that we can place the first queen in any of the 'n' positions.
// Now for the next position , we cannot select the position that is right below it but we can select some positions below to its right or left.
// So that leaves us n-1 choices and so on until we are left with little choices.
// We now use a helper that will be our recursive function.
// We also use a column vector so that we don't need to check the whole column in n time and we can instantly get our answer in O(1) making the space our O(n).
// Now we run a loop from 0 to n for each but we use an if-condition check so that recursive call is done for only few.
// If the column[j] == 0 it means the queen can be placed there and if there is no queen in diagonals , then we can place the queen only for these.
// For row , we are always sending (rows+1) so that if we found a valid position , the queen is placed in the new row.
// For diagonals checking we've made a function that checks diagonals in O(n) time (we only check diagonals upper not down because we haven't placed the value down at that time).
// If we are able to place all the Queens it means rows will be 'n' and this is our base case.
// If somehow we are not able to place all the Queens then we will never reach the base case due to our column vector and diagonals function.

// Time Complexity :
// In the for loop of recursion we make a choice out of 'n'.
// Then for those 'n' , we can have 'n-1' choices as no two queens can be placed in the same column.
// Thus we have n*(n-1)*(n-2)...3*2*1 = n! (Approx)
// Total Time : O(n!) (but if we don't neglect push_back() time , it would be O(n^2*n!)

// Space Complexity :
// Maximum Recursive depth that can go is n = O(n)
// The temp vector is n^2 size.
// So space : O(n^2)
// If we let total valid boards as 'S' , then ans vector total space : S*n^2.
// Total Space (including ans) : O(S*n^2) or O(n!*n^2) because S grows extremely fast relative to 'n' making it S <= n!
vector<vector<string>> solveNQueens(int n)
{
    vector<vector<string>> ans;             // Answer to store all vector of strings
    vector<string> temp(n, string(n, '.')); // One Temp Board

    // We can fill the temp board like this as well if we just wrote vector<string> temp(n) :
    /*
    for(int i = 0 ; i<n ; i++)
    {
        for(int j = 0 ; j<n ; j++)
        {
            temp[i].push_back('.');
        }
    }
    // O(n^2) time for this
    */

    // We use the column vector so that we know to put the queen at that column or not in O(1)
    vector<bool> cols(n, 0);
    helper(0, n, ans, temp, cols);
    return ans;
}
void helper(int rows, int n, vector<vector<string>> &ans, vector<string> &temp, vector<bool> &cols)
{
    if (rows == n)
    {
        ans.push_back(temp);
        return;
    }

    for (int j = 0; j < n; j++)
    {
        if (cols[j] == 0 && diagonals(temp, rows, j, n))
        {
            cols[j] = 1;
            temp[rows][j] = 'Q';
            helper(rows + 1, n, ans, temp, cols);
            temp[rows][j] = '.';
            cols[j] = 0;
        }
    }
}

bool diagonals(vector<string> &temp, int i, int j, int n)
{
    int rows = i, cols = j;
    // Left Diagonal :
    while (rows >= 0 && cols >= 0)
    {
        if (temp[rows][cols] == 'Q')
        {
            return 0;
        }
        rows--;
        cols--;
    }

    rows = i, cols = j;
    // Right Diagonal :
    while (rows >= 0 && cols < n)
    {
        if (temp[rows][cols] == 'Q')
        {
            return 0;
        }
        rows--;
        cols++;
    }
    return 1;
}

// 2) We use the same logic but now we try to make left and right diagonals in O(1) also instead of O(n) search.
// Now we make two n^2 boxes for n = 5 , and observe in right diagonal that:
/*
        Col 0   Col 1   Col 2       Col 3   Col 4
Row 0 [   0   ][   1   ][   2   ][   3   ][   4   ]
Row 1 [   1   ][   2   ][   3   ][   4   ][   5   ]
Row 2 [   2   ][   3   ][   4   ][   5   ][   6   ]
Row 3 [   3   ][   4   ][   5   ][   6   ][   7   ]
Row 4 [   4   ][   5   ][   6   ][   7   ][   8   ]

We can see that by going towards the right diagonal upwards or downwards the value remains same for a particular diagonal.
If we see the pattern for any diagonal , then we can say that row+col = diagonal value.
Also our values are going upto 0-8 (9 Values) for n=5 box so we can make an array upto 2*n - 1.
So now when we visit (0,1) and place our queen here and for the next row , we check cols[0] = 0 is unmarked then we check the rightDig for this.
So if we can place the queen at (0,0) after having it placed at (0,1) we check rightDig where it tells by the [row+col] = [0+1] = [1] = 1 so we cannot place there.
Similarly if we had placed a queen at (0,3) then rightDig will correctly tell us not to place it at (1,2) , (2,1) , (0,3) because these are right diagonals and even their row+col sums are same = 3.
The sum remains sum across right diagonal because while going upwards towards right diagonal we do row-- and col++.

Now we see the left Diagonal :

        Col 0   Col 1   Col 2       Col 3   Col 4
Row 0 [   0   ][   1   ][   2   ][   3   ][   4   ]
Row 1 [  -1   ][   0   ][   1   ][   2   ][   3   ]
Row 2 [  -2   ][  -1   ][   0   ][   1   ][   2   ]
Row 3 [  -3   ][  -2   ][  -1   ][   0   ][   1   ]
Row 4 [  -4   ][  -3   ][  -2   ][  -1   ][   0   ]
We can see that by going towards the left diagonal for a particular upwards , we have row -- and col --.
So we can just get our answer by doing col-row or row-col. (because the differences are same when we stand at a particular (i,j) and then move across left diagonal).
Doing (row-col) gives us the matrix with same values only flipped triangular so we can do either row-col or col-row (we will go with col-row).
But we can see that we are encountering the negative values.
To avoid using unordered map for the negative value index , we will shift our index.
Here we see -4 , we make it 0 , by adding n=5 and also adding -1.
So now our formula becomes : (5-1)+(0-4) = 0 or (n-1)+(col-row)

        Col 0   Col 1       Col 2   Col 3   Col 4
Row 0 [   4   ][   5   ][   6   ][   7   ][   8   ]
Row 1 [   3   ][   4   ][   5   ][   6   ][   7   ]
Row 2 [   2   ][   3   ][   4   ][   5   ][   6   ]
Row 3 [   1   ][   2   ][   3   ][   4   ][   5   ]
Row 4 [   0   ][   1   ][   2   ][   3   ][   4   ]

Again here we have total values 2*n - 1.
So we use the [n-1+(col-row)] for checking whether we can place a value in the leftDig or not.
E.g if we placed a value at (0,0) then we check cols[0] = 1 is marked then  we check for (1,1) so we see (5-1)+(1-1) = 4 and that was marked when we visited (0,0) so this tells not to put the value at its left diagonal.
Similarly we won't be able to place a value at (2,2) , (3,3) , (4,4) as well because these are left diagonals and they all have same answer when we use (n-1)+(col-row).
*/

/*
Time Complexity :
Total Time Complexity still remains same because the time is mostly taken by the recursive call.
So total time still : O(n!) or O(n^2*n!)

Space Complexity :
Space taken is increase because now we use the left and right diagonals.
// Maximum Recursive depth that can go is n = O(n)
// Left and Right Diagonals = 2*n - 1 = O(2*n) = O(n)
// The temp vector is n^2 size = O(n^2)
// So space : O(n) + O(n) + O(n^2) = O(n^2)
// If we let total valid boards as 'S' , then ans vector total space : S*n^2.
// Total Space (including ans) : O(S*n^2) or O(n!*n^2) because S grows extremely fast relative to 'n' making it S <= n!
*/

/*
vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> ans;     // Answer to store all vector of strings
        vector<string> temp(n , string(n,'.'));       // One Temp Board

        // We use the column vector so that we know to put the queen at that column or not in O(1)
        // We also use the right left Diagonals so that we can find answer in O(1)
        vector<bool> cols(n, 0);
        vector<bool> rightDig(2 * n - 1, 0);
        vector<bool> leftDig(2 * n - 1, 0);
        helper(0, n, ans, temp, cols, leftDig, rightDig);
        return ans;
    }

void helper(int rows, int n, vector<vector<string>> &ans, vector<string> &temp, vector<bool> &cols, vector<bool> &leftDig, vector<bool> &rightDig)
{
    if (rows == n)
    {
        ans.push_back(temp);
        return;
    }

    for (int j = 0; j < n; j++)
    {
        if (cols[j] == 0 && rightDig[j + rows] == 0 && leftDig[(n - 1) + j - rows] == 0)
        {
            cols[j] = 1;
            temp[rows][j] = 'Q';
            rightDig[j + rows] = 1;
            leftDig[(n - 1) + j - rows] = 1;

            helper(rows + 1, n, ans, temp, cols, leftDig, rightDig);

            temp[rows][j] = '.';
            cols[j] = 0;
            rightDig[j + rows] = 0;
            leftDig[(n - 1) + j - rows] = 0;
        }
    }
}
*/

int main()
{
    int n;
    cout << "Enter n (1-9) : ";
    cin >> n;
    vector<vector<string>> ans = solveNQueens(n);
    for (int i = 0; i < ans.size(); i++)
    {
        for (int j = 0; j < ans[i].size(); j++)
        {
            cout << ans[i][j] << endl;
        }
        cout << endl
             << endl;
    }

    return 0;
}

// Recursive Tree for N-Queens where n = 4.
/*
                                                            ROOT: helper(row = 0)
                      /                               |                               |                               \
                 j = 0 [Q...]                    j = 1 [.Q..]                    j = 2 [..Q.]                    j = 3 [...Q]
                      |                               |                               |                               |
              helper(row = 1)                 helper(row = 1)                 helper(row = 1)                 helper(row = 1)
             /   |     \    \                /   /     \    \                /   /     \    \                /   /     \    \
          j=0   j=1    j=2  j=3           j=0   j=1   j=2   j=3           j=0   j=1   j=2   j=3           j=0   j=1   j=2   j=3
           ❌    ❌     |    ❌            |     ❌    ❌    ❌            ❌    ❌    ❌     |            ❌     |    ❌    ❌
                      /                    |                                                  |                     |
              helper(row = 2)         helper(row = 2)                                 helper(row = 2)         helper(row = 2)
              /   |   \   \           /   |   \   \                                   /   |   \   \           /   |   \   \
            j=0 j=1 j=2 j=3         j=0 j=1 j=2 j=3                                 j=0 j=1 j=2 j=3         j=0 j=1 j=2 j=3
             ❌  ❌  ❌  ❌          ❌  ❌  |   |                                   |   ❌  ❌  ❌          ❌  ❌  ❌  ❌
             └───────────┘                  /     \                                  |                       └───────────┘
            LOOP FINISHES                  /       \                                 |                       LOOP FINISHES
           (Zero options!)                /         \                                |                      (Zero options!)
           Backtracks to       helper(row = 3)    helper(row = 3)             helper(row = 3)                Backtracks to
               Row 1           /  |  \  \          /  |  \  \                 /  |  \  \                         Row 1
                             j=0 j=1 j=2 j=3     j=0 j=1 j=2 j=3            j=0 j=1 j=2 j=3
                              ❌  ❌  ❌  ❌      ❌  ❌  |  ❌              ❌  |  ❌  ❌
                              └───────────┘              |                       |
                              LOOP FINISHES       helper(row = 4)         helper(row = 4)
                             (Zero options!)      (Base Case 🎉)          (Base Case 🎉)
                              Backtracks to       [1, 0, 3, 2]            [2, 3, 0, 1]
                             Row 2 to try j=3
*/
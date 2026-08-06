#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
You are given an m x n matrix board containing letters 'X' and 'O', capture regions that are surrounded:

Connect: A cell is connected to adjacent cells horizontally or vertically.
Region: To form a region connect every 'O' cell.
Surround: A region is surrounded if none of the 'O' cells in that region are on the edge of the board. Such regions are completely enclosed by 'X' cells.
To capture a surrounded region, replace all 'O's with 'X's in-place within the original board. You do not need to return anything.

Input: board = [["X","X","X","X"],
                ["X","O","O","X"],
                ["X","X","O","X"],
                ["X","O","X","X"]]

Output: [["X","X","X","X"],
        ["X","X","X","X"],
        ["X","X","X","X"],
        ["X","O","X","X"]]
*/

// Forward Declarations :
bool isValid(int i, int j, int m, int n);
void dfs(vector<vector<char>> &board, int i, int j, int m, int n, char sign, char original);

// This question is similar to the Closed Islands.
// Here we have to turn each of the inner 'O' to 'X'.
// However if there is any region of 'O' going to edge sides then we don't have to convert it to 'X'.
// So first , we turn all the edge side 'O' regions to '#'.
// Then we turn all the inner 'O' to 'X'.
// And lastly , we revert the edge region '#' back to 'O'.
// We write only 1 DFS instead of 2-3 by passing the signs and original as parameters.

// Time : O(mn)
// Space : O(mn) due to recursion stack.
void solve(vector<vector<char>> &board)
{
    int m = board.size();    // Rows
    int n = board[0].size(); // Cols

    // 1st and Last Row
    for (int i = 0; i < n; i++)
    {
        if (board[0][i] == 'O')
        {
            dfs(board, 0, i, m, n, '#', 'O');
        }
        if (board[m - 1][i] == 'O')
        {
            dfs(board, m - 1, i, m, n, '#', 'O');
        }
    }

    // 1st and Last Col
    for (int i = 0; i < m; i++)
    {
        if (board[i][0] == 'O')
        {
            dfs(board, i, 0, m, n, '#', 'O');
        }
        if (board[i][n - 1] == 'O')
        {
            dfs(board, i, n - 1, m, n, '#', 'O');
        }
    }

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            if (board[i][j] == 'O')
            {
                dfs(board, i, j, m, n, 'X', 'O');
            }
        }
    }

    // Revert '#' to 'O'
    // 1st and Last Row
    for (int i = 0; i < n; i++)
    {
        if (board[0][i] == '#')
        {
            dfs(board, 0, i, m, n, 'O', '#');
        }
        if (board[m - 1][i] == '#')
        {
            dfs(board, m - 1, i, m, n, 'O', '#');
        }
    }

    // 1st and Last Col
    for (int i = 0; i < m; i++)
    {
        if (board[i][0] == '#')
        {
            dfs(board, i, 0, m, n, 'O', '#');
        }
        if (board[i][n - 1] == '#')
        {
            dfs(board, i, n - 1, m, n, 'O', '#');
        }
    }
}

void dfs(vector<vector<char>> &board, int i, int j, int m, int n, char sign, char original)
{
    board[i][j] = sign;

    if (isValid(i - 1, j, m, n) && board[i - 1][j] == original)
    {
        dfs(board, i - 1, j, m, n, sign, original);
    }

    if (isValid(i + 1, j, m, n) && board[i + 1][j] == original)
    {
        dfs(board, i + 1, j, m, n, sign, original);
    }

    if (isValid(i, j - 1, m, n) && board[i][j - 1] == original)
    {
        dfs(board, i, j - 1, m, n, sign, original);
    }

    if (isValid(i, j + 1, m, n) && board[i][j + 1] == original)
    {
        dfs(board, i, j + 1, m, n, sign, original);
    }
}

bool isValid(int i, int j, int m, int n)
{
    if (i >= 0 && j >= 0 && i < m && j < n)
    {
        return 1;
    }
    return 0;
}
int main()
{
    vector<vector<char>> board = {
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'X', 'O', 'X'},
        {'X', 'O', 'X', 'X'}};
    solve(board);
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
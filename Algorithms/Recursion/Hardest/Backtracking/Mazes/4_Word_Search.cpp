#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
Given an m x n grid of characters board and a string word, return true if word exists in the grid.
The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.
*/

// Forward Declarations :
bool isValid(int i, int j, int m, int n);
bool dfs(vector<vector<char>> &board, string &word, int i, int j, int index);

// 1) We use a standard DFS.
// We check at each index in m by n matrix , if word[0] matches it or not so we can start looking for it.
// If it matches then we run a DFS and keep looking for it until we find the complete word or mismatch it in between.
/*
Time Complexity: O(M * N * 3^L)
M * N: In the worst-case scenario, our outer loop in exist() checks every single cell in the M x N grid as a potential starting point for our word.
3^L: L is the length of our string word. At our starting cell, we can explore up to 4 directions. However, for every step after the first, we cannot go back to the cell we just came from (since it is marked in our visited tracker). Thus, we only have at most 3 remaining directions to choose from. For a word of length L, our DFS search tree goes up to depth L, making our maximum branching work O(3^L).
Total Time = O(M * N * 3^L)

Space Complexity: O(M * N + L)
O(M * N) for visited Matrix: Our 2D boolean grid takes memory proportional to the size of our board (M x N).
O(L) for Call Stack: The maximum depth of our recursive call stack is bounded by the length of our word L (our algorithm stops once index == word.size()).
Total Space = O(M * N + L)
*/

bool exist(vector<vector<char>> &board, string word)
{
    int m = board.size();
    int n = board[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, 0));

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // Start DFS only if the first character matches
            if (board[i][j] == word[0])
            {
                if (dfs(board, word, visited, i, j, 1, m, n))
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

bool dfs(vector<vector<char>> &board, string &word, vector<vector<bool>> &visited, int i, int j, int index, int m, int n)
{
    if (index == word.size())
    {
        return 1;
    }

    visited[i][j] = 1;

    // 1. Down (i + 1, j)
    if (isValid(i + 1, j, m, n) && board[i + 1][j] == word[index] && !visited[i + 1][j])
    {
        if (dfs(board, word, visited, i + 1, j, index + 1, m, n))
        {
            return 1;
        }
    }

    // 2. Right (i, j + 1)
    if (isValid(i, j + 1, m, n) && board[i][j + 1] == word[index] && !visited[i][j + 1])
    {
        if (dfs(board, word, visited, i, j + 1, index + 1, m, n))
        {
            return 1;
        }
    }

    // 3. Up (i - 1, j)
    if (isValid(i - 1, j, m, n) && board[i - 1][j] == word[index] && !visited[i - 1][j])
    {
        if (dfs(board, word, visited, i - 1, j, index + 1, m, n))
        {
            return 1;
        }
    }

    // 4. Left (i, j - 1)
    if (isValid(i, j - 1, m, n) && board[i][j - 1] == word[index] && !visited[i][j - 1])
    {
        if (dfs(board, word, visited, i, j - 1, index + 1, m, n))
        {
            return 1;
        }
    }

    visited[i][j] = 0;
    return 0;
}

bool isValid(int i, int j, int m, int n)
{
    if (i >= 0 && i < m && j >= 0 && j < n)
    {
        return 1;
    }
    return 0;
}

// 2) We use the original board as our visited array.
// We keep the variable from the board inside a 'temp' variable and then we place another symbol that won't come in our board.
// Then we keep doing this and we can return our board to its original state if we cannot do any moves and then place board i,j to temp.
// Time : O(m*n*3^l)
// Space : O(l)
bool dfs2(vector<vector<char>> &board, string &word, int i, int j, int index, int m, int n)
{
    if (index == word.size())
    {
        return 1;
    }

    char temp = board[i][j];
    board[i][j] = '#';

    // 1. Down (i + 1, j)
    if (isValid(i + 1, j, m, n) && board[i + 1][j] == word[index])
    {
        if (dfs2(board, word, i + 1, j, index + 1, m, n))
        {
            return 1;
        }
    }

    // 2. Right (i, j + 1)
    if (isValid(i, j + 1, m, n) && board[i][j + 1] == word[index])
    {
        if (dfs2(board, word, i, j + 1, index + 1, m, n))
        {
            return 1;
        }
    }

    // 3. Up (i - 1, j)
    if (isValid(i - 1, j, m, n) && board[i - 1][j] == word[index])
    {
        if (dfs2(board, word, i - 1, j, index + 1, m, n))
        {
            return 1;
        }
    }

    // 4. Left (i, j - 1)
    if (isValid(i, j - 1, m, n) && board[i][j - 1] == word[index])
    {
        if (dfs2(board, word, i, j - 1, index + 1, m, n))
        {
            return 1;
        }
    }

    board[i][j] = temp;
    return 0;
}
int main()
{
    string x = "ABCCED";
    vector<vector<char>> board = {{'A', 'B', 'C', 'E'},
                                  {'S', 'F', 'C', 'S'},
                                  {'A', 'D', 'E', 'E'}};
    bool y = exist(board, x);
    cout << "Word Exists ? " << boolalpha << y << endl;
    return 0;
}
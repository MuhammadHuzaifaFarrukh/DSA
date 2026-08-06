#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
Note:

A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.
*/
// This is not a recursion question however , for solving it , one must know the basics of recursion + backtracking and sudoku as well.

// Because we have to check just the numbers that are already filled , we just run a loop of 81 numbers.
// If there is a dot , we skip otherwise we check it with our conditions.
// Also while checking for same row/col , we might check the same number , so for this we have two options :
// 1) Place Conditions inside the check() function more like row!=i and col!=j and then for grid as well.
// 2) Make the cell to be checked as dot and when checked , then return to its normal state.
// 2nd option is more easier and suitable.
// Time : O(81) = O(1).
// Space : O(1)
bool isValidSudoku(vector<vector<char>> &board)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == '.')
            {
                continue;
            }
            else
            {
                int num = board[i][j] - '0';
                board[i][j] = '.';
                if (!checkConditions(board, num, i, j))
                {
                    return 0;
                }
                board[i][j] = '0' + num;
            }
        }
    }
    return 1;
}

// Runs in O(1)
bool checkConditions(vector<vector<char>> &board, int num, int i, int j)
{
    char c = '0' + num;
    // Check at same row
    for (int col = 0; col < 9; col++)
    {
        if (board[i][col] == c) // && col!=j
        {
            return 0;
        }
    }
    // Check at same col
    for (int row = 0; row < 9; row++)
    {
        if (board[row][j] == c) // && row!=i
        {
            return 0;
        }
    }

    // Checking for the 3 by 3 box.
    int row = i / 3 * 3, col = j / 3 * 3;
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (board[x + row][y + col] == c) // ( (x+row != i) || (y+col!=j) )
            {
                return 0;
            }
        }
    }
    return 1;
}
int main()
{
    vector<vector<char>> board = {{'5', '3', '.', '.', '7', '8', '9', '.', '2'},
                                  {'6', '7', '2', '1', '9', '5', '3', '.', '.'},
                                  {'.', '9', '8', '.', '4', '.', '5', '.', '7'},
                                  {'8', '5', '9', '7', '.', '1', '4', '2', '.'},
                                  {'4', '2', '6', '8', '5', '.', '7', '9', '.'},
                                  {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
                                  {'9', '6', '.', '5', '.', '7', '2', '8', '.'},
                                  {'2', '8', '7', '4', '1', '.', '.', '.', '5'},
                                  {'3', '4', '5', '2', '8', '.', '.', '7', '9'}};

    cout << "Is it valid ? : " << boolalpha << isValidSudoku(board) << endl;

    return 0;
}
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:

Each of the digits 1-9 must occur exactly once in each row.
Each of the digits 1-9 must occur exactly once in each column.
Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
The '.' character indicates empty cells.
*/
// This is like permutation without repetition with some constraints.

// We make 2 functions for this implementation.
// First we make a helper function which is going to be a recursive one and 2nd we make a check function that will check the constraints.
// Inside the helper function we use (i,j) as positions.
// Once our 'i' row reaches 9th row , it means we've successfully completed our sudoku.
// So i==9 means return 1 and if j == 9 , this means to go on the next row for more checks.
// Also there are some dots which means we have to fill those places , so we also check that if there are no dots then skip this cell , and move on to the next cell in the same row.
// Now we have 9 choices but for placing the choice we have to check our constraints now.
// For this our checker function will help us. This checker checks and iterates on the same row and same column to check if this number appeared before in that same row / column of that cell.
// After it passes this check , we also have to check if this number is present in a 3 by 3 grid (which is another check constraint).
// Sudoku board has total 9 of the 3 by 3 grids as :
// 1) (0,0) -> (2,2)    2) (0,3) -> (2,5)       3) (0,6) -> (2,8)
// 4) (3,0) -> (5,2)    5) (3,3) -> (5,5)       6) (3,6) -> (5,8)
// 7) (6,0) -> (8,2)    8) (6,3) -> (8,5)       9) (6,6) -> (8,8)

// Rows 0,1,2 give i/3 = 0
// Rows 3,4,5 give i/3 = 1
// Rows 6,7,8 give i/3 = 2

// Cols 0,1,2 give j/3 = 0
// Cols 3,4,5 give j/3 = 1
// Cols 6,7,8 give j/3 = 2

// Now we can easily find out that if we are given any (i,j) , we can tell which grid it belongs to.
// So if we use hit and trial we see there are differences of 3 rows/cols.
// Now we can just i/3 and j/3 as i,j will have values 0-8 so i/3 and j/3 can have values : 0,1,2 only
// Now if we multiply them by 3 , we can map them to find exact row/col : floor(i/3)*3 and floor(j/3)*3.
// E.g : If we are given : (4,5) = (i,j) then we just : 4/3*3 and 5/3*3 = 1*3 and 1*3 = 3 and 3. => (3,3) is the starting point of a 3 by 3 grid that covers (4,5).

// Now once these checks are done , we call the same function for the next cell in same row and check if it can be done.
// So helper() will be called again and again until i==9 is reached.
// Also if we cannot place any choice , then we backtrack to the previous state.

// Suppose we have (5,3,.,7,8,9,.,.) in a particular row. Now we check for the '.' to place a number so we check its (row,col) and 3 by 3 grid as well. If we can place a number only then we move on.
// If we've tried all choices and still the check function says that we cannot place any number at a cell (i,j) then we move to the previous state and see the last number we entered was wrong so we try to enter any other number.
// If we are successful this time , then we move on and again check for the cell that we failed on. If we are not successful the time we backtracked to the previous cell , then we backtrack again to find even previous last state than this one to find any other choice we can enter.
// If this sudoku is solvable , then after many backtracks , it will successfully find the choices and if it is an impossible one , then it will keep backtracking and then it will reach the first cell where we had to put our choice which will eventually run out of choices and we will have to declare that this is not solvable sudoku.

// Time Complexity :
// If the sudoku is completely empty then we have 9 by 9 choices = 81 choices on the board.
// For each choice , we make recursive calls from num = 1 to 9 , which means that on average , each cell has 9 decision nodes.
// So each node splits into 9 branches , it means in 81 nodes , it would split into : 9 * 9 * 9 *,..., *9 (81 times)= 9^81 branches. (Although when we place a choice , then we have fewer than 9 choices left but we just say approx).
// Time Complexity : O(9^81) (or O(1) still fixed number)

// Space Complexity :
// The board is already given and we don't use any extra space other than recursive stack.
// When a decision for a cell is selected by selecting a number , we go on to check the decision for the next cell and so on.
// In the worst case (81 empty cells), there will be at most 81 stack frames stored in memory at any one time.
// Space : O(m) where m is the number of empty cells m<= 81 making it O(1)

void solveSudoku(vector<vector<char>> &board)
{
    // If we want to also give answer whether this sudoku is solvable or not , then we can just store this helper() function's answer inside a boolean variable and then check.
    // bool isSolvable = helper(board,0,0);
    helper(board, 0, 0);
}

bool helper(vector<vector<char>> &board, int i, int j)
{
    // If all rows are done , then it means we successfully completed the sudoku
    if (i == 9)
    {
        return 1;
    }

    if (j == 9)
    {
        return helper(board, i + 1, 0);
    }

    if (board[i][j] != '.')
    {
        return helper(board, i, j + 1);
    }

    for (int num = 1; num <= 9; num++)
    {
        if (checkConditions(board, num, i, j))
        {
            board[i][j] = '0' + num;
            if (helper(board, i, j + 1))
            {
                return 1;
            }
            board[i][j] = '.';
        }
    }
    return 0;
}
bool checkConditions(vector<vector<char>> &board, int num, int i, int j)
{
    char c = '0' + num;
    // Check at same row
    for (int col = 0; col < 9; col++)
    {
        if (board[i][col] == c)
        {
            return 0;
        }
    }
    // Check at same col
    for (int row = 0; row < 9; row++)
    {
        if (board[row][j] == c)
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
            if (board[x + row][y + col] == c)
            {
                return 0;
            }
        }
    }
    return 1;
}

// 2) Same logic but now we will optimize the part of the checker in O(1) which was before in O(27).
// All the base cases and other things are same.
// We make 3 2D arrays , one for row , one for column and one for the grid of 3 by 3.
// These will instantly tell us instead of iterating over whole row / col / grid of 3 by 3.
// We initially keep them as 0 (false) and the board given is filled a bit , so we also fill it accordingly.
// We have row array of 9 rows and 10 columns , so any number say 5 occurs in the (0,0) then we just mark it 0th row and column actually here represents numbers (1-9) (we do have extra column 0 here).
// So number 5 at (0,0) gets marked in our row array as 0th row and 5th column which can be checked instantly if there is any 5 in the 0th row.
// Now we also mark this 5 in our column array which has 9 rows and 10 columns. Here 9 rows are actually 9 columns and 10 columns are actually 1-9 numbers.
// Number 5 at (0,0) gets marked at 0th row 5th column.
// If there is a Number 3 at (1,0) , then it gets marked at row 1 and column 3 which can be checked instantly if there is any number 3 in the 1-indexed column.
// Now we have total 9 boxes.
/*
Box 0 | Box 1 | Box 2   <-- Rows 0-2
-------+-------+-------
 Box 3 | Box 4 | Box 5   <-- Rows 3-5
-------+-------+-------
 Box 6 | Box 7 | Box 8   <-- Rows 6-8
*/
// So we map those boxes using the formula but a little changed : floor(i/3)*3 + floor(j/3)
// This formula is just like a jagged array if we considered it as whole 9 by 9 matrix as a flat 1D array then we could reach any index by i*9 + j but now we just divided it by 3 for our partitions.
// We added j/3 for complete address.
// Now if we have a number 4 at (2,3) then this formula finds it : (2/3)*3 + (3/3) = 0+1 = 1.
// So it means that we have to place it in box 1 (index 1 of the box array).
// So this number 4 at (2,3) gets marked at row 1-index and column 4. Column shows the number , and row shows the whole box indices.
// Each of the 9 boxes have 9 values.
// So now we can instantly check that if there is any number 4 in the box 1.
// This formula (i/3)*3 +j/3 is the mapping of the 9 boxes originally now as 9 rows of boxes with each column showing the number.
// Once we've filled our board with the given values , then we move on to the recursive part and do the same while backtracking.
// When we move forward we fill our lookup tables also just like we discussed here and when we backtrack then we fill 0 in them again.
// Time : O(9^81) = O(1)
// Space : O(1) (Because arrays are still fixed and so is the stack space)
void solveSudoku2(vector<vector<char>> &board)
{
    vector<vector<bool>> rows(9, vector<bool>(10, 0));
    vector<vector<bool>> cols(9, vector<bool>(10, 0));
    vector<vector<bool>> boxes(9, vector<bool>(10, 0));
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] != '.')
            {
                int num = board[i][j] - '0';
                int box_idx = (i / 3) * 3 + (j / 3);
                rows[i][num] = 1;
                cols[j][num] = 1;
                boxes[box_idx][num] = 1;
            }
        }
    }

    helper2(board, 0, 0, rows, cols, boxes);
}

bool helper2(vector<vector<char>> &board, int i, int j, vector<vector<bool>> &rows, vector<vector<bool>> &cols, vector<vector<bool>> &boxes)
{
    if (i == 9)
    {
        return 1;
    }
    if (j == 9)
    {
        return helper2(board, i + 1, 0, rows, cols, boxes);
    }

    if (board[i][j] != '.')
    {
        return helper2(board, i, j + 1, rows, cols, boxes);
    }

    int box_idx = (i / 3) * 3 + (j / 3);

    for (int num = 1; num <= 9; num++)
    {
        if (!rows[i][num] && !cols[j][num] && !boxes[box_idx][num])
        {

            board[i][j] = '0' + num;
            rows[i][num] = 1;
            cols[j][num] = 1;
            boxes[box_idx][num] = 1;

            if (helper2(board, i, j + 1, rows, cols, boxes))
            {
                return 1;
            }

            board[i][j] = '.';
            rows[i][num] = 0;
            cols[j][num] = 0;
            boxes[box_idx][num] = 0;
        }
    }

    return 0;
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

    solveSudoku(board);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
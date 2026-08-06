#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
You are given row x col grid representing a map where grid[i][j] = 1 represents land and grid[i][j] = 0 represents water.
Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).
The island doesn't have "lakes", meaning the water inside isn't connected to the water around the island. One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.
Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
Output: 16
*/

// Forward Declarations :
bool isValid(int i, int j, int m, int n);
int dfs(vector<vector<int>> &grid, int i, int j, int m, int n);

// If they were just 1d array structures , we could have used the formula (no of boxes *2) + 2.
// However as they are 2D structures , the more close they get , the more perimeter gets decreased.
// So we find the first cell that is 1.
// Grid contains 0s and 1s.

// After that we run a basic DFS on it and put 3 base cases on it.
// If a neighbouring cell is 1 , it won't be counted in perimeter because it touches its internal edge.
// However if a neighbouring cell is 0 or if we are at the boundary , then we count it as 1.
// So first we check the validity of (i,j) entry , if its not valid , meaning we are out of bounds , and this means we came from the edge of a previous cell , so we add 1.
// Then we check if this entry is 0 or not , if it is then it means that we came from the cell whose neighbour is 0 so we count it as external edge as 1.
// If this entry is 2 , means we already visited it , so we return 0 from this one.
// We put 2 for the cells we've visited otherwise if we place 0 , then we cannot differentiate if it is a neighbour 0 or visiting 0.
// So this question is just a little different because we check validity at the top instead of doing it with move.
// We select the move later and then check if its valid or not , and if not valid (at the edge out of bounds ) , it means that we encountered an external edge of the island.
// If we select a move that is 0 , it means we again encounter external edge of island so we add 1 for this as well.
// If we select a move that is 2 , it means we have already checked that it comes this way , so we don't need to deal with it here.
// All the moves (up,down,left,right) will give us the answers.

// Time : O(mn)
// Space : O(mn) due to recursion otherwise O(1)
int islandPerimeter(vector<vector<int>> &grid)
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] == 1)
            {
                return dfs(grid, i, j, grid.size(), grid[i].size());
            }
        }
    }
}

int dfs(vector<vector<int>> &grid, int i, int j, int m, int n)
{
    // We are out of bounds , so previous cell was at the boundary of the grid.
    if (!isValid(i, j, m, n))
    {
        return 1;
    }

    // We are at the external edge of island , so we add 1 from it.
    if (grid[i][j] == 0)
    {
        return 1;
    }

    // Already visited , we cannot use this i,j move
    if (grid[i][j] == 2)
    {
        return 0;
    }

    grid[i][j] = 2;

    int count = 0;
    // Use any 4 moves with Validation at the top.
    count += dfs(grid, i + 1, j, m, n);
    count += dfs(grid, i - 1, j, m, n);
    count += dfs(grid, i, j - 1, m, n);
    count += dfs(grid, i, j + 1, m, n);

    return count;
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
    vector<vector<int>> v = {{0, 1, 0, 0},
                             {1, 1, 1, 0},
                             {0, 1, 0, 0},
                             {1, 1, 0, 0}};
    cout << "Perimeter of the Island : " << islandPerimeter(v) << endl;
    return 0;
}
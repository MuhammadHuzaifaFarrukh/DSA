#include <iostream>
#include <string>
#include <vector>

using namespace std;
/*
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
*/

// Forward Declarations :
bool isValid(int i, int j, int m, int n);
void dfs(vector<vector<char>> &grid, int i, int j, int m, int n, vector<vector<bool>> &visited);

// 1) Using Visited Array :
// An Island can be consecutive number of 1's in vertical or horizontal side connected e.g '1111' or
// '1111    or   '1
//  1  1'          1'
// Like this , as long as we don't encounter 0 , we can say its an island , meaning we need to find the connected components (in graphs terms).
// So what we do is we make a visited array of grid size.
// Now if visited is not 0 , and grid i,j is 1 , only then we start our dfs to make all the connected ones with it vertically or horizontally as zeroes.
// So we actually make visited filled where our island is in grid matrix.
// Any Island from grid is marked as an island in the visited array and that's why we check that visited[i][j] must be 0 if we have grid[i][j] = '1' there because if it is , then we just run another DFS to make that island on visited array and make count++.
// We don't backtrack in this , we just explore the depth of the island unless we encounter any neighbouring '0'.

// Time Complexity :
/*
Outer Loops: We iterate through every cell in the m*n matrix once.
DFS Calls: Every cell is visited at most once across the entire run.
Because we mark visited[i][j] = 1 permanently (without backtracking to unmark it), no cell is ever re-explored by DFS.
Time : O(mn)
*/
// Space Complexity :
/*
visited Grid: Storing our 2D boolean array takes m*n auxiliary memory.
Recursion Stack: In the worst-case scenario (e.g., a grid filled entirely with '1's or a long snake-like island), the DFS call stack can go up to depth m*n, which takes space.
Space : O(mn)
*/

int numIslands(vector<vector<char>> &grid)
{
    int count = 0;
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), 0));
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            // Start DFS only if the cell is '1'
            if (!visited[i][j] && grid[i][j] == '1')
            {
                dfs(grid, i, j, grid.size(), grid[i].size(), visited);
                count++;
            }
        }
    }
    return count;
}

void dfs(vector<vector<char>> &grid, int i, int j, int m, int n, vector<vector<bool>> &visited)
{
    visited[i][j] = 1;
    // All Moves (if possible) :
    if (isValid(i - 1, j, m, n) && grid[i - 1][j] == '1' && !visited[i - 1][j])
    {
        dfs(grid, i - 1, j, m, n, visited);
    }

    if (isValid(i + 1, j, m, n) && grid[i + 1][j] == '1' && !visited[i + 1][j])
    {
        dfs(grid, i + 1, j, m, n, visited);
    }

    if (isValid(i, j - 1, m, n) && grid[i][j - 1] == '1' && !visited[i][j - 1])
    {
        dfs(grid, i, j - 1, m, n, visited);
    }

    if (isValid(i, j + 1, m, n) && grid[i][j + 1] == '1' && !visited[i][j + 1])
    {
        dfs(grid, i, j + 1, m, n, visited);
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

// 2) Without Visited Array :
// We make the changes inside the grid.
// For marking the visited places , we just do it by seeing grid[i][j] == '1' and inside DFS , we make its island to water by turning grid[i][j] = '0'.
// Time : O(mn)
// We use no extra space : O(1)
// Space : O(mn) due to recursion.
void dfs2(vector<vector<char>> &grid, int i, int j, int m, int n)
{
    grid[i][j] = '0';
    // All Moves (if possible) :
    if (isValid(i - 1, j, m, n) && grid[i - 1][j] == '1')
    {
        dfs2(grid, i - 1, j, m, n);
    }

    if (isValid(i + 1, j, m, n) && grid[i + 1][j] == '1')
    {
        dfs2(grid, i + 1, j, m, n);
    }

    if (isValid(i, j - 1, m, n) && grid[i][j - 1] == '1')
    {
        dfs2(grid, i, j - 1, m, n);
    }

    if (isValid(i, j + 1, m, n) && grid[i][j + 1] == '1')
    {
        dfs2(grid, i, j + 1, m, n);
    }
}

int main()
{
    vector<vector<char>> grid = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}};

    cout << "Number of Islands : " << numIslands(grid) << endl;
    return 0;
}
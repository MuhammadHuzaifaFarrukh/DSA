#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.)
You may assume all four edges of the grid are surrounded by water.
The area of an island is the number of cells with a value 1 in the island.
Return the maximum area of an island in grid. If there is no island, return 0.

Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],
                [0,0,0,0,0,0,0,1,1,1,0,0,0],
                [0,1,1,0,1,0,0,0,0,0,0,0,0],
                [0,1,0,0,1,1,0,0,1,0,1,0,0],
                [0,1,0,0,1,1,0,0,1,1,1,0,0],
                [0,0,0,0,0,0,0,0,0,0,1,0,0],
                [0,0,0,0,0,0,0,1,1,1,0,0,0],
                [0,0,0,0,0,0,0,1,1,0,0,0,0]]
Output: 6
Explanation: The answer is not 11, because the island must be connected 4-directionally.
*/

// Forward Declarations :
int dfs(vector<vector<int>> &grid, int i, int j, int m, int n);
bool isValid(int i, int j, int m, int n);

// We find the area of each island by iterating over the grid and finding any 1 first.
// Once we have it , it means we have the starting point of an island , so we start counting the number of steps from there we can make to 0.
// We take an island and mark its 1s to 0s using DFS and then we go on to the next one.
// Visited areas of island are marked 0 as water after being visited.
// Then we compare the max area for each island.

// Time : O(mn)
// Space : O(mn) due to recursion stack
int maxAreaOfIsland(vector<vector<int>> &grid)
{
    int area = INT_MIN;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] == 1)
            {
                area = max(area, dfs(grid, i, j, grid.size(), grid[i].size()));
            }
        }
    }
    if (area == INT_MIN)
    {
        return 0;
    }
    return area;
}
int dfs(vector<vector<int>> &grid, int i, int j, int m, int n)
{
    int area = 1;
    grid[i][j] = 0; // We mark the visited areas of the islands as water after visiting.
    if (isValid(i + 1, j, m, n) && grid[i + 1][j] == 1)
    {
        area += dfs(grid, i + 1, j, m, n);
    }

    if (isValid(i - 1, j, m, n) && grid[i - 1][j] == 1)
    {
        area += dfs(grid, i - 1, j, m, n);
    }

    if (isValid(i, j - 1, m, n) && grid[i][j - 1] == 1)
    {
        area += dfs(grid, i, j - 1, m, n);
    }

    if (isValid(i, j + 1, m, n) && grid[i][j + 1] == 1)
    {
        area += dfs(grid, i, j + 1, m, n);
    }
    return area;
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
    vector<vector<int>> v = {
        {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}};

    cout << "Max Area of the Island : " << maxAreaOfIsland(v) << endl;
    return 0;
}
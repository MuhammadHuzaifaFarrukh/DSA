#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
Given a 2D grid consists of 0s (land) and 1s (water).
An island is a maximal 4-directionally connected group of 0s and a closed island is an island totally (all left, top, right, bottom) surrounded by 1s.
Return the number of closed islands.

Input: grid = [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]
Output: 1

Input: grid = [[1,1,1,1,1,1,1],
               [1,0,0,0,0,0,1],
               [1,0,1,1,1,0,1],
               [1,0,1,0,1,0,1],
               [1,0,1,1,1,0,1],
               [1,0,0,0,0,0,1],
               [1,1,1,1,1,1,1]]
Output: 2
*/

// Forward Declarations :
bool isValid(int i, int j, int m, int n);
void dfs(vector<vector<int>> &grid, int i, int j, int m, int n);

// A Closed Island group of 0s is closed only if it is surrounded by water 1s , and no part of the island must be at the edge sides of the grid.
// If we find a 0s border on corner ,its not a closed island , because we aren't considering the out-of-bounds area of water.
// So what we do is , first we run a DFS on first and last row , first and last columns to find if there is any 0 there then that means that there is a part of the island on the edge sides.
// So first we remove those islands out.
// Then after that , we just run a usual (mn) loop to find out the number of islands as usual like in the problem (Number of Islands).
// All the islands (0s) we are gonna find , are gonna be closed now , because we have eliminated all the islands who were touching either first,last row or first last column.
// So now when we find 0s in the (mn) loop , we run a DFS and incrememnt our count at each DFS.
// We convert each island (0s) to water (1s) marking it as visited.

// Time : O(mn)
// Space : O(mn) due to recursion stack
int closedIsland(vector<vector<int>> &grid)
{
    int count = 0;
    int m = grid.size(), n = grid[0].size();

    // 1st and Last Row
    for (int i = 0; i < n; i++)
    {
        if (grid[0][i] == 0)
        {
            dfs(grid, 0, i, m, n);
        }
        if (grid[m - 1][i] == 0)
        {
            dfs(grid, m - 1, i, m, n);
        }
    }

    // 1st and Last Col
    for (int i = 0; i < m; i++)
    {
        if (grid[i][0] == 0)
        {
            dfs(grid, i, 0, m, n);
        }
        if (grid[i][n - 1] == 0)
        {
            dfs(grid, i, n - 1, m, n);
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == 0)
            {
                count++;
                dfs(grid, i, j, m, n);
            }
        }
    }
    return count;
}
void dfs(vector<vector<int>> &grid, int i, int j, int m, int n)
{
    grid[i][j] = 1;
    if (isValid(i + 1, j, m, n) && grid[i + 1][j] == 0)
    {
        dfs(grid, i + 1, j, m, n);
    }

    if (isValid(i - 1, j, m, n) && grid[i - 1][j] == 0)
    {
        dfs(grid, i - 1, j, m, n);
    }

    if (isValid(i, j - 1, m, n) && grid[i][j - 1] == 0)
    {
        dfs(grid, i, j - 1, m, n);
    }

    if (isValid(i, j + 1, m, n) && grid[i][j + 1] == 0)
    {
        dfs(grid, i, j + 1, m, n);
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
    vector<vector<int>> v = {
        {0, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0}};

    cout << "Number of Closed Islands : " << closedIsland(v) << endl;
    return 0;
}
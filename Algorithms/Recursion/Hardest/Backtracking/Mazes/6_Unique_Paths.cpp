#include <iostream>
#include <vector>
#include <string>

using namespace std;
/*
You are given an m x n integer array grid where grid[i][j] could be:
1 representing the starting square. There is exactly one starting square.
2 representing the ending square. There is exactly one ending square.
0 representing empty squares we can walk over.
-1 representing obstacles that we cannot walk over.
Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.

Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
Output: 2
Explanation: We have the following two paths:
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
*/

// Forward Declarations :
bool isValid(int i, int j, int m, int n);
int dfs(vector<vector<int>> &grid, vector<vector<bool>> &visited, int i, int j, int m, int n, int walkables);

// We count the total walkable paths (0s).
// Then we check on each path whether it is 1 or not because this 1 is our starting point.
// After finding our starting point , we run a DFS on it.
// We also keep a visited tracker.
// We send walkables+1 , because we are counting the grid[i][j] = 1 as well other than zeroes.
// If we find i,j = 2 then we check our walkables finished or not and if they are then we've found a unique path.
// If the walkables still left then it means , we haven't used up all the walkables.
// If we haven't found grid[i][j] = 2 then we go and search for it in our up,down,left,right moves and also keep marked those cells which we visited.
// When we backtrack then we make them unmarked and also return the count.

// Time Complexity :
// We have a grid of m*n cells and at each cell we have on average 3 choices , because we cannot go back to the cell where we came from for further uniqueness.
// So we have Time : O(3^(m*n)).

// Space Complexity :
// We use a visited array of size m*n.
// Recursive space is also m*n.
// Space : O(mn)
int uniquePathsIII(vector<vector<int>> &grid)
{
    int walkables = 0, count = 0;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] == 0)
            {
                walkables++;
            }
        }
    }

    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), 0));
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            // Start DFS from here :
            if (grid[i][j] == 1)
            {
                count += dfs(grid, visited, i, j, grid.size(), grid[i].size(), walkables + 1);
            }
        }
    }
    return count;
}

int dfs(vector<vector<int>> &grid, vector<vector<bool>> &visited, int i, int j, int m, int n, int walkables)
{
    if (grid[i][j] == 2)
    {
        if (walkables == 0)
        {
            return 1;
        }
        return 0;
    }

    int count = 0;
    visited[i][j] = 1;
    if (isValid(i + 1, j, m, n) && grid[i + 1][j] != -1 && !visited[i + 1][j])
    {
        count += dfs(grid, visited, i + 1, j, m, n, walkables - 1);
    }

    if (isValid(i - 1, j, m, n) && grid[i - 1][j] != -1 && !visited[i - 1][j])
    {
        count += dfs(grid, visited, i - 1, j, m, n, walkables - 1);
    }

    if (isValid(i, j + 1, m, n) && grid[i][j + 1] != -1 && !visited[i][j + 1])
    {
        count += dfs(grid, visited, i, j + 1, m, n, walkables - 1);
    }

    if (isValid(i, j - 1, m, n) && grid[i][j - 1] != -1 && !visited[i][j - 1])
    {
        count += dfs(grid, visited, i, j - 1, m, n, walkables - 1);
    }

    visited[i][j] = 0;
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
    vector<vector<int>> grid = {{1, 0, 0, 0},
                                {0, 0, 0, 0},
                                {0, 0, 0, 2}};

    cout << "Total Paths : " << uniquePathsIII(grid) << endl;
    return 0;
}
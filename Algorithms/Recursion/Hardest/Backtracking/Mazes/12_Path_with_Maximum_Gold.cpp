#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
In a gold mine grid of size m x n, each cell in this mine has an integer representing the amount of gold in that cell, 0 if it is empty.

Return the maximum amount of gold you can collect under the conditions:

Every time you are located in a cell you will collect all the gold in that cell.
From your position, you can walk one step to the left, right, up, or down.
You can't visit the same cell more than once.
Never visit a cell with 0 gold.
You can start and stop collecting gold from any position in the grid that has some gold.

Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
Output: 24
Explanation:
[[0,6,0],
 [5,8,7],
 [0,9,0]]
Path to get the maximum gold, 9 -> 8 -> 7.

Input: grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
Output: 28
Explanation:
[[1,0,7],
 [2,0,6],
 [3,4,5],
 [0,3,0],
 [9,0,20]]
Path to get the maximum gold, 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7.
*/

// Forward Declarations :
int dfs(vector<vector<int>> &grid, int i, int j, int m, int n, int gold);
bool isValid(int, int, int, int);

// We have to try all the paths because we don't know which path gets us the max gold.
// Suppose this matrix [[0,6,0],[5,8,7],[0,9,0]].
// Now we have to see the first non-zero number and then we start exploring all the paths from it.
// We keep track of the gold accumulated while exploring the path and once we cannot explore it further , we backtrack and return the maxGold at that point.
// See at 6 , we can track 6->8->9 , or 6->8->5 , or 6->8->7 , the path 6->8->9 , we track the currentGold values and recursively call the function by adding the gold using another move and also keep the maxgold value.
// Along 6->8->9 , we keep gold 14 , and see max gold there is 6+8+9 = 23 , and we see it cannot be explored any further so we backtrack from there and explore the other paths while returning the maximum gold value 23.
// So we try the path 6->8->5 , here we keep gold 14, and see max gold is : 6+8+5 =19 , and we cannot explore any further so we again backtrack , and return this max gold 19, but now we still keep 23 , because we have already seen a path with maximum gold value so we discard this 19 value.
// Then we try another path 6->8->7 , here we keep gold 14 and see max gold : 6+8+7 = 21 , and we cannot explore any further so we backtrack returning 21 and still keep our maximum answer as 23.
// Now once we have finished DFS on 6 , we return to our (mn) loop and keep 23 as our answer.
// Now we check and try DFS on another path with  non-zero value , which is 5 in this case.
// While doing this all we get a maximum path of 7->8->9 = 24.
// Because we cannot know in advance which cell will give us the maximum gold , we try DFS at each cell having value > 0 and find the maximum gold path from those.

// Time Complexity :
// At each cell , we have approximately 3 moves.
// Total cells in worst case can have all non-zero (>0) values so it means this takes time upto m*n*3^k where 'k' is the number of gold cells we can get while exploring a path.
// So Time : O(m*n*3^k) where k is the number of gold cells in a path.

// Space Complexity :
// We don't use any extra space like visited matrix instead we use the grid matrix and convert its cells temporarily to 0 for O(1) space.
// Recursive stack can go upto the maximum path explored.
// The maximum depth of the call stack corresponds to the maximum length of a single valid path, which is bounded by k.
// Space : O(k)

int getMaximumGold(vector<vector<int>> &grid)
{
    int area = INT_MIN;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] > 0)
            {
                area = max(area, dfs(grid, i, j, grid.size(), grid[i].size(), 0));
            }
        }
    }
    if (area == INT_MIN)
    {
        return 0;
    }
    return area;
}

int dfs(vector<vector<int>> &grid, int i, int j, int m, int n, int gold)
{
    int temp = grid[i][j];
    int maxGold = gold + temp;
    grid[i][j] = 0;
    if (isValid(i - 1, j, m, n) && grid[i - 1][j] > 0)
    {
        maxGold = max(maxGold, dfs(grid, i - 1, j, m, n, gold + temp));
    }

    if (isValid(i + 1, j, m, n) && grid[i + 1][j] > 0)
    {
        maxGold = max(maxGold, dfs(grid, i + 1, j, m, n, gold + temp));
    }

    if (isValid(i, j - 1, m, n) && grid[i][j - 1] > 0)
    {
        maxGold = max(maxGold, dfs(grid, i, j - 1, m, n, gold + temp));
    }

    if (isValid(i, j + 1, m, n) && grid[i][j + 1] > 0)
    {
        maxGold = max(maxGold, dfs(grid, i, j + 1, m, n, gold + temp));
    }

    grid[i][j] = temp;
    return maxGold;
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
    vector<vector<int>> v = {{0, 6, 0},
                             {5, 8, 7},
                             {0, 9, 0}};
    cout << " Maximum Gold in a Path is : " << getMaximumGold(v) << endl;
    return 0;
}
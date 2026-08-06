#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Given a Maze Matrix with n dimensions , tell whether there is an exit to this maze if we start from (0,0) and end at (n-1,n-1).
// 1s indicate Walls.
// 0s indicate walkable paths.
// We can move in any of the 4 directions (Up, Down, Left, Right).

// Foward Declaration :
bool isValid(int i, int j, int n);

// We use the same logic to find all the paths like rat in a maze using 'DFS'.
// We just return our answer as yes or no so we just keep a temp array for storing a single path if it exists.
// Now if we are able to reach i=j=n-1 then we return yes.
// We then try our moves and we put this recursive function call in an if-statement so that if we are really able to reach our goal , then we immediately return from it.
// If we can make a further move , then we go there , and use down / right first moves because they might lead to our path earlier.
// Visited keeps tracks of our moves.
// If we cannot make any move further then we return 0 and backtrack and also pop the character out we pushed to undo our path.
// We can/cannot undo our visited 2D tracker.
// If we don't undo it , this helps us in decreasing our time complexity.
// We only undo because we cannot find a way so keeping visited as it , will help us in not visiting those blocked / deadends again.
// If we undo them , it will still find us correct answer (if it exists) , however it increases the time by visiting those blocked/deadends we once visited.

// Time : O(n^2) (or O(4^(n^2)) if we are undo our visited matrix)
// At worst we won't find our answer if our path is blocked.
// So we will fill up / visit our visited array n^2 times.
// So our time becomes n^2 at worst if we don't undo visited array.

// Space : O(n^2)

bool isSolvable(vector<vector<int>> &maze, string &path, vector<vector<bool>> &visited, int i, int j, int n)
{
    if (i == n - 1 && j == n - 1)
    {
        return 1;
    }
    visited[i][j] = 1;

    // Down, Right, Up , Left
    if (isValid(i + 1, j, n) && maze[i + 1][j] == 0 && !visited[i + 1][j])
    {
        path.push_back('D');
        if (isSolvable(maze, path, visited, i + 1, j, n))
        {
            return 1;
        }
        path.pop_back();
    }

    if (isValid(i, j + 1, n) && maze[i][j + 1] == 0 && !visited[i][j + 1])
    {
        path.push_back('R');
        if (isSolvable(maze, path, visited, i, j + 1, n))
        {
            return 1;
        }
        path.pop_back();
    }

    if (isValid(i - 1, j, n) && maze[i - 1][j] == 0 && !visited[i - 1][j])
    {
        path.push_back('U');
        if (isSolvable(maze, path, visited, i - 1, j, n))
        {
            return 1;
        }
        path.pop_back();
    }

    if (isValid(i, j - 1, n) && maze[i][j - 1] == 0 && !visited[i][j - 1])
    {
        path.push_back('L');
        if (isSolvable(maze, path, visited, i, j - 1, n))
        {
            return 1;
        }
        path.pop_back();
    }
    // visited[i][j] = 0;
    return 0;
}
bool isValid(int i, int j, int n)
{
    if (i >= 0 && j >= 0 && i < n && j < n)
    {
        return 1;
    }
    return 0;
}

// 2) Using the directional loop with same logic :
string dir = "DRUL";
int row[4] = {1, 0, -1, 0};
int col[4] = {0, 1, 0, -1};
bool isSolvable2(vector<vector<int>> &maze, string &path, vector<vector<bool>> &visited, int i, int j, int n)
{
    if (i == n - 1 && j == n - 1)
    {
        return 1;
    }

    visited[i][j] = 1;

    for (int k = 0; k < 4; k++)
    {
        if (isValid(i + row[k], j + col[k], n) && maze[i + row[k]][j + col[k]] == 0 && !visited[i + row[k]][j + col[k]])
        {
            path.push_back(dir[k]);
            if (isSolvable2(maze, path, visited, i + row[k], j + col[k], n))
            {
                return 1; // Propagate success upwards without popping path
            }
            path.pop_back(); // Pop back only if this path failed
        }
    }
    // visited[i][j] = 1;
    return 0;
}

int main()
{
    vector<vector<int>> maze =
        {
            {0, 1, 0, 0, 0, 0},
            {0, 1, 0, 1, 1, 0},
            {0, 0, 0, 1, 0, 0},
            {0, 1, 1, 1, 0, 1},
            {0, 0, 0, 0, 0, 0},
            {1, 1, 0, 1, 0, 0}};

    if (maze[0][0] == 1 || maze[maze.size() - 1][maze.size() - 1] == 1)
    {
        cout << " There is no way to solve this ! " << endl;
        return 0;
    }

    string path = "";
    vector<vector<bool>> visited(maze.size(), vector<bool>(maze.size(), 0));

    if (isSolvable(maze, path, visited, 0, 0, maze.size()))
    {
        cout << " Path found ! : " << path << endl;
    }
    else
    {
        cout << " There is no way to solve this ! " << endl;
    }
    return 0;
}
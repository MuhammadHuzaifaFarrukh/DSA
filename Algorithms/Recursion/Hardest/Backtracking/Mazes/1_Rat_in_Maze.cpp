#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
Given a binary matrix maze[][] of size n × n containing values 0 and 1, find all possible paths for a rat to travel from the source cell (0, 0) to the destination cell (n - 1, n - 1).
The rat can move in four directions: up, down, left, and right.-> (U,D,L,R)
1 represents an open cell through which the rat can move.
0 represents a blocked cell that cannot be traversed.
The rat can move only through open cells and cannot visit the same cell more than once in a path. Return all valid paths as strings consisting of 'U', 'D', 'L', and 'R', representing the sequence of moves taken by the rat.
Note: Return the paths in lexicographically increasing order.
If no valid path exists, return an empty list.
*/

// Forward Declaration :
void total(vector<vector<int>> &maze, vector<vector<bool>> &visited, int i, int j, int n, string &temp, vector<string> &ans);

// 1) We use total() recursive function for this.
// Now we first check if the first or last entries are zero or not , because they need to be 1 for our journey.
// Then we require a visited matrix as well that will keep a track of the path that we visited along.
// If our i,j == n-1 then it means we have reached successfully to one answer and store it and then we return back.
// We keep visited[i][j] = 1 while exploring a new path.
// Then we need 3 conditions so we can call the function again.
// 1) The Path must not be out of bounds    2) It must not be a 0       3) It must not be visited.
// If these 3 are true then we call UP,DOWN,LEFT,RIGHT by the moves.
// We store one 'letter' in our temp array and then call the function again to explore the path.
// When we reach a deadend , only then we go back and undo our visited track record , and we also undo our temp stored answer.
// We keep checking if we can make any move out of 4 moves and if yes only then we explore that path.
// If not , then we backtrack to the previous state and again check for any further moves.
// When we have explored all the paths , then we return to our previous state and cannot make any further moves.
// Then we simply return.
// While using the DFS , we explore the path and keep exploring it until we reach deadend and then we backtrack.

// Time Complexity :
// At each stage , we have total 4 moves options.
// Total boxes are n by n.
// So we can say that time total is : O(4^(n^2))    (Can also be considered 3^(n^2) if we consider 3 moves on average).
// We can say it as O(3^(n^2)) because once we visit a cell , now we are on its neighbour and we just came from the previous cell so we cannot go on that in further moves so after visiting 1 cell , we can say that we have on average 3 moves.
// So this makes it almost 3 moves on each cell on average -> O(3^(n^2)) also fine cause this can be the tightest bound , O(4^(n^2)) is the loose upper bound.

// Space Complexity :
// We store a visited record track of size n by n -> O(n^2).
// We store a temp string which can go upto n by n for a very long path in case all entries are 1 inside our matrix.    -> O(n^2)
// Space : O(n^2)
// We store an answer array , if there are k valid paths , then each can be of size n^2 -> O(k*n^2)
// So total Space : O(k*n^2)
vector<string> ratInMaze(vector<vector<int>> &maze)
{
    vector<vector<bool>> visited(maze.size(), vector<bool>(maze.size(), 0));
    string path = "";
    vector<string> ans;
    if (maze[0][0] == 0 || maze[maze.size() - 1][maze.size() - 1] == 0)
    {
        return ans;
    }
    total(maze, visited, 0, 0, maze.size(), path, ans);
    return ans;
}

bool valid(int i, int j, int n)
{
    if (i >= 0 && j >= 0 && i < n && j < n)
    {
        return 1;
    }
    return 0;
}
void total(vector<vector<int>> &maze, vector<vector<bool>> &visited, int i, int j, int n, string &temp, vector<string> &ans)
{
    if (i == n - 1 && j == n - 1)
    {
        ans.push_back(temp);
        return;
    }
    visited[i][j] = 1;
    // Up -> i-1 , j        (-1,0)
    // Down -> i+1 , j      (1,0)
    // Left -> i,j-1        (0,-1)
    // Right -> i,j+1       (0,1)

    // Up
    if (valid(i - 1, j, n) && maze[i - 1][j] && !visited[i - 1][j])
    {
        temp.push_back('U');
        total(maze, visited, i - 1, j, n, temp, ans);
        temp.pop_back();
    }

    // Down
    if (valid(i + 1, j, n) && maze[i + 1][j] && !visited[i + 1][j])
    {
        temp.push_back('D');
        total(maze, visited, i + 1, j, n, temp, ans);
        temp.pop_back();
    }

    // Left
    if (valid(i, j - 1, n) && maze[i][j - 1] && !visited[i][j - 1])
    {
        temp.push_back('L');
        total(maze, visited, i, j - 1, n, temp, ans);
        temp.pop_back();
    }

    // Right
    if (valid(i, j + 1, n) && maze[i][j + 1] && !visited[i][j + 1])
    {
        temp.push_back('R');
        total(maze, visited, i, j + 1, n, temp, ans);
        temp.pop_back();
    }

    visited[i][j] = 0;
}

// 2) Same logic as above but improved code :
// Moves we have are (-1,0) , (1,0) , (0,-1) , (0,1)
// So we have first coordinate in each as : -1,1,0,0
// And 2nd coordinate : 0,0,-1,1
// Same Time and Space as (1)
int row[4] = {-1, 1, 0, 0};
int col[4] = {0, 0, -1, 1};
string dir = "UDLR";
void total2(vector<vector<int>> &maze, vector<vector<bool>> &visited, int i, int j, int n, string &temp, vector<string> &ans)
{
    if (i == n - 1 && j == n - 1)
    {
        ans.push_back(temp);
        return;
    }
    visited[i][j] = 1;
    for (int k = 0; k < 4; k++)
    {
        if (valid(i + row[k], j + col[k], n) && maze[i + row[k]][j + col[k]] && !visited[i + row[k]][j + col[k]])
        {
            temp.push_back(dir[k]);
            total2(maze, visited, i + row[k], j + col[k], n, temp, ans);
            temp.pop_back();
        }
    }
    visited[i][j] = 0;
}
int main()
{
    vector<vector<int>> v = {{1, 0, 0, 0},
                             {1, 1, 0, 1},
                             {1, 1, 1, 1},
                             {1, 1, 1, 1}};
    vector<string> ans = ratInMaze(v);
    cout << ans.size() << " Paths " << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << endl;
    }
    return 0;
}
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
using namespace std;

/*
There is a 1 million by 1 million grid on an XY-plane, and the coordinates of each grid square are (x, y).
We start at the source = [sx, sy] square and want to reach the target = [tx, ty] square. There is also an array of blocked squares, where each blocked[i] = [xi, yi] represents a blocked square with coordinates (xi, yi).
Each move, we can walk one square north, east, south, or west if the square is not in the array of blocked squares. We are also not allowed to walk outside of the grid.
Return true if and only if it is possible to reach the target square from the source square through a sequence of valid moves.

Input: blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
Output: false
Explanation: The target square is inaccessible starting from the source square because we cannot move.
We cannot move north or east because those squares are blocked.
We cannot move south or west because we cannot go outside of the grid.

Input: blocked = [], source = [0,0], target = [999999,999999]
Output: true
Explanation: Because there are no blocked cells, it is possible to reach the target square.
*/

// Forward Declarations :
bool isValid(int i, int j, int m, int n);
bool dfs(int i, int j, vector<int> &target, map<pair<int, int>, bool> &status, int &steps, int m, int n);
bool dfs2(int i, int j, vector<int> &target, unordered_set<long long> &status, int &steps, int m, int n);

// 1) By using DFS + Maps :
// Here we have an imaginary grid of size 1 mil by 1 mil.
// So we cannot allocate such an array because that will cause stack overflow and MLE as well.
// Instead we take unordered map and its key will be pair<x,y> with value visited or unvisited.
// But this still takes a lot of time.
// Now we are given that there will be at max 200 blocked cells. (constraints of LC)
// So the maximum blockage that can happen using 200 blocked cells is if they cover either the source / target by a diagonal margin like this :
//     0   1   2   3  . . 197 198 199 200
//   +-----------------------------------
// 0 | S   .   .   .  . .  .   .   .   X  <-- Block #1   (row 0, col 199)  -> 199 open cells
// 1 | .   .   .   .  . .  .   .   X   .  <-- Block #2   (row 1, col 198)  -> 198 open cells
// 2 | .   .   .   .  . .  .   X   .   .  <-- Block #3   (row 2, col 197)  -> 197 open cells
// . | .   .   .   .  . .  .   .   .   .
// 197| .   .   .   .  . .  X   .   .   .  <-- Block # 198  (row 197, col 2)  -> 2 open cells
// 198| .   .   X   .  . .  .   .   .   .  <-- Block # 199 (row 198, col 1)  -> 1 open cell
// 199| X   .   .   .  . .  .   .   .   .  <-- Block # 200  (row 199, col 0)  -> 0 open cells (seals corner)

// This is the maximum blockage that can occur is like this , it won't happen if it wraps around either the source / target in circle / square , although that might block , it won't give maximum blockage.
// So the maximum area inside a right triangle with legs of length 199 is:$$\text{Area} = \frac{199 \times 200}{2} = 19,900 \text{ cells}$$
// If we have a line of 200 blocked cells, they sit at positions:
// Block 1: (0, 199)
// Block 2: (1, 198)
// ...
// Block 200: (199, 0)

// Now look at row 0:
// The block is at column 199.
// That means columns 0 through 198 are open.
// Count of open cells in row 0 = 199 cells (which is B - 1).

// Every row down has 1 fewer open cell:
// Row 0: 199 open cells
// Row 1: 198 open cells
// Row 2: 197 open cells
// ...
// Row 198: 1 open cell
// Row 199: 0 open cells

// The Sum:
// Total Enclosed Open Cells = 199 + 198 + 197 + ... + 1 + 0

// Using the formula for the sum of numbers from 1 to 199:
// Sum = (199 * (199 + 1)) / 2 = (199 * 200) / 2 = 19,900 ~ 20000
// This means that if source (S) is trapped inside this triangle, DFS will visit at most 19,900 cells before running out of valid moves .
// It hits a dead end, finishes, and correctly reports false.
// So we only need to check that if source has reached target , and target reached source as well.
// If steps have reached more than 20000 , this means that source has found more than 20000 unique cells.
// We need to check for both i.e source->target and target->source.
// Because under normal cases source will reach target or tell us the answer if it is possible because it may or may not reach its coordinates.
// However if there are many blockages and too much distance between them , then we use the 20000 step case.
// Source needs to get past of these 20000 cells to be free but it may be possible that target is surrounded.
// OR Target may be free but source may not be free.
// So we need both of them to get past of their blocked steps to be free in case of huge distances and more blocked points.

// Also if we run a standard DFS on this , it would take 1 trillion cells.
// A standard computer executes roughly 10^8 operations per second.
// Traversing 10^12 cells would take over 2.7 hours for a single test case.
// Storing 10^12 elements in memory requires several Terabytes of RAM, causing an immediate out-of-memory crash.

// We don't backtrack , because if we find a path that is already leading us to a dead end , then if we come to that path again from another direction , it will still lead us to the dead end.
// So we don't unmark the blocks that we've already visited because those have been tried and didn't lead us to escape.
// If we unmark them , it gets our time to exponential with base 3.

// Compile with this :
// g++ "-Wl,--stack,67108864" -o solution.exe 70_Escaping_a_Large_Maze.cpp and then ./solution.exe

// Time Complexity :
/*
Step 1: Preprocessing Blocked Cells
Inserting B blocked cells into std::map takes O(B * log B) time because each insertion into a Red-Black tree takes O(log B) time.

Step 2: Performing DFS Search
The DFS runs for at most N steps (where N is bounded by 20000). At each step:
Checking if a coordinate is blocked or visited takes O(log(B + K)) time, where K is the number of visited cells so far.
Inserting the current coordinate into the map takes O(log(B + K)) time.
Across N steps, the upper bound for search and marking is O(N * log(B + N)).

Step 3: Total Time Complexity
Combining Phase 1 and Phase 2 gives:
Total Time Complexity = O(B * log B + N * log(B + N))
Since N is much larger than B (20000 versus 200), this simplifies to O(B * log B + N * log N).
Since DFS is called twice (from source to target, and target to source), total time remains O(B * log B + N * log N).


// Space Complexity :
Step 1: Explicit Data Structures (Map Storage)
The map stores at most B blocked cells and N visited cells.
Data Structure Space = O(B + N).

Step 2: Auxiliary Space (Recursion Call Stack)
In the worst case, DFS can go up to N levels deep before returning or hitting the 20000 step limit.
Maximum Call Stack Depth = N frames.
Auxiliary Space for Call Stack = O(N).

Step 3: Total Space Complexity
Total Space = Data Structure Space + Auxiliary Call Stack Space.

Total Space Complexity = O(B + N) + O(N) = O(B + N).
Each entry in std::map creates a dynamic Red-Black tree node containing left pointer, right pointer, parent pointer, color flag, and the key-value pair, leading to high memory overhead per element.
*/
bool isEscapePossible(vector<vector<int>> &blocked, vector<int> &source, vector<int> &target)
{
    if (source == target)
    {
        return 1;
    }
    map<pair<int, int>, bool> status;
    for (int i = 0; i < blocked.size(); i++)
    {
        status[{blocked[i][0], blocked[i][1]}] = 1;
    }
    map<pair<int, int>, bool> copy = status;

    int stepsSource = 0;
    int stepsTarget = 0;
    bool canSource = dfs(source[0], source[1], target, status, stepsSource, 1000000, 1000000);
    bool canTarget = dfs(target[0], target[1], source, copy, stepsTarget, 1000000, 1000000);
    return (canSource && canTarget);
}

bool dfs(int i, int j, vector<int> &target, map<pair<int, int>, bool> &status, int &steps, int m, int n)
{
    if (i == target[0] && j == target[1])
    {
        return 1;
    }
    if (steps > 20000)
    {
        return 1;
    }
    if (status.count({i, j}))
    {
        return 0;
    }
    status[{i, j}] = 1;
    steps++;

    // All moves :
    if (isValid(i - 1, j, m, n) && status.count({i - 1, j}) == 0)
    {
        if (dfs(i - 1, j, target, status, steps, m, n))
        {
            return 1;
        }
    }

    if (isValid(i + 1, j, m, n) && status.count({i + 1, j}) == 0)
    {
        if (dfs(i + 1, j, target, status, steps, m, n))
        {
            return 1;
        }
    }

    if (isValid(i, j - 1, m, n) && status.count({i, j - 1}) == 0)
    {
        if (dfs(i, j - 1, target, status, steps, m, n))
        {
            return 1;
        }
    }

    if (isValid(i, j + 1, m, n) && status.count({i, j + 1}) == 0)
    {
        if (dfs(i, j + 1, target, status, steps, m, n))
        {
            return 1;
        }
    }

    // No need to backtrack since visiting them once is enough , if we visit them again via a different path , that only increases time.
    // status[{i, j}] = 0;
    // steps--;

    return 0;
}

bool isValid(int i, int j, int m, int n)
{
    if (i >= 0 && j >= 0 && i < m && j < n)
    {
        return 1;
    }
    return 0;
}

// 2) By using DFS + Unordered Set :
// Same logic as above , but this time we use unordered set.
// Unordered set cannot keep pair so we need a way to enclose our (i,j) in 1 number.
// To pack to 32 bit integers into 64 bit long integers , we use encoding using bitwise operations.
// 1 million requires 20 bits , so i and j can at worst have 1 millionth coordinates values.
// So we left shift i by 20 and take its Bitwise OR with j so we can place j as well in a single number.
// Bits 20 to 63:  [ Stores row index 'i' ]
// Bits 0 to 19:   [ Stores col index 'j' ]
// Suppose i = 5 and j = 9:
// i = 5 in binary 101
// i << 20  10100000000000000000000 (shifted 20 spots to the left)
// j = 9 in binary 1001
// (i << 20) | j  10100000000000000001001
// This creates one single long long key that represents (5, 9) perfectly without needing any string conversion or pair-hashing overhead

// Compile with this :
// g++ "-Wl,--stack,67108864" -o solution2.exe 70_Escaping_a_Large_Maze.cpp and then ./solution2.exe

// Time Complexity :
// Step 1: Preprocessing Blocked Cells
// Inserting B blocked cells into std::unordered_set takes O(B) average time because each insertion into a hash table takes O(1) average time.

// Step 2: Performing DFS Search
// The DFS runs for at most N steps (where N is bounded by 20000). At each step:
// Converting coordinates to a long long key using bit-shifting takes O(1) time.
// Checking if a key exists in std::unordered_set takes O(1) average time.
// Inserting the key into std::unordered_set takes O(1) average time.
// Total time for N steps = O(N).

// Step 3: Total Time Complexity
// Combining Phase 1 and Phase 2 gives:
// Total Time Complexity = O(B + N) average time.
// Executing the search twice (source to target and target to source) keeps the complexity at O(B + N).

// Space Complexity :
// Step 1: Explicit Data Structures (Set Storage)
// The unordered_set stores at most B blocked cells and N visited cells as long long primitive integers.
// Data Structure Space = O(B + N).

// Step 2: Auxiliary Space (Recursion Call Stack)
// In the worst case, DFS reaches a depth of up to N recursive function calls.
// Maximum Call Stack Depth = N frames.
// Auxiliary Space for Call Stack = O(N).

// Step 3: Total Space Complexity
// Total Space = Data Structure Space + Auxiliary Call Stack Space.
// Total Space Complexity = O(B + N) + O(N) = O(B + N).
// Note on Overhead: Using long long values in std::unordered_set stores flat integers directly in bucket arrays, eliminating node pointer overhead and using far less memory than std::map.
long long getKey(long long i, long long j)
{
    return (i << 20) | j;
}

bool isEscapePossible2(vector<vector<int>> &blocked, vector<int> &source, vector<int> &target)
{
    if (source == target)
    {
        return 1;
    }

    unordered_set<long long> status;
    for (int i = 0; i < blocked.size(); i++)
    {
        status.insert(getKey(blocked[i][0], blocked[i][1]));
    }

    unordered_set<long long> copy = status;

    int stepsSource = 0;
    int stepsTarget = 0;

    bool canSource = dfs2(source[0], source[1], target, status, stepsSource, 1000000, 1000000);
    bool canTarget = dfs2(target[0], target[1], source, copy, stepsTarget, 1000000, 1000000);

    return canSource && canTarget;
}

bool dfs2(int i, int j, vector<int> &target, unordered_set<long long> &status, int &steps, int m, int n)
{
    if (i == target[0] && j == target[1])
    {
        return 1;
    }
    if (steps > 20000)
    {
        return 1;
    }

    long long key = getKey(i, j);
    status.insert(key);
    steps++;

    if (isValid(i - 1, j, m, n) && status.count(getKey(i - 1, j)) == 0)
    {
        if (dfs2(i - 1, j, target, status, steps, m, n))
        {
            return 1;
        }
    }

    if (isValid(i + 1, j, m, n) && status.count(getKey(i + 1, j)) == 0)
    {
        if (dfs2(i + 1, j, target, status, steps, m, n))
        {
            return 1;
        }
    }

    if (isValid(i, j - 1, m, n) && status.count(getKey(i, j - 1)) == 0)
    {
        if (dfs2(i, j - 1, target, status, steps, m, n))
        {
            return 1;
        }
    }

    if (isValid(i, j + 1, m, n) && status.count(getKey(i, j + 1)) == 0)
    {
        if (dfs2(i, j + 1, target, status, steps, m, n))
        {
            return 1;
        }
    }

    return 0;
}

// 3) Using BFS for this is a great Win in terms of Space.
int main()
{
    vector<vector<int>> blocked = {{0, 1}, {1, 0}};
    vector<int> source = {0, 0};
    vector<int> target = {1, 2};

    if (isEscapePossible2(blocked, source, target))
    {
        cout << "Escape is Possible " << endl;
    }
    else
    {
        cout << "Escape Not Possible " << endl;
    }
    return 0;
}
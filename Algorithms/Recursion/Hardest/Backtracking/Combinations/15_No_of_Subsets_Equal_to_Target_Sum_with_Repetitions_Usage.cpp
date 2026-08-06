#include <iostream>
#include <vector>

using namespace std;

// Given a vector of positive integers , we need to see if any subset equals target or not.
// Repetition is allowed , meaning we can reuse the same number more than once.
// If yes then return true otherwise false.
// E.g : (2,3,4) with target = 6 , then we can have pairs : (2,2,2) , (3,3) , (2,4) , 3 pairs
// We want to generate all the possible choices with repetition usage , means we can use the same number.

// Again we generate all the subsets (combinations) using recursion.
// We call 2 functions for 2 branches with OR so that any branch that gives us true will be considered as a YES answer.
// We call 1 function same as it is with next index which indicates that we didn't take this sum as our choice.
// We call 1 function same as it is with next index and target - this number which indicates that we took this sum as our choice.
// If our target becomes 0 , it means we found the target and return 0.
// If it becomes negative then there is no point of finding further as we are gonna encounter positives only.

// Time : O(2^(T/M + N)) or O(N^(T/M))
// Space : O(T/M + N)
int find(vector<int> &arr, int index, int n, int target)
{
    if (target == 0)
    {
        return 1;
    }
    if (index == n || target < 0)
    {
        return 0;
    }
    return (find(arr, index + 1, n, target)) + (find(arr, index, n, target - arr[index]));
}

// If this vector allowed negatives and zero also then we need to handle these constraints in our input because we cannot handle negatives or zeroes here cause that will induce infinite recursion.

int main()
{
    vector<int> v = {2, 3, 4};
    int target = 6;
    cout << " Targets : " << find(v, 0, v.size(), target) << endl;
    return 0;
}

// Finding Time and Space Complexity :
/*
Assuming that all elements in arr are strictly positive integers (arr[i] > 0) (which is required to prevent the infinite loops we just discussed), let's calculate the exact worst-case time and space complexity of this Unbounded Knapsack / Combination Sum algorithm.

Let:
N be the size of the array (n).
T be the target value.
M be the minimum element in the array (M = minimum value in arr).

1. Time Complexity: O(2^(T/M + N)) or O(N^(T/M))
Because you can reuse the same element infinitely, the recursion tree does not have a fixed depth of N. Instead, the depth is determined by how many times we can subtract the smallest element (M) from the target (T) before it drops below 0.

The Recursion Tree Analysis
At any state in your recursion, you have 2 choices:
Exclude (Skip): Move to the next index (index + 1).
Include (Take): Stay at the same index (index) and subtract arr[index] from target.
Maximum depth of the "Take" branch: In the absolute worst case (where we keep taking the smallest element M), we can go down a depth of up to T/M levels.
Maximum depth of the "Skip" branch: We can only skip N times before we run out of elements (index == n).
Therefore, the maximum height of the recursion tree is:
Max Height = H = T/M + N
Since every node in the recursion tree splits into 2 branches (binary tree), the upper bound for the total number of states visited is:
O(2^(T/M + N))
(Note: If T is very large compared to N, a tighter mathematical bound for the number of leaves is often written as O(N^(T/M)) because we can make at most T/M decisions to "take" among the N choices).

2. Space Complexity: O(T/M + N)
The space complexity of a recursive algorithm is determined by the maximum depth of the recursion call stack at any given moment.
As analyzed above:
The longest possible path in the recursion tree occurs when we continuously take the smallest element M until the target becomes negative, and then skip all remaining elements to hit index == n.
The maximum stack frames active at once will be the height of this deepest path:
Max Stack Depth = T/M + N
Thus, the auxiliary space complexity is:
O(T/M + N)
*/
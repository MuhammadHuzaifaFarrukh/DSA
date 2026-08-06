#include <iostream>
#include <vector>

using namespace std;

/*
You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
Return the number of combinations that make up that amount. If that amount of money cannot be made up by any combination of the coins, return 0.
You may assume that you have an infinite number of each kind of coin.
The final answer is guaranteed to fit into a signed 32-bit integer.

// Example :
Input: amount = 5, coins = [1,2,5]
Output: 4
Explanation: there are four ways to make up the amount:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
*/
// This problem is like No of subsets sum equal target with repetition number usage allowed.

//
// We have to take again two choices.
// Yes -> Keep this number and stay on the same index.
// No -> Skip this number and go to next index.
// We keep doing this for all combinations , until the amount becomes 0.
// If amount becomes less than 0 , or we go out of index , only then we stop and backtrack.

/*
Time Complexity: O(2^(N + (T / C_min)))
Because this is a raw recursive function without memoization, it explores every single branch of choices until it overshoots the target or runs out of coins.
The Take Choice (index stays the same):
We can repeatedly take the same coin. In the worst-case scenario (e.g., you have a coin of value 1), we can take it a maximum of (T / C_min) times before target < 0 triggers a return.
The Skip Choice (index + 1): You can skip a coin at most N times before running out of coins (index == coins.size()).
At each step, the algorithm makes a binary split (Take vs. Skip).
The maximum depth of this massive tree is bounded by N + (T / C_min).
Since a binary tree of depth D has up to 2^D nodes, the raw time complexity is: O(2^(N + (T / C_min)))
*/
// Total Time comp if simplified or approxed : O(2^n)

/*
Space :
In the worst-case path, the computer will keep taking the smallest coin over and over again until the target drops below 0.
This chain of "Take" calls creates a call stack depth proportional to the maximum depth of the tree, which is N + (T / C_min).
Space = O(N + (T / C_min))
No additional vector or without reference used so :
Total Space: O(N + (T / C_min))
// Total Space if we just say approx or simplified : O(n)
*/
int change(vector<int> &arr, int index, int n, int target)
{
    if (target == 0)
    {
        return 1;
    }
    if (index == n || target < 0)
    {
        return 0;
    }
    return (change(arr, index + 1, n, target)) + (change(arr, index, n, target - arr[index]));
}

int main()
{
    vector<int> v = {1, 2, 5};
    int target = 11;
    cout << "No of combinations to make the target of " << target << " with this array are : " << change(v, 0, v.size(), target) << endl;

    return 0;
}
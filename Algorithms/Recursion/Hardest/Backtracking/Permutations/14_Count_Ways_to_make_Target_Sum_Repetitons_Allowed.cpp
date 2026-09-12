#include <iostream>
#include <vector>

using namespace std;

/*
Given an array of distinct integers nums and a target integer target, return the number of possible combinations that add up to target.
Input: nums = [1,2,3], target = 4
Output: 7
Explanation:
The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
Note that different sequences are counted as different combinations.
*/
// This is like permutation with repetition number usage allowed.

// We cannot use swapping logic of permutation.
// We use that only when dealing with Distinct/No Repetition permutations where we are simply reordering a fixed set of items.
// We use the logic of permutation with repetition allowed.
// For normal permutation we always sent an index to fix our elements at each index.
// But now we start our for loop each time from i = 0 to i < n.
// We are trying all the possible arrangements.
// At each stage we fix no position.
// We can select any of the array element.
// Say (1,5,6) with target = 7.
// Then at first level , we have 3 choices 1,5,6.
// When we select 1 , we have again 3 choices , 1,5,6.
// When we select 5 or 6 for first level , we still have 3 choices 1,5,6.
// On the 2nd level , when we selected 1,1, we still have 3 choices 1,5,6.
// This means that at any level , we have n choices.
// This tree goes way down until it reaches sum == 0.
// When it does , we return 1.
// If sum reaches negative , it means we cannot find our sum ahead so we need to return 0.
// We add up all the ways gained.

/* The stopped branches mean that their sum was negative
                                                                                                    (1,5,6)
                                                                                /                       |                      \
                                                                            (1+)                      (5+)                    (6+)
                                                                    /       |  \                    /  |   \                /  |   \
                                                                (1+1)       (1+5) (1+6)           (5+1) (5+5) (5+6)       (6+1) (6+5) (6+6)
                                                            /   |    \      /  |  \                /   |  \
                                                (1+1+1) (1+1+5) (1+1+6) (1+5+1) (1+5+5) (1+5+6) (5+1+1) (5+1+5) (5+1+6)
                                        /  |      \
                                (1+1+1+1) (1+1+1+5) (1+1+1+6)
                                    /    |    \
                                (1+1+1+1+1)  (1+1+1+1+1+5) (1+1+1+1+1+6)
                            /  |           \
                (1+1+1+1+1+1) (1+1+1+1+1+5) (1+1+1+1+1+6)
            /         |       \
    (1+1+1+1+1+1+1) (1+1+1+1+1+5) (1+1+1+1+1+6)
*/

/*
Time Complexity: O(n^(T / min_val))
Since we are allowed to reuse any number infinitely, our recursion tree branches out by a factor of n at every single level.
How deep does the tree go?
The tree stops growing when targetSum less than 0 or targetSum == 0. The absolute longest possible path down the tree happens when we continuously pick the smallest positive number in our array (min_val). The maximum depth (D) of the tree will be: D = T / min_val.
How many nodes are generated?
At every level of the tree, we have n choices.
Level 1 has n nodes.
Level 2 has n^2 nodes.
Level D has n^D nodes.
Summing up all the work across the tree, our total time complexity is bounded by O(n^(T / min_val)).
This is purely exponential time.

Space Complexity: O(T / min_val)
Our code doesn't use any auxiliary data structures (no vectors, no strings, no hash maps). The only memory consumed is our recursive call stack.
As calculated above, the absolute deepest our call stack can ever get before hitting a base case (targetSum less than or equal to 0) is when the recursion repeatedly subtracts the smallest element in our array.
Therefore, our maximum stack depth is T / min_val, giving us a space complexity of O(T / min_val).
Space : O(T / min_val)
*/
int ways(vector<int> &nums, int n, int targetSum)
{
    if (targetSum == 0)
    {
        return 1;
    }
    if (targetSum < 0)
    {
        return 0;
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans += ways(nums, n, targetSum - nums[i]);
    }
    return ans;
}
// 1) If we want to allow any negatives or zero in this case then we need to fix a maximum length constraint as well otherwise it would be impossible to check where to stop.
// Whole code remains same.
// When target becomes zero , that's one way.
// When our currentSize becomes == maxLength then its time to backtrack.
/*
int waysWithMaxSize(vector<int> &nums, int n, int targetSum, int currentSize, int k)
{
    int ans = 0;
    if (targetSum == 0 && currentSize > 0)
    {
        ans = 1;
    }

    // MAX SIZE BOUNDARY: If we have reached our maximum allowed sequence length,
    // we physically cannot pick any more numbers. We stop the recursion here.
    if (currentSize == k)
    {
        return ans;
    }

    for (int i = 0; i < n; i++)
    {
        // Pass down the updated sum, increment our current size by 1, and keep the max size limit
        ans += waysWithMaxSize(nums, n, targetSum - nums[i], currentSize + 1, maxSize);
    }

    return ans;
}
// We call it as :
vector<int> nums = {1, -1, 0, 2};
int n = nums.size();
int targetSum = 2;
int maxSize = 4; // We decide the maximum length of the permutation
// Start currentSize at 0
int totalWays = waysWithMaxSize(nums, n, targetSum, 0, maxSize);
*/
// Time : O(n^k) where k is the maxsize and space : O(k)

// ===============================================================================================================================================================================================

// 2) For doing exact 'k' and negatives , positives , zero allowed with repeated permutation then we just need 1 base case i.e to check the length = k and only then we check sum.
/*
if (currentSize == k)
{
    Only grade the sum now that we are exactly at size k
    return (targetSum == 0) ? 1 : 0;
}
*/
// Time : O(n^k) where k is the maxsize and space : O(k)
// These 3 follow-ups are the cleanest, most bulletproof way to handle negatives, zeros, and sizes is to keep our checks at the very top of the function call (acting as a net) rather than scattering conditions inside the loop body.

int main()
{
    vector<int> v = {1, 5, 6};
    int sum = 7;
    cout << "Ways to make Target Sum " << sum << " : " << ways(v, v.size(), sum) << endl;
    return 0;
}
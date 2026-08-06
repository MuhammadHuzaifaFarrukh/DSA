#include <iostream>
#include <vector>

using namespace std;
/*
Given an array of distinct integers nums and a target integer target, return the number of possible combinations that add up to target.
Input: nums = [1,5,6], target = 7
Output: 2
Explanation:
The possible combination ways are:
(1,6) and (6,1)
*/
// This is Permutations but without repetition usage.

// We just use the same permutations logic without repetition.
// At each step we fix our index and then we also check if our target becomes zero or not.
// If it does it means we found a way.
// If the sum becomes negative , it means there is no way our sum can be found now.

// Time :
// At worst the target may be massive and all elements are ver small so it finds all the permutations of size n.
// Therefore it will take time O(n*n!)

// Space :
// At worst the target may be massive and all elements are ver small, so our stack depth goes upto maximum of 'n' for permutations of size n.
// And there is no extra space being used other than small variables.
// So our space is O(n)

int ways(vector<int> &nums, int n, int index, int targetSum)
{
    // int ans = 0, no issue
    if (targetSum == 0)
    {
        return 1;
    }
    if (targetSum < 0)
    {
        return 0;
    }
    // We may or may not write index == n cause this is handled by our for loop.

    int ans = 0;
    for (int i = index; i < n; i++)
    {
        swap(nums[i], nums[index]);
        ans += ways(nums, n, index + 1, targetSum - nums[index]);
        swap(nums[i], nums[index]);
    }
    return ans;
}
// 1) If our code allowed negatives and zero then we would check the base case as :
/*
If our array has zeros and negative numbers, we cannot return 1 early the absolute second (targetSum - nums[index] == 0) inside the loop.
Why? Because a zero or a matching positive/negative pair later in the array could form a completely separate, longer permutation that also sums to your target!
We could also put the extra base cases at the top of function instead of checking inside the for loop and keep index == n  just for returning :
int ans = 0;
if (targetSum == 0 && index > 0)
{
    ans = 1;
}
if (index == n)
{
    return ans;
}
*/
// This takes time O(n*n!) and Space : O(n)

// ========================================================================================================================================================================

// 2) If our code allowed negatives and zero and also had a constraint of checking upto of size 'k' of nPk not exact 'k'  instead of here doing all nP0 , nP1 , ... , nPn.
// We use the same base cases as above and change n to k.
// 
/*
int ans = 0;
if (targetSum == 0 && index > 0)
{
    ans = 1;
}
// Once we hit our maximum allowed elements (k).
// we return the running ans accumulated at this spot and stop diving deeper.
if (index == k)
{
    return ans;
}
*/
// This also takes time O(n*n!) and Space : O(n)

// ========================================================================================================================================================================

// 3) If our code allowed negatives and zero and also had a constraint of checking exact of size 'k' of nPk instead of here doing all nP0 , nP1 , ... , nPn.
// So then we would put this extra base case and keep index == n  just for returning :
/*
if (index == k)
{
    // Now we check if this specific k-sized permutation hits our target
    return (targetSum == 0);
}
*/
// This also takes time O(n*n!) and Space : O(n)
// Doing it in a for-loop would make it messy and error-prone.
// These 3 follow-ups are the cleanest, most bulletproof way to handle negatives, zeros, and sizes is to keep our checks at the very top of the function call (acting as a net) rather than scattering conditions inside the loop body.

int main()
{
    vector<int> v = {1, 5, 6};
    int target = 7;
    cout << "Number of ways to make the target " << target << " : " << ways(v, v.size(), 0, target) << endl;
    return 0;
}
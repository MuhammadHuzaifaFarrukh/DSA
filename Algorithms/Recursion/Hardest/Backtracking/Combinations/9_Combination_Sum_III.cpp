#include <iostream>
#include <vector>
using namespace std;
/*
Find all valid combinations of k numbers that sum up to n such that the following conditions are true:

Only numbers 1 through 9 are used.
Each number is used at most once.
Return a list of all possible valid combinations. The list must not contain the same combination twice, and the combinations may be returned in any order.

// Example :
Input: k = 3, n = 7
Output: [[1,2,4]]
Explanation:
1 + 2 + 4 = 7
There are no other valid combinations.
*/
// We have to specifically get nCk sums and without any repetition.

// This problem statement is actually the same combination problem of nCk.
// They are saying to use only 1-9 numbers so we can create an array with numbers 1-9 and go for all their combinations.
// We have to generate all the combinations of size 'k'.
// We again do the same question , choice of yes , means selecting this value as our sum and moving to next index.
// OR we don't choose it and skip over to the next number.

// Time Complexity :
/*
The recursion tree can only ever look at 9 elements.
Each element has 2 choices (Take or Skip).
The absolute maximum number of leaves our recursion tree can ever visit is 2^9= 512.
Because 512 is a constant number that never changes based on our input, the time complexity is O(1).

// If nums could be any size n, our code behaves like a pure combination generator capped at size k.
The maximum number of valid combinations of size k out of n elements is nCk.
// But it could go even higher depending on pruning.
// If we don't write the pruning condition , it becomes 2^n choices , and n*2^n for pushbacks included.

*/
// Time : O(1)

// Space Complexity :
// Since we made our vector 1-9 , the recursive depth of stacks can only be upto 1-10 , fixed.
// How many combinations can actually sum up to n with length k?
// The maximum possible number of unique combinations we could ever generate from 1 to 9 is 9Ck .
// The largest this coefficient can get is when k=4 or 5, which yields exactly 9C4 = 126 rows.
// Each row stores at most k integers (max 9).
// Since our output array arr will never hold more than 126 * 5 = 630 integers in the absolute worst case, the total space complexity is also completely bounded at O(1).
// Space : O(1)
void CombinationsSum3(vector<int> &nums, int n, int k, int index, vector<vector<int>> &arr, vector<int> &temp)
{
    if (temp.size() == k)
    {
        if (n == 0)
        {
            arr.push_back(temp);
        }
        return;
    }
    if (n < 0 || index == nums.size())
    {
        return;
    }
    CombinationsSum3(nums, n, k, index + 1, arr, temp);
    temp.push_back(nums[index]);
    CombinationsSum3(nums, n - nums[index], k, index + 1, arr, temp);
    temp.pop_back();
}

int main()
{
    int n = 9, k = 3;
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<vector<int>> arr;
    vector<int> temp;
    CombinationsSum3(nums, n, k, 0, arr, temp);
    return 0;
}
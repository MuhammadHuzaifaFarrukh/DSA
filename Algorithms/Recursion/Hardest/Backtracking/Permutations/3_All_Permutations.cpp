#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
// We want to find the all nPk for a given array / vector.
// If we are given {1,2,3,4} ,then we have to find 4P0 + 4P1 + 4P2 + 4P3 + 4P4.
// Total Permutations : en! where e is euler's constant.
// Any nPk is partial Permutation while nPn are full permutations.
*/

// 1) We can just try our specific nPk and run a loop from k = 0 to k = n.
// This takes total time O(n^2*n!) and Space : O(n*n!)

// 2) This method where we just run our recursion by using nPn , we can actually get all the nP0 and all other permutations , by going inside our for loop and saving answer right before recursion.
// We apply the same swapping method.
// Now when we are finding the permutations of (1,2,3,4) , we first fix (1) then we fix (1,2) , then we fix (1,2,3) and finally we fix (1,2,3,4).
// So usually we save this (1,2,3,4) for our nPn permutation , but now for all the permutations , we will save the permutation fix at each step.
// Also we will save the 'k' elements at that time otherwise saving the whole nums we will see (1,2,3,4) 4 times instead of (1),(1,2),(1,2,3) and (1,2,3,4).
// This takes time O(n*n!) and Space : O(n*n!)
void PermutationsAllK(vector<int> &nums, vector<vector<int>> &ans, int index)
{
    // Base case is just the physical end of the array (nPn)
    if (index == nums.size())
    {
        return;
    }

    for (int i = index; i < nums.size(); i++)
    {
        swap(nums[i], nums[index]);

        vector<int> current_slice(nums.begin(), nums.begin() + index + 1);
        ans.push_back(current_slice);
        PermutationsAllK(nums, ans, index + 1);
        swap(nums[i], nums[index]);
    }
}

int main()
{
    vector<int> v = {1, 2, 3, 4};
    vector<vector<int>> ans;
    PermutationsAllK(v, ans, 0);

    for (int i = 0; i < ans.size(); i++)
    {
        for (int j = 0; j < ans[i].size(); j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

// Recurrence Relation :
/*
For this problem, the work depends on the number of elements we have left to look at in our loop. Let's use m to represent the remaining elements from our current index to the end of the array, where m = nums.size() - index.
When we call the function, our loop runs exactly m times. During each iteration of that loop, we perform our constant-time swaps and then make a recursive call to the next index, which drops our remaining pool of numbers from m down to m - 1.
Because the loop executes m times and drives the branching process, our recurrence relation for a normal step is:
T(m) = m * T(m - 1) + O(m)
Here, the O(m) term directly represents the cost of the loop running m times at this specific level.
The Base Case
When m = 0 (meaning our index has reached the end of the array), our code hits the top condition and returns immediately.
T(0) = O(1)

Unrolling to Find the Total Complexity
When we look at how this tree branches out, the loop at the very top level runs n times. Each of those branches creates a loop that runs n - 1 times, and so on.
When you sum up the total number of times the loop body executes across every single level of the entire recursion tree, it perfectly accumulates to a total count of operations that is proportional to n * n-factorial.

So, by simply counting the work done by the loop traversals as we move down the nodes of the tree, we get our final time complexity:
Total Time Complexity = O(n * n-factorial)
*/
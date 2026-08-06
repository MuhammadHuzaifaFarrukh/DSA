#include <iostream>
#include <vector>

using namespace std;
/*
We are given an array and we have to generate its permutations for size 'k' where 'k' can be much larger than array size.
Our array: nums = [1, 2] (size n = 2)
Our target length: k = 3
All Repeated Permutations of Length 3
[1, 1, 1]
[1, 1, 2]
[1, 2, 1]
[1, 2, 2]
[2, 1, 1]
[2, 1, 2]
[2, 2, 1]
[2, 2, 2]
*/
// This is repeated permutations meaning we can use any number any number of times until a length 'k'.
// Repeated Permutations P(n,k) = n^k.
// For (1,2) with k = 3 , we can put in our formula : n=2,k=3, 2^3 = 8 unique permutations.
// For finding all the permutations from 0 to k length : n^0 + n^1 + n^2 +...+ n^k we have formula : n*(n^k-1)/ (n-1)

// We cannot use swapping logic here.
// We use that only when dealing with Distinct/No Repetition permutations where we are simply reordering a fixed set of items.
// Here we use our temp vector logic.
// Making repeated permutations , we don't fix index because now we have all the choices at all levels.
// Our repeated recursion goes upto length 'k'.
// So our base case is that when our temporary vector becomes 'k'.
// We also don't need to use any visited array because we can use any number at any level.

/*
Time Complexity: O(n^k)
At every single level of our recursion tree, our loop runs exactly n times because we are allowed to choose any element from our pool.
Level 1 has n branches.
Level 2 has n^2 branches.
Level k has n^k leaf nodes where we reach the base case.
Since the tree grows up to depth k, the total number of states visited is n^1 + n^2 + ...+ n^k, which simplifies to O(n^k).
(Note: If we print or copy the full permutation at the base case, the time would become O(k * n^k), but for the raw traversal shown, it is O(n^k)).

Space Complexity: O(k)
Our space complexity is determined by two things:
The Call Stack: The recursion goes down exactly k levels deep before hitting the base case and turning around.
This takes O(k) space.
Our current_permutation vector grows up to a maximum size of k elements.
Since both variables scale linearly with our target length, our total space complexity is O(k).
*/
void PermuteRep(vector<int> &nums, int k, int currentLength, vector<int> &temp)
{
    // Base Case : Once our current permutation reaches size k, we stop!
    if (currentLength == k)
    {
        for (int i : temp)
        {
            cout << i << " ";
        }
        return;
    }

    for (int i = 0; i < nums.size(); i++)
    {
        temp.push_back(nums[i]);
        // We can also print or save the answer of our temp vector , so that it generates all the permutations , not just length 'k' and our base case would still be same but only return when it appears.
        // ans.push_back(temp);

        // Recurse deeper and increase our length tracker by 1
        PermuteRep(nums, k, currentLength + 1, temp);
        temp.pop_back(); // Backtrack
    }
}

int main()
{
    vector<int> v = {1, 2, 3};
    vector<int> temp;
    int k = 4;
    PermuteRep(v, k, 0, temp);
    return 0;
}

// Recurrence Relation :
/*
The Repetition Recurrence Relation
For this problem, the work depends on how many slots we still have left to fill in our current permutation before we hit our target size k. Let's use r to represent these remaining slots, where r = k - currentLength. Let's also use n to represent the total number of unique elements available in our nums array (nums.size()).
When we call the PermuteRep function, our loop always runs exactly n times because we start from i = 0 every single time to allow repetition. Inside that loop, we push an element into temp, make a recursive call that fills 1 slot (reducing our remaining slots from r down to r - 1), and then pop it back out.
Because the loop runs exactly n times and spawns n separate recursive branches at every single step, our recurrence relation for a normal step is:
T(r) = n * T(r - 1) + O(n)

The O(n) term represents the fixed overhead of running our loop n times at the current level.

The Base Case
When r = 0 (which means our currentLength has reached k), we hit our base case at the top of the function. Inside this base case, we run a loop to print out all the elements currently inside our temp vector.
Since our temp vector has exactly k elements at this point, printing them out takes O(k) time.
So, the exact time taken at the base case is:
T(0) = O(k)
Unrolling the Relation to Find Complexity
If we look at how this tree branches out, it builds a perfectly balanced, uniform tree:

At the top level, we have n choices, creating n branches.
At the next level down, every single one of those branches creates another n choices, making n * n branches.
This multiplying continues for exactly k levels until we reach the bottom of the tree.
By the time we hit the base case at the bottom of the tree, we have generated a total of n raised to the power of k leaf nodes.
At each of those leaf nodes, we spend O(k) time running our loop to print the answer.
Putting together the work done by the loops at every level of the tree, the overall time complexity works out to:

Total Time Complexity = O(k * (n^k))
*/
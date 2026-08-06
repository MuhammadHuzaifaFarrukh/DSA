#include <iostream>
#include <vector>

using namespace std;

/*
Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].
You may return the answer in any order.
Input: n = 4, k = 2
Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
Explanation: There are 4 choose 2 = 6 total combinations.
Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to be the same combination.
// Here it is mentioned to give only specific combinations , like nCk not all the combinations like power set and without any repetitions.
*/
// The General Formula of Combinations nCk is : n! / (k!*(n-k)!).

// We want to generate all the combinations of n , [1,n] such that there length is 'k'.
// We use Include / Exclude again.
// We come and ask if we want to take a number or not.
// For yes , we push it into temp vector and again call the same function with next index.
// For no , we just call the same function with next index without pushing it into temp vector.
// This allows it to explore all the combinations of nCk.
// When the length of any pair reaches 'k' , we stop there and save our answer.
// If the value goes beyond the 'n' , then we just backtrack.

// Time Complexity :
/*
When we are asking for choices , our structure represents that of a binary tree with yes or no.
So we are recursively asking if we should take this number or not.
This continues till approx length 'n'.
We see that at each level , the nodes increase : 1,2,4,8,16,...
And time taken in all nodes is like constant.
So our total time is O(2^n) or O(n*2^n) if we added pushback time also.
If we used the condition to eliminate the dead ends which waste our time , then time comp would be : O(nCk) or O(k*nCk) if we added pushback time also.
*/

// Space Complexity :
/*
Our tree's depth goes upto 'n' call stacks at max.
Our temp stores only at most 'k' numbers.
So Space is O(n+k) = O(n)
But anwer vector stores 2^n or nCk each of size 'k'.
So answer takes O(k*nCk) size.
Total Space : O(n) + O(k*nCk) = O(k*nCk)
*/

void Combinations(int n, int k, int val, vector<vector<int>> &arr, vector<int> &temp)
{
    if (temp.size() <= k && temp.size() > 0)
    {
        arr.push_back(temp);
        // return;
    }

    // Base Case 2: Out of bounds, OR we don't have enough numbers left to reach 'k'
    // (e.g., if we need 3 more numbers but only 1 remains between val and n, we stop)
    if (val > n || temp.size() + (n - val + 1) < k) // temp.size() + (n - val + 1) < k condition only saves a little branching , it doesn't affect output if we don't write it.
    {
        return;
    }

    // Choice 1: Take the current number (val)
    temp.push_back(val);
    Combinations(n, k, val + 1, arr, temp);
    temp.pop_back(); // Backtrack to restore the state

    // Choice 2: Skip the current number (val)
    Combinations(n, k, val + 1, arr, temp);

    // If we used for loop , then we don't need the 2nd base case.
    /*
    for (int i = val; i <= n; i++)
    {
        temp.push_back(i);
        Combinations(n, k, i + 1, arr, temp);
        temp.pop_back();
    }
    */
}

// The technique used here is the DFS.

int main()
{
    int n = 4, k = 2;
    vector<int> temp;
    vector<vector<int>> ans;
    Combinations(n, k, 1, ans, temp);
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

// Combinations Recurrence Relation nCk :
/*
The Two-Variable Recurrence Relation
Unlike subsets, the work here depends on two shifting values:

The number of choices we have left to look at: n - val + 1. Let's call this remaining pool m.

The number of slots we still need to fill in our combination: k - temp.size(). Let's call this remaining quota r.

Every time we call Combinations, our pool of numbers shrinks by 1 because val moves to val + 1.

If we Take the number, our remaining quota drops by 1 (r - 1).

If we Skip the number, our remaining quota stays the same (r).

So, for a normal step, our recurrence relation is:
T(m, r) = T(m - 1, r - 1) + T(m - 1, r) + O(1)

The Base Cases
Because we have optimization guards, our recursion stops under three different conditions:

Success Base Case (r = 0):
When temp.size() == k, we have a valid combination. We copy temp into arr. Since temp always has exactly k elements at this point, copying it takes O(k) time.
T(m, 0) = O(k)

Out of Numbers Base Case (m = 0 when r is greater than 0):
If val > n but we haven't hit our size goal, we just return. This takes constant time.
T(0, r) = O(1)

Pruning Base Case (m less than r):
Our optimization condition temp.size() + (n - val + 1) < k is mathematically equivalent to saying "the remaining pool is smaller than our remaining quota" (m less than r). When this triggers, the code immediately returns in constant time.
T(m, r) = O(1) for m less than r

What this means for Total Complexity
This specific recurrence relation directly tracks the mathematical definition of combinations, known as Pascal's Identity:
n-choose-k = (n-1)-choose-(k-1) + (n-1)-choose-k

Because our recursion tree perfectly mirrors Pascal's triangle and cuts off early thanks to our pruning conditions, the total number of valid leaf nodes generated is exactly n-choose-k.

Since we do O(k) work to copy the vector at each of those successful leaf nodes, the overall time complexity works out to:

Total Time Complexity = O(k * (n-choose-k))
*/
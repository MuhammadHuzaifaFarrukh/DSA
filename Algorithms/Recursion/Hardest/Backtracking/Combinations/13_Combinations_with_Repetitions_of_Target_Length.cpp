#include <iostream>
#include <vector>

using namespace std;

/*
Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].
A number may be used more than once.
You may return the answer in any order.
Input: n = 4, k = 2
Output: [[1,1],[1,2],[1,3],[1,4],[2,2],[2,3],[2,4],[3,3],[3,4],[4,4]]
Explanation: There are 4 choose 2 = 10 total combinations.
Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to be the same combination.
// Here it is mentioned to give only specific combinations , like nCk not all the combinations like power set and with repetitions.
*/
// The General Formula of Combinations (n+k-1)Ck.
/*
Why does this weird n+k-1 formula exist?
It comes from a famous combinatorics visualization method called Stars and Bars.
Imagine you are buying k pieces of fruit, and there are n different types of fruit available in the store (e.g., Apples, Bananas, Oranges).
To separate the different types of fruit in your basket, you use dividers (bars).
If you have n types of fruit, you need exactly n-1 dividers to separate them into n distinct piles.
The fruits you choose are represented by k stars.
Now, your entire choice can be represented by a sequence of stars * and bars | :
If you want 2 Apples, 0 Bananas, and 1 Orange (n=3 types, k=3 choices):
**     |          | *
Apples   Bananas   Oranges
Because you have k stars and n-1 bars, the total number of slots in your sequence is:
Total Slots = k + (n - 1) = n + k - 1
To make a combination, all you have to do is choose which of those total slots will be the k stars (or which will be the n-1 bars).

*/

// We want to generate all the combinations of n , [1,n] such that there length is 'k'.
// We use Include / Exclude again.
// We come and ask if we want to take a number or not.
// For yes , we push it into temp vector and again call the same function with same index so that we can use that number again.
// For no , we just call the same function with next index without pushing it into temp vector.
// This allows it to explore all the combinations of (n+k-1)Ck
// When the length of any pair reaches 'k' , we stop there and save our answer.
// If the value goes beyond the 'n' , then we just backtrack.

// Time Complexity :
/*
When we are asking for choices , our structure represents that of a binary tree with yes or no.
So we are recursively asking if we should take this number or not.
This continues till approx length n+(k-1).
We see that at each level , the nodes increase : according to the length.
And time taken in all nodes is like constant.
So our total time is O((n+k-1)Ck) or O(k*(n+k-1)Ck) if we also add the pushback time.
*/

// Space Complexity :
/*
Our tree's depth goes upto 'n' call stacks at max.
Our temp stores only at most 'k' numbers.
So Space is O(n+k) = O(n)
But anwer vector stores (n+k-1)Ck each of size 'k'.
So answer takes O((n+k-1)Ck) size.
Total Space : O(n) + O((n+k-1)Ck) = O((n+k-1)Ck)
*/

void Combinations(int n, int k, int val, vector<vector<int>> &arr, vector<int> &temp)
{
    if (temp.size() == k)
    {
        arr.push_back(temp);
        return;
    }
    // Base Case 2: Out of bounds
    if (val > n)
    {
        return;
    }

    // Choice 1: Take the current number (val)
    temp.push_back(val);
    Combinations(n, k, val, arr, temp);
    temp.pop_back(); // Backtrack to restore the state

    // Choice 2: Skip the current number (val)
    Combinations(n, k, val + 1, arr, temp);
}

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
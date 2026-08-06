#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// We want to find the specific nPk for a given array / vector and a given k.
// If we are given {1,2,3,4} , k = 2 ,then we have to find 4P2.

// We use the same swapping logic of permutations.
// We just change the 'n' size array to 'k' size.
// We are changing inside nums , so we push_back the nums.
// This generates the all nPk , but with same size as 'n'.
// Because it fixes any 'k' elements first and then generates all permutations around it.
// Now if we want to just generate the 'k' sized , then we still make changes and when we reach base case , we only take k first elements and save them.
// nPk Permutations are called Partial Permutations.

// Time Complexity :
// The formula of nPk is n!/(n-k)!
// So in the worst case k can go to n.
// So its time can be O(n*(nPk)) or O(n*n!).

// Space Complexity :
// At the deepest point of execution, there are exactly k active function frames sitting on the call stack at the same time.
// So the space taken is O(k) since there is no extra space.
// We use ans array to save our answer of nPk and each row contains n sized vectors.
// So we can say that total space : O(n*nPk) or O(k*nPk) if copy only k elements.

void PermutationsNPK(vector<int> &nums, vector<vector<int>> &ans, int n, int index, int k)
{
    if (index == k)
    {
        // vector<int> current_permutation(nums.begin(), nums.begin() + k);
        // ans.push_back(current_permutation);
        ans.push_back(nums);
        return;
    }

    for (int i = index; i < nums.size(); i++)
    {
        swap(nums[i], nums[index]);
        PermutationsNPK(nums, ans, n, index + 1, k);
        swap(nums[i], nums[index]);
    }
}

/*
Finding 4P2 (Length 2)
What it means: Fill 2 slots [ __ , __ ] using 4 numbers.

How to see it:
Fix one number in the first slot, then loop through all the remaining numbers to fill the second slot. Move your fixed number from left to right across the array:

Fix 1 in the first slot: Pair it with the remaining elements (2, 3, 4).
[1, 2], [1, 3], [1, 4]

Fix 2 in the first slot: Pair it with the remaining elements (1, 3, 4).
[2, 1], [2, 3], [2, 4]

Fix 3 in the first slot: Pair it with the remaining elements (1, 2, 4).
[3, 1], [3, 2], [3, 4]

Fix 4 in the first slot: Pair it with the remaining elements (1, 2, 3).
[4, 1], [4, 2], [4, 3]

*/

// If we want to use 'n' instead of a vector , then we use the visited[i] and pushback method instead of the swapping method.
int main()
{
    vector<int> v = {1, 2, 3, 4}; // We can also pass a single 'n' , which represents [1,n]
    vector<vector<int>> ans;
    int k = 2;
    PermutationsNPK(v, ans, v.size(), 0, k);
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
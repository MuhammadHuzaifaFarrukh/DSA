#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
The solution set must not contain duplicate subsets.
Return the solution in any order.

Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
// Internal order doesn't matter like {1,2} = {2,1}.
// This is not a specific nCr , this is a powerset but without duplicates sets.
// The Powerset contains all the nCr like nC0 + nC1 + ... + nCn without any repetition.
*/

void subSet(vector<int> &nums, int index, int n, vector<vector<int>> &ans, vector<int> temp);

// First we sort the vectors so that for using std::unique , we won't have any trouble because it may consider a set {1,4} and {4,1} as different whereas they are same.
// So we sort so our input {4,1,4} looks like {1,4,4}
// Now we run our recursive function which gives us the 2D Vector.
// Then we have to sort it again so that same duplicates subsets are consecutive together.
// Our function may not generate the same subsets together or consecutive so we run a sort on the answer as well.
// Now we can easily use std::unique which brings all consecutive duplicates to the end and we use erase to erase the duplicate subsets.

// Time Comp :
// Sorting the original vector -> nlogn
// Subsets function takes total n*2^n time or 2^n time if we don't count push_back.
// Then we sort the 2^n length whole vector which takes 2^nlog2^n time.
// 2^nlog2^n = 2^n*nlog2 = n*2^n. (we have neglected the push_back() complexity for our ease now).
// Now when C++ uses std::sort for 2D vector sorting , it has to look for comparing each of the row by row comparison and for comparison of 2 rows , it looks at each element of two rows.
// In the worst case, comparing two vectors of size N takes O(N) operations.
// So, the total sorting step is: Number of Comparisons*Cost per Comparison :
// (n*2^n)*(n)= (n^2*2^n) is its time comp.

// Space Comp :
// The maximum depth of the stack is n.
// When we look at the rightmost side , we can see all the yes answers , so temp stores our temporary one length increased in each level.
// So space taken  by temp in 'n' levels :
// 1 , 2, 3 , 4 ,....,n = O(n^2)
// Though this can be avoided and reduced to O(n) by using temp as reference vector.
// But Worst space taken for the subset can be atmost n by temp
// Our answer array stores upto 2^n powerset so we can suppose we have all the sets length n , then total space by 2D vector is :n*2^n and combining stack calls total space becomes : O(n*2^n) + O(n)

// Time : O(n^2*2^n)
// Space : O(n*2^n)
vector<vector<int>> subsetsWithDup(vector<int> &nums)
{
    vector<vector<int>> ans;
    vector<int> temp;

    // 1. Sorting the original vector
    sort(nums.begin(), nums.end());

    // Our Original Function to do the work :
    subSet(nums, 0, nums.size(), ans, temp);

    // 2. Sort the 2D vector so duplicates are placed consecutively
    // C++ sorts by comparing elements index by index.
    sort(ans.begin(), ans.end());

    // 3. Remove duplicate subsets using the erase-unique idiom
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    return ans;
}
void subSet(vector<int> &nums, int index, int n, vector<vector<int>> &ans, vector<int> temp)
{
    if (index == n)
    {
        ans.push_back(temp);
        return;
    }
    subSet(nums, index + 1, n, ans, temp); // Choice of No
    temp.push_back(nums[index]);           // We stored this number , so we are taking it as a "YES" now
    subSet(nums, index + 1, n, ans, temp);
    // We can write temp.pop_back() here if we are using reference temp vector<> which saves memory and space.

    // We can choose to write this loop instead of sorting answer array and then removing the duplicate sets also.
    // After this loop runs , we make our next function call.
    // If we used reference temp , then we can place any choice before / after loop.
    // If we passed by value temp , then we place the choice of "NO" before the loop and choice of "YES" after the loop.
    /*
    int next_index = index + 1;
    while (next_index < nums.size() && nums[next_index] == nums[index])
    {
        next_index++;
    }
    */
}
int main()
{
    vector<int> v = {4, 4, 1};
    vector<vector<int>> ans = subsetsWithDup(v);
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
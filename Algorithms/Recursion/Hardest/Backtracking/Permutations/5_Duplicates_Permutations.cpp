#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;
/*
Given a collection of numbers, nums, that might contain duplicates, return all possible unique permutations in any order.

Input: nums = [1,1,2]
Output:
[ [1,1,2],[1,2,1],[2,1,1] ]
*/
// We have to find all the nPn permutations , and eliminate the repeated permutations.
// In combinations , when we say repetition , we include those repeated ones because they aren't included by the normal combination nCk and will be unique if included.
// In permutations ,when we say duplicates , we don't have to include those duplicates permutation because they will be included if we just used the basic Permutation thing and won't be unique.
// But in permutations ,when we say repetition ,that's a different meaning.
// So here duplicates Permutations mean that don't allow duplicate permutations.
// If an array contains duplicates and we are to find its unique permutations , then we apply the concept of repeated permutations.
// However if we are to find its unique combinations , then we still use combinations without duplicates elements usage.
// For total Permutations count we count them using nPk : nP0 + nP1 + nP2 + ... + nPn = eN! , where e is euler's constant
// nPn represents n!.
// For duplicate Permutations count we have a formula : n!/(f1!*f2!*...fn!) where f1...fn represent the frequencies of the duplicated numbers.
// E.g : (1,1,2,2) , we see total numbers 4 and freq(1) = 2 and freq(2) = 2 so 4!/2!2! = 24/4 = 6 Total Unique Permutations

// There are few approaches for this :
// 1) Just like we solved unique combinations for duplicates in array , we can solve this one as well using that same logic.
// We sort original array , find all its permutations , then sort this answer 2D array and then remove duplicates by using erase(unique()) formula.
// In worst case there may be no duplicates so its time becomes : O(n*n!) and space : O(n*n!).
/*
vector<vector<int>> permuteUnique(vector<int>& nums)
{
    sort(nums.begin(),nums.end());
    vector<vector<int>>ans;
    Permutations(nums,ans,0,nums.size());
    sort(ans.begin(),ans.end());
    ans.erase(unique(ans.begin(),ans.end()),ans.end());
    return ans;
}
*/

// 2) We use the permutation swapping method with just a slight change.
// We use unordered map <int,bool> or we use vector (Hash Map).
// Our constrains on Leetcode said -10<=nums[i]<=10 so we are using a vector of size 21 that will contain those numbers.
// If any number was allowed then we would use unordered map or set.
// We use indexing as [arr[i]+10] , so our index 0 maps to -10 , 1 maps to -9 and so on.
// We make sure that if we swapped with some element at position 'i' , then that same element cannot appear at that exact same position because that will generate same permutations at that position again.
// Like (1,1,2,2) , if we swapped index 0 with 0 , it makes (1,1,2,2) which makes some permutations , but if we swap now 0 with 1 index , then it will generate (1,1,2,2) so we generate duplicate permutations.
// If we swap 0 with 2 ,0 with 3 then we get (2,1,1,2) and (2,1,2,1).
// Now these two also look different but when we generate their possible permutations by fixing first index , we see that both of them generate same permutations , so that's why we don't allow 2 to be at first index more than once.
// We make a boolean map at each stage new so that right after fixing and tracking 1 element at each stage , we make a new boolean map which helps us to check if the same element that appears can also appear at other positions.
// Like (1,1,2,2) , when we fixed swap 0 with 0 index (1,1,2,2) , now we again encounter 1 , and if we had used reference or global map , then it would have said 1 appeared on index 0 so it cannot appear on index 1.
// But we know that 1 can appear on index 1 so that's why we make a new boolean map at each stage.

// If there were other than -10 to 10 numbers , we would use unordered map/set and then that would take memory at each next level by 1.
// At Final Level , the new map would take 1 element space , then on further above levels , that would take increased space , on avg it becomes O(n^2) auxiliary space.
// In worst case there may be no duplicates so its time becomes : O(n*n!) and space : O(n*n!).

// If we didn't use unordered map or any tracking map.
/*
                              [1,1,2,2]
                        /      |      |          \
            [1,1,2,2]    [1,1,2,2]   [2,1,1,2]     [2,1,2,1]
Now we can see that we have two branches (1,1,2,2) that will lead to same permutations.
Even (2,1,1,2) and (2,1,2,1) will also generate same permutations.

*/

/*
                            [1,1,2,2]
                        /                \
            [1,1,2,2]                     [2,1,1,2]
          /          \                    /        \
        [1,1,2,2]  [1,2,1,2]            [2,1,1,2]   [2,2,1,1]
        /         /        \          /        \         |
    [1,1,2,2] [1,2,1,2]  [1,2,2,1]  [2,1,1,2] [2,1,2,1]  [2,2,1,1]
*/
// We can make changes in the same code to find nPk , nPn , or generate all the permutations for the duplicate permutations.
void Permutations(vector<int> &nums, vector<vector<int>> &ans, int index, int n)
{
    // We can also change the size 'n' here to find any nPk.
    // if(index == k)
    // We just wrote the below condition to save our temp answer like having a base case.
    // Otherwise if we don't write it , there's no issue and our code will also generate full tree structure but answer won't be saved here.
    // If we don't write this condition then we will have to save our answer inside the for loop and that would also save the partial permutations as well.
    // However for simplicity we usually write the condition of base case here and only write / save answer for cases if we want to save all the permutations or specific 'k'.

    if (index == n)
    {
        ans.push_back(nums);
        return;
    }
    vector<bool> freq(21);
    for (int i = index; i < nums.size(); i++)
    {
        if (freq[nums[i] + 10] == 0)
        {
            swap(nums[i], nums[index]);
            // We can also save here for finding all the permutations from nP0 to nPn with duplicates and write only return in the base case instead of saving an answer vector.
            // vector<int> current_slice(nums.begin(), nums.begin() + index + 1);
            // ans.push_back(current_slice);
            // We can save nPn here as well , but that would break the simplicity of the code.
            // Saving here and not writing above is also fine and code runs well , but we maintain a structure to write base cases usually at the top or before.
            Permutations(nums, ans, index + 1, n);
            swap(nums[i], nums[index]);
            freq[nums[i] + 10] = 1;
        }
    }
}

// 3) We can optimize the use of the map or tracker , by first tracking all the characters / numbers , then we would check if the count of that specific number is > 0.
// Auxiliary Space will become now O(n) but total space is still O(n^2).
vector<vector<int>> permuteUnique(vector<int> &nums)
{
    vector<vector<int>> ans;
    vector<int> temp;

    // 1. Create a single global frequency map of the input pool
    vector<int> counts(21, 0);
    for (int i = 0; i < nums.size(); i++)
    {
        counts[nums[i] + 10]++;
    }

    // 2. Run the recursion without any swaps!
    buildPermutations(counts, temp, ans, nums.size());
    return ans;
}

void buildPermutations(vector<int> &counts, vector<int> &temp, vector<vector<int>> &ans, int n)
{
    if (temp.size() == n)
    {
        ans.push_back(temp);
        return;
    }

    // We use a single loop over the unique available numbers
    for (int i = 0; i < 21; i++)
    {
        if (counts[i] > 0)
        {
            // Choose
            counts[i]--;
            temp.push_back(i - 10);

            // Explore (Uses the exact same reference map!)
            buildPermutations(counts, temp, ans, n);

            // Backtrack the tracker! Restores the count for the next sibling branch
            temp.pop_back();
            counts[i]++;
        }
    }
}

int main()
{
    vector<int> v = {1, 1, 2, 2};
    vector<vector<int>> ans;
    Permutations(v, ans, 0, v.size());
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
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/*
Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.
Each number in candidates may only be used once in the combination.
Note: The solution set must not contain duplicate combinations.
// The array may contain duplicates.
Input: candidates = [10,1,2,7,6,1,5], target = 8
Output:
[ [1,1,6],[1,2,5],[1,7], [2,6] ]
*/
// This problem is equivalent to subset sum equals target and Subset II but without any repetitions and no duplicate appear in the answer.

// This problem is just like subset sum equals target or not.
// But it asks to eliminate any set/combination that has appeared already must not appear again.
// Like if an array is {1,1,2} then finding all possible combinations give us a set (1,2) and again (1,2) so we have two sets.
// One way is to sort the given array ,and then sort the answer array at the end , then erase all the duplicate sets within it.
// But that takes too much time and may give TLE.
// So we just sort the given array candidates.
// This will place all the duplicates together.
// Then we find all the possible combinations.
// Now once we have found combinations using a number , before going for the choice of next number we have to see if the next number isn't the same as previous.
// Because if the previous and this number is same , it means that the duplicate set will appear if we use it again.
// So we use while loop to skip over these duplicate same numbers.
// Then we go for the choice of "NO" where we don't take this number and go for the next number.

// Time Complexity :
// Sorting first took time nlogn.
// The recursion tree goes upto 'n' levels.
// Finding total combinations (even without duplicates because at worst there may be all unique elements present) takes almost 2^n nodes time because time in each node is constant.
// Thus total time : O(nlogn + 2^n) or O(nlogn + n*2^n) if we don't neglect pushback of temp into ans.
// This time is less than the time taken by our methodology of doing the sorting of answer again and then removing duplicates total time taken : O(n^2*2^n).

// Space :
// Recursion can go upto n levels and temp can get increasing by 1 for each level yes choices.
// 1+2+3+...+n = O(n^2) , which happens if temp was not a reference variable.
// If temp vector is passed by reference then space taken can go at most 'n' at 'n' level so total space by this temp vector : O(n) or O(n^2) depending if it is referenced or not.
// In the worst case there can be upto 2^n valid combinations , so our answer array will hold 2^n combinations.
// Each combination can have length upto 'n'.
// So space by ans : O(n*2^n).
// Total Space : O(n*2^n + n^2) = O(n*2^n)
void CombinationSum2(vector<int> &candidates, int target, int index, vector<vector<int>> &arr, vector<int> &temp)
{
    if (target == 0)
    {
        arr.push_back(temp);
        return;
    }
    if (target < 0 || index == candidates.size())
    {
        return;
    }

    temp.push_back(candidates[index]);
    CombinationSum2(candidates, target - candidates[index], index + 1, arr, temp);
    temp.pop_back();
    int next_index = index + 1;
    while (next_index < candidates.size() && candidates[next_index] == candidates[index])
    {
        next_index++;
    }
    CombinationSum2(candidates, target, next_index, arr, temp);
}
int main()
{
    vector<int> candidates = {1, 1, 2};
    int target = 3;
    // We must sort the array first.
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> arr;
    vector<int> temp;
    CombinationSum2(candidates, target, 0, arr, temp);
    return 0;
}
#include <iostream>
#include <vector>

using namespace std;

// Given a vector of positive integers , we need to see how many subsets equal target or not.
// If yes then return true otherwise false.
// E.g : {2,5,6,1} with target = 8 , then we have 2 pairs : (2,6) and (2,5,1).
// We want to generate all the possible choices without any repetition usage , means we cannot use the same number.

// Again we generate all the subsets (combinations) using recursion.
// We call 2 functions for 2 branches with + so that any branch that gives us true will be considered as a YES answer and will be added in our final answer.
// We call 1 function same as it is with next index which indicates that we didn't take this sum as our choice.
// We call 1 function same as it is with next index and target - this number which indicates that we took this sum as our choice.
// If our target becomes 0 , it means we found the target and return 0.
// If it becomes negative then there is no point of finding further as we are gonna encounter positives only.

// Time : O(2^n)    -> Binary Tree Like Structure
// Space : O(n)     -> Maximum Depth upto 'n' levels.
int find(vector<int> &arr, int index, int n, int target)
{
    if (target == 0)
    {
        return 1;
    }
    if (index == n || target < 0)
    {
        return 0;
    }
    return (find(arr, index + 1, n, target)) + (find(arr, index + 1, n, target - arr[index]));
}

// If this vector allowed negatives and zero also then we would have to terminate target < 0 condition because for that we need to go check all combinations.
// We would write base conditions :
/*
if(index == n)
{
    if(target == 0)
    {
        return 1;
    }
    return 0;
}
*/
int main()
{
    vector<int> v = {2, 5, 6, 1};
    int target = 8;
    cout << " Targets : " << find(v, 0, v.size(), target) << endl;
    return 0;
}
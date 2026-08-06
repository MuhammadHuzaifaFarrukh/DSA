#include <iostream>
#include <vector>

using namespace std;

// Given a vector of positive integers , we need to see if any subset equals target or not.
// If yes then return true otherwise false.
// E.g : {4,2,3} , and target  = 7 , can be generate by the pair (4,3) or (3,4).
// We want to generate all the possible choices without any repetition usage , means we cannot use the same number.
// Again we generate all the subsets (combinations) using recursion.
// We call 2 functions for 2 branches with OR so that any branch that gives us true will be considered as a YES answer.
// We call 1 function same as it is with next index which indicates that we didn't take this sum as our choice.
// We call 1 function same as it is with next index and target - this number which indicates that we took this sum as our choice.
// If our target becomes 0 , it means we found the target and return 0.
// If it becomes negative then there is no point of finding further as we are gonna encounter positives only.

// Time : O(2^n)    -> Binary Tree Like Structure
// Space : O(n)     -> Maximum Depth upto 'n' levels.
bool find(vector<int> &arr, int index, int n, int target)
{
    if (target == 0)
    {
        return 1;
    }
    if (index == n || target < 0)
    {
        return 0;
    }
    return (find(arr, index + 1, n, target)) || (find(arr, index + 1, n, target - arr[index]));
}

// If this vector allowed negatives and zero also then we would have to terminate target < 0 condition because for that we need to go check all combinations.
// If we allowed repetitions in this , then we just need to keep the index as it is in the 2nd function call after OR (||). and time comp would be O(2^(n+T)) where T is the target value.
int main()
{
    vector<int> v = {1, 2, 3};
    int target = 4;
    cout << " Target made ?" << find(v, 0, v.size(), target) << endl;
    return 0;
}
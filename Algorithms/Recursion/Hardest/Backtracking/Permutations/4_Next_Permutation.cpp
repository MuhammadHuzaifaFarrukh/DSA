#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
A permutation of an array of integers is an arrangement of its members into a sequence or linear order.

For example, for arr = [1,2,3], the following are all the permutations of arr: [1,2,3], [1,3,2], [2, 1, 3], [2, 3, 1], [3,1,2], [3,2,1].
The next permutation of an array of integers is the next lexicographically greater permutation of its integer. More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the next permutation of that array is the permutation that follows it in the sorted container. If such arrangement is not possible, the array must be rearranged as the lowest possible order (i.e., sorted in ascending order).

For example, the next permutation of arr = [1,2,3] is [1,3,2].
Similarly, the next permutation of arr = [2,3,1] is [3,1,2].
While the next permutation of arr = [3,2,1] is [1,2,3] because [3,2,1] does not have a lexicographical larger rearrangement.
Given an array of integers nums, find the next permutation of nums.

The replacement must be in place and use only constant extra memory.
*/
// This is permutation (Full) without any reptition or duplicates.

// We can use the normal permutation method to generate all n! permutations nPn but it becomes difficult to stop there using recursion because we don't know when to stop and where at the next permutation.
// Because that can generate all of nPn.
// However that still becomes messy or error prone if we place lots of permutations.
// Also if we are at the last permutation , then we cannot say we are at the last permutation because our program will still keep generating all nPn permutations.
// Therefore the last permutation cannot be solved like by this recursive normal method of permutation generations because last permutation says its next permutation is all the elements sorted.
// E.g (3,2,1) -> (1,2,3)

// We use the "DICTIONARY" algorithm
// 1) Scan from right to left to find a pivot.

// Pivot is the first element with property of (nums[i]) < nums[i+1]
// We have to start from the 2nd last element that is to be compared with last element and then 3rd last to be compared with 2nd element and so on until we find an index or reach index = -1.
// Suppose we have only two elements (1,2) then we start finding index from 0th index by putting i = n-2 which gives 2-2=0.
// So it helps us to give any 2nd last element.
// Even if we put an empty array or array with 1 element , this index i will be either -2 or -1 and will not be any valid index so we just go to the last step of reverse if we tried to put empty or array with 1 element.

// 2) Find the strict larger number than pivot from right to left.
// Once we find we swap them.
// If we are unable to find the index , then we simply reverse and this happens in the case (3,2,1)

// 3) Then we have to reverse the array from the point where our old pivot was+1 to the end.
// For empty and array with 1 element , reversing does no affect at all.
// Empty Array : reverse(nums.begin()-2+1,nums.end()); , so this will crashes our program.
// 1 Element array or Index Not Found (-1): reverse(nums.begin()-1+1,nums.end()); = reverse(nums.begin()-1+1,nums.end());
// For All other elements with index found it reverses just fine and we also did +1 to start after our index position.

// Time : O(n)
// Space : O(1)
void nextPermutation(vector<int> &nums)
{
    /*
    // You may add this if you want to save from empty array case.
        if(nums.empty())
        {
            return;
        }
    */
    int i = nums.size() - 2;
    // We must have atleast two numbers to find the next unique permutation

    // Step 1: Find the rightmost inversion (the pivot)
    while (i >= 0 && nums[i] >= nums[i + 1])
    {
        i--;
    }

    // Step 2 & 3: If a pivot is found, find the successor and swap
    if (i >= 0)
    {
        int j;
        for (j = nums.size() - 1; j >= 0; j--)
        {
            if (nums[j] > nums[i])
            {
                break;
            }
        }
        /*
        // This also works :
        while (nums[j] <= nums[i])
        {
            j--;
        }
        */
        swap(nums[i], nums[j]);
    }

    // Step 4: Reverse the suffix to reset it to the lowest possible order
    // If we couldn't find the index it means no next permutation exists so we just reverse it (3,2,1) becomes (1,2,3) , -1+1= 0
    reverse(nums.begin() + i + 1, nums.end());
}

int main()
{
    vector<int> v = {1, 5, 8, 4, 7, 6, 5, 3, 1};
    nextPermutation(v);
    for (int i : v)
    {
        cout << i << " ";
    }
    return 0;
}
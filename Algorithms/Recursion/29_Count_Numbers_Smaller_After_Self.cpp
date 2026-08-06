#include <iostream>
#include <vector>

using namespace std;

/*
Given an integer array nums, return an integer array counts where counts[i] is the number of smaller elements to the right of nums[i].

Input: nums = [5,2,6,1]
Output: [2,1,1,0]
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
*/

// We solve this using Merge Sort algorithm with little changes.
// We will apply merge sort on a new array named indices.
// This indices will store the original positions of the elements so that when we are about to update count , it gets updated correctly.
// With each merge , we also see the right count , which indicates how many elements were greater than our number right.
// While merging , if right array wins , we increase right count by 1 , so that when we place left index value in temp array , count gets the correct value of the right counts.
// Time : O(nlogn)
// Space : O(n)
vector<int> countSmaller(vector<int> &nums)
{
    vector<int> counts(nums.size(), 0);
    vector<int> indices(nums.size());
    for (int i = 0; i < nums.size(); i++)
    {
        indices[i] = i;
    }
    mergeSort(counts, nums, indices, 0, nums.size() - 1);
    return counts;
}

void mergeSort(vector<int> &counts, vector<int> &nums, vector<int> &indices, int start, int end)
{
    if (start == end)
    {
        return;
    }
    int mid = start + (end - start) / 2;
    mergeSort(counts, nums, indices, start, mid);
    mergeSort(counts, nums, indices, mid + 1, end);
    merge(counts, nums, indices, start, mid, end);
}

void merge(vector<int> &counts, vector<int> &nums, vector<int> &indices, int start, int mid, int end)
{
    int left = start, right = mid + 1;
    int index = 0;
    vector<int> temp(end - start + 1);
    int right_count = 0;

    while (left <= mid && right <= end)
    {
        // When left array wins , we also update counts at original index , with value of right counts.
        if (nums[indices[left]] <= nums[indices[right]])
        {
            temp[index] = indices[left];
            counts[indices[left]] += right_count;
            index++;
            left++;
        }
        else
        {
            temp[index] = indices[right];
            index++;
            right++;
            // When right array part wins , we update the right counts
            right_count++;
        }
    }

    // If Left Portion is still left
    // We have to update the count if it couldn't be updated in the upper while loop().
    while (left <= mid)
    {
        temp[index] = indices[left];
        counts[indices[left]] += right_count;
        index++;
        left++;
    }

    // If Right Portion is still left
    while (right <= end)
    {
        temp[index] = indices[right];
        index++;
        right++;
    }

    // Fill Values into the Array from the temp array
    index = 0;
    while (start <= end)
    {
        indices[start] = temp[index];
        index++;
        start++;
    }
}

int main()
{
    vector<int> v = {5, 2, 6, 1};
    vector<int> ans = countSmaller(v);
    for (int i : ans)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
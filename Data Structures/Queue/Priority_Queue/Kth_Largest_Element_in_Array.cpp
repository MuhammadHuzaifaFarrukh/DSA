#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

/*
Given an integer array nums and an integer k, return the kth largest element in the array.
Note that it is the kth largest element in the sorted order, not the kth distinct element.

Input: nums = [3,2,1,5,6,4], k = 2
Output: 5

Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4
*/

// 1) The Traditional Approach of comparisons.
// We compare and keep finding the kth element , but that method would require manual checks (say 100th max element would require 100 manual if-else for O(n) Time)
// If we decide to put those manual checks in another loop , then it would go to O(n*k).
// It can fail in case of duplicates.
int findKthLargest(vector<int> &arr, int k)
{
    int current_max = *max_element(arr.begin(), arr.end()); // First minimum.

    for (int i = 2; i <= k; i++)
    {
        int next_max = INT_MIN;

        for (int j = 0; j < arr.size(); j++)
        {
            // Find the largest element strictly greater than current_max
            if (arr[j] < current_max && arr[j] > next_max)
            {
                next_max = arr[j];
            }
        }

        current_max = next_max; // Move to the next largest step
    }

    return current_max;
}

// 2) Sort the array in descending order.
// Take the kth largest element as arr[k-1].
// Time : O(nlogn)
// Space : O(logn) due to C++ std::sort()
int findKthLargest2(vector<int> &arr, int k)
{
    sort(arr.begin(), arr.end(), greater<int>());
    return arr[k - 1];
}

// 3) Max-Heap Approach
// Pop k-1 elements and then the kth largest will be at top
// Time to Pop Out elements : (k-1)logn ~ klogn , it can go to nlogn in the worst case where k=n.
// Total Time : O(n+klogn) or O(nlogn)

// Space Complexity :
// All elements are pushed into heap so it takes O(n) space.
// Best When K is relatively small.
int findKthLargest3(vector<int> &nums, int k)
{
    priority_queue<int> pq(nums.begin(), nums.end());
    for (int i = 0; i < k - 1; i++)
    {
        pq.pop();
    }
    return pq.top();
}

// 4) A little bit optimized using min-heap :
// We build heap using only the first 'k' elements from array.
// Then we check each number , if its greater than the largest one present in our heap only then we put this number in our heap.
// We check this for (n-k) times.
// Time Complexity :
// We build heap in 'k' time.
// Then we do push and pop both for (n-k) times. = O((n-k)logk) , which is for avg case.
// In the worst , we may do push and pop every single time so it can get nlogk also.
// Thus total Time : O(k+(n-k)logk) or O(nlogk).
// Best when K is too large.
int findKthLargest4(vector<int> &nums, int k)
{
    priority_queue<int, vector<int>, greater<int>> pq(nums.begin(), nums.begin() + k);

    for (int i = k; i < nums.size(); i++)
    {
        if (nums[i] > pq.top())
        {
            pq.pop();
            pq.push(nums[i]);
        }
    }
    return pq.top();
}

// 5) We use quick select.
// We know that kth smallest element in a sorted target will be at index k-1.
// So we use quick sort and start to find the index of the pivot.
// If the index of pivot turns out to be target , we've found our target.
// If pivot index is greater than our target , it means target is in left half.
// If pivot index is smaller than our target , it means target is in right half.
// We are choosing pivot as the last indexed element , you may choose any.
// Time on Avg : O(n)       (N + N/2 + N/4 + N/8 + ... ~ 2N = N)
// Time for worst case : O(n^2)
// Space on Avg : O(logn)
// Space for worst case : O(n)
// Will get TLE on leetcode.
int quickSelect(vector<int> &arr, int start, int end, int k)
{
    int target = arr.size() - k;
    if (start <= end)
    {
        int pivot = partition(arr, start, end);
        if (pivot == target)
        {
            return arr[pivot]; // Kth Smallest Element
        }
        else if (pivot > target)
        {
            // Search for left Half :
            return quickSelect(arr, start, pivot - 1, k);
        }
        else
        {
            // Search for Right Half :
            return quickSelect(arr, pivot + 1, end, k);
        }
    }
    return -1;
}

int partition(vector<int> &arr, int start, int end)
{
    int pos = start;
    while (start <= end)
    {
        if (arr[start] <= arr[end])
        {
            swap(arr[start], arr[pos]);
            pos++;
        }
        start++;
    }
    return (pos - 1);
}

// 6) Binary Search on answer range.
// Not suitable for arrays containing large values , because it is applied on answer range.
// Here we set start = min of array and end = max of array.
// Now we find mid and see how many values are >= mid.
// If count >= k , then it means kth largest is right there , we need to increase our answer space , we also save this mid as ans because it could be a probable answer.
// If count < k , it means , we need to decrease our answer space by mid+1 so we can find less numbers to increase the counts of kth largest numbers.
// Time : O(nlog(max-min))
// Space : O(1)
int findKthLargest4(vector<int> &arr, int k)
{
    int ans;
    int start = *min_element(arr.begin(), arr.end());
    int end = *max_element(arr.begin(), arr.end());
    while (start <= end)
    {
        int mid = start + (end - start) / 2;
        int count = 0;
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] >= mid)
            {
                count++;
            }
        }
        if (count >= k)
        {
            ans = mid;
            start = mid + 1; // Search in the right half for larger element
        }
        else
        {
            end = mid - 1; // Search in the left half for smaller element.
        }
    }
}

int main()
{
    vector<int> v = {3, 2, 1, 5, 6, 4};
    int k = 2;
    cout << "Kth largest element : " << findKthLargest2(v, k) << endl;

    return 0;
}
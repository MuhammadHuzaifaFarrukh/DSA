#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

/*
Given an integer array arr[] and an integer k, find and return the kth smallest element in the given array.
Note: The kth smallest element is determined based on the sorted order of the array.

Input: arr[] = [10, 5, 4, 3, 48, 6, 2, 33, 53, 10], k = 4
Output: 5
Explanation: 4th smallest element in the given array is 5.

Input: arr[] = [7, 10, 4, 3, 20, 15], k = 3
Output: 7
Explanation: 3rd smallest element in the given array is 7.
*/

// 1) Brute Force Approach :
// We find the 1st minimum element.
// Then we run this in a nested loop for (k-1) times to find the kth smallest using current minimum and next minimum.
// When we find a new minimum element , we assign current minimum to this one so that the next minimum we find must be strictly greater than current minimum and less than next min which is INT_MAX at start.
// Time : O(nk)
// Space : O(1)
int kthSmallest(vector<int> &arr, int k)
{
    int current_min = *min_element(arr.begin(), arr.end()); // First minimum.

    for (int i = 2; i <= k; i++)
    {
        int next_min = INT_MAX;

        for (int j = 0; j < arr.size(); j++)
        {
            // Find the smallest element strictly greater than current_min
            if (arr[j] > current_min && arr[j] < next_min)
            {
                next_min = arr[j];
            }
        }

        current_min = next_min; // Move to the next smallest step
    }

    return current_min;
}

// 2) Sort the array
// Access the kth smallest by arr[k-1].
// Time : O(nlogn)
// Space : O(logn) due to C++ std::sort()
int kthSmallest2(vector<int> &arr, int k)
{
    sort(arr.begin(), arr.end());
    return arr[k - 1];
}

// 3) Using Min-Heap :
// We make min-heap using given elements in our vector.
// Then we take out the (k-1) smallest elements at the top.
// After this , the top element will be present at the top.
// Time Complexity :
// Time to build heap = O(n)
// Time to Pop Out elements : (k-1)logn ~ klogn , it can go to nlogn in the worst case where k=n.
// Total Time : O(n+klogn) or O(nlogn)

// Space Complexity :
// All elements are pushed into heap so it takes O(n) space.
int kthSmallest3(vector<int> &arr, int k)
{
    priority_queue<int, vector<int>, greater<int>> pq(arr.begin(), arr.end());
    for (int i = 0; i < k - 1; i++)
    {
        pq.pop();
    }
    return pq.top();
}

// 4) By using Max Heap :
// We build heap using only the first 'k' elements from array.
// Then we check each number , if its smaller than the largest one present in our heap only then we put this number in our heap.
// We check this for (n-k) times.
// Time Complexity :
// We build heap in 'k' time.
// Then we do push and pop both for (n-k) times. = O((n-k)logk) , which is for avg case.
// In the worst , we may do push and pop every single time so it can get nlogk also.
// Thus total Time : O(k+(n-k)logk) or O(nlogk)

// Space Complexity :
// Max Heap here , it will always contain 'k' elements.
// Space : O(k)
int kthSmallest4(vector<int> &arr, int k)
{
    priority_queue<int> pq(arr.begin(), arr.begin() + k);
    for (int i = k; i < arr.size(); i++)
    {
        if (arr[i] < pq.top())
        {
            pq.pop();
            pq.push(arr[i]);
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
// Time on Avg : O(n)   (N+N/2+N/4+N/8+... ~ 2N ~ N)
// Time for worst case : O(n^2)
// Space on Avg : O(logn)
// Space for worst case : O(n)
int quickSelect(vector<int> &arr, int start, int end, int k)
{
    int target = k - 1;
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

// 6) Using Binary Search on answer range.
// Not suitable for arrays containing large values , because it is applied on answer range.
// Here we set start = min of array and end = max of array.
// Now we find mid and see how many values are <= mid.
// If count >= k , then it means kth smallest is right there , we need to shrink our answer space , we also save this mid as ans because it could be a probable answer.
// If count < k , it means , we need to increase our answer space by mid+1.
// Time : O(nlog(max-min))
// Space : O(1)
int kthSmallest5(vector<int> &arr, int k)
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
            if (arr[i] <= mid)
            {
                count++;
            }
        }
        if (count >= k)
        {
            ans = mid;
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }
    return ans;
}

int main()
{
    vector<int> v = {3, 5, 12, 2, 1, 9, 6, 7, 10};
    int k = 4;
    cout << "Smallest Element Kth in Array : " << kthSmallest(v, k) << endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

/*
Given an n x n matrix where each of the rows and columns is sorted in ascending order, return the kth smallest element in the matrix.
Note that it is the kth smallest element in the sorted order, not the kth distinct element.
You must find a solution with a memory complexity better than O(n^2).
*/
// Example :
/*
Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
Output: 13
Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15], and the 8th smallest number is 13.
*/
// The Elements are sorted row and column wise.

// 1) Brute Force + Sorting
// Put all the elements inside another vector.
// Sort this new vector.
// The kth smallest element is right at the (k-1) index.
// Time : O(n^2logn)
// Extra Space : O(n^2)
// Total Space : O(n^2)
int kthSmallest(vector<vector<int>> &matrix, int k)
{
    vector<int> v;
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            v.push_back(matrix[i][j]);
        }
    }
    sort(v.begin(), v.end());
    return v[k - 1];
}

// 2) Using Min Heap.
// We push all the elements from matrix to heap.
// Then we take out (k-1) smallest elements to get the kth smallest element at the top.
// Time Complexity :
// Pushing n^2 elements : n^2logn^2 = n^2logn (Doing it using step down method it would take only n^2)
// Popping only (k-1) elements out of all : klogn.
// Total Time (Using Pushing each ): O(klogn + n^2logn) or O(n^2logn)
// Total Time (Using Step Down) : O(klogn + n^2) or O(n^2)
// Space Complexity :
// Extra Space : O(n^2)
// Total Space : O(n^2)
int kthSmallest2(vector<vector<int>> &matrix, int k)
{
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            pq.push(matrix[i][j]);
        }
    }
    for (int i = 0; i < k - 1; i++)
    {
        pq.pop();
    }

    return pq.top();
}

// 3) Optimized Min-Heap :
// We push each row's first element along with their indexes of rows and cols.
// Then we run our loop for (k-1) times and get the kth element from our heap.
// While running this one , the smallest one that we take out from heap , we also check if its row has more elements or not , because if this is the smallest , then its possible that next element in this row is also a candidate for the next smallest element , so we push it if it exists.
// We check that by (j+1) < matrix.size().
// Time Complexity :
// We make vector of pairs in 'n' time.
// We make heap of 'n' size : n.
// We run the loop until we've found kth smallest element : klogn
// Total Time :  O(n+klogn) or O(klogn)

// Space Complexity :
// Extra Space : O(n)
// Total Space : O(n)
int kthSmallest3(vector<vector<int>> &matrix, int k)
{
    vector<pair<int, pair<int, int>>> v;
    for (int i = 0; i < matrix.size(); i++)
    {
        v.push_back({matrix[i][0], {i, 0}});
    }
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq(v.begin(), v.end());
    k--;
    while (k--) // If k can exceed size , keep here validation for that too.
    {
        int i = pq.top().second.first;
        int j = pq.top().second.second;
        pq.pop();
        if (j + 1 < matrix.size())
        {
            pq.push({matrix[i][j + 1], {i, j + 1}});
        }
    }
    return pq.top().first;
}

// 4) We can use the quickselect here , by flattening the matrix to a new 1D array.
// This would take :
// Avg Case Time : O(n^2)
// Worst Case Time : O(n^4)
// Avg Case Extra Space : O(n^2)
// Avg Case Recursive Space : O(logn^2) = O(logn)
// Avg Case Total Space : O(n^2)
// Worst Case Extra Space : O(n^2)
// Worst Case Recursive Space : O(n^2)
// Worst Case Total Space : O(n^2)

// 5) Binary Search + Greedy :
// We set our minimum element as start , because answer cannot be less than this minimum.
// We set our end as maximum element because answer cannot be greater than the maximum element of array.
// Because our matrix is row-wise and column-wise sorted we apply 2D Staircase Walk.
// That helps us to find us how many values are <= mid.
// If this count >= K , then kth smallest element may be in this mid range so we save this probable answer and go to find another answer by going to left.
// If this count < k , then it means that kth smallest element is ahead of this mid range.
// Its like finding minimizing the maximum value.
// Start <-----------------Ans###################> End
// Time : O(nlogm) where m is the distance between max element - min element ,
// Space : O(1)
int kthSmallest4(vector<vector<int>> &matrix, int k)
{
    int start = matrix[0][0];
    int n = matrix.size();
    int end = matrix[n - 1][n - 1];
    int ans = 0;
    while (start <= end)
    {
        int mid = start + (end - start) / 2;
        int count = 0;
        int row = 0, col = n - 1;

        // We cannot use sliding window to find the values <= mid
        // Because sliding window is used on a linear structure not 2D or more
        // We use the 2D Staircase Walk because matrix is sorted both column and row-wise.
        // We go at the last value of each row and check if the value <= mid
        // If it is then all the values from starting to that last value of that row will be greater so we will add all that as col+1 and go to find for the next row.
        // If not , then we move to left side of that same row by moving col--.
        // If we skip that col , we won't check it another time , because all values from there down below will be greater so we don't need to check that again.
        // This runs in O(n) in worst case.
        while (row < n && col >= 0)
        {
            if (matrix[row][col] <= mid)
            {
                count += (col + 1);
                row++;
            }
            else
            {
                col--;
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
// Most Optimized approach is the Binary Search.

int main()
{
    vector<vector<int>> v = {{16, 28, 60, 64},
                             {22, 41, 63, 91},
                             {27, 50, 87, 93},
                             {36, 78, 88, 94}};
    int k = 6;
    cout << k << "th Smallest Element in Sorted Matrix : " << kthSmallest(v, k) << endl;

    return 0;
}
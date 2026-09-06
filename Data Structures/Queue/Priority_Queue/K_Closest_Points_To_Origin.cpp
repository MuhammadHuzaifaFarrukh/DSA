#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <cmath>

using namespace std;

/*
Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an integer k, return the k closest points to the origin (0, 0).
The distance between two points on the X-Y plane is the Euclidean distance (i.e., √(x1 - x2)2 + (y1 - y2)2).
You may return the answer in any order.
The answer is guaranteed to be unique (except for the order that it is in).

Input: points = [[1,3],[-2,2]], k = 1
Output: [[-2,2]]
Explanation:
The distance between (1, 3) and the origin is sqrt(10).
The distance between (-2, 2) and the origin is sqrt(8).
Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
We only want the closest k = 1 points from the origin, so the answer is just [[-2,2]].

Input: points = [[3,3],[5,-1],[-2,4]], k = 2
Output: [[3,3],[-2,4]]
Explanation: The answer [[-2,4],[3,3]] would also be accepted.
*/

// 1) We solve it using Max Heap.
// We use pairs to store the distance and points also as another pair i.e a nested pair.
// Because we are using pairs , we need to define our heap completely with all 3 parameters.
// Then we use long long to prevent overflow and double for sqrt().
// Then we put the first 'k' points in our max heap.
// For (n-k) points , we check if we can put this point in our max heap or not , by comparing its distance with the largest distanced point in the max heap.
// If the current distance is smaller than the largest distance in the max heap , then we put this pair in our max heap.
// Time Complexity :
// Time to push 'k' points in heap : klogk
// Time to push/pop '(n-k)' points in heap : (n-k)logk
// Time : O(klogk + (n-k)logk) or O(nlogk)

// Space Complexity :
// O(k)
vector<vector<int>> kClosest(vector<vector<int>> &points, int k)
{
    priority_queue<pair<double, pair<long, long>>, vector<pair<double, pair<long, long>>>, less<pair<double, pair<long, long>>>> pq;
    for (int i = 0; i < k; i++)
    {
        double x = sqrt(points[i][0] * points[i][0] + points[i][1] * points[i][1]);
        pq.push({x, {points[i][0], points[i][1]}});
    }

    for (int i = k; i < points.size(); i++)
    {
        double x = sqrt(points[i][0] * points[i][0] + points[i][1] * points[i][1]);
        if (pq.top().first > x)
        {
            pq.pop();
            pq.push({x, {points[i][0], points[i][1]}});
        }
    }
    vector<vector<int>> ans;
    while (!pq.empty())
    {
        ans.push_back({(int)pq.top().second.first, (int)pq.top().second.second});
        pq.pop();
    }
    return ans;
}

// 2) Using Quick select.
// We can simply look for the kth closest point to the origin using quicksort and modifying it for our purpose.
// We use a dist() in the partition() function so that it compares according to distances and swaps accordingly.
// We use quickselect on the original array instead of saving our answer.
// When pivot == target , it means the kth closest point has been put at its original place.
// So we will now just return it.
// In the main() code , we will take all the points from 0 to k-1 as 'k' closest points.
// When we fixed kth closest point , it ensures that points to its left are of even smaller distances , and points to its right are of greater distances.
// So when we found kth point , it means all the left points to kth point are (k-1) closest points.
// Thus we take all of them 0 to k-1.
// Time for Avg Case : O(n)         (N+N/2+N/4+N/8+... ~ 2N = N)
// Time for Worst Case : O(n^2)
// Space for Avg Case : O(logn)
// Space for Worst Case : O(n)
vector<vector<int>> kClosest2(vector<vector<int>> &points, int k)
{
    quickSelect(points, 0, points.size() - 1, k);
    vector<vector<int>> ans;
    for (int i = 0; i < k; i++)
    {
        ans.push_back(points[i]);
    }
    return ans;
}
void quickSelect(vector<vector<int>> &points, int start, int end, int k)
{
    int target = k - 1;
    if (start <= end)
    {
        int pivot = partition(points, start, end);
        if (pivot == target)
        {
            return;
        }
        else if (pivot > target)
        {
            // Search for left Half :
            quickSelect(points, start, pivot - 1, k);
        }
        else
        {
            // Search for Right Half :
            quickSelect(points, pivot + 1, end, k);
        }
    }
}

int partition(vector<vector<int>> &points, int start, int end)
{
    int pos = start;
    while (start <= end)
    {
        if (dist(points[start]) <= dist(points[end]))
        {
            swap(points[start], points[pos]);
            pos++;
        }
        start++;
    }
    return (pos - 1);
}

int dist(vector<int> &p)
{
    return p[0] * p[0] + p[1] * p[1];
}

int main()
{
    vector<vector<int>> points = {{3, 3}, {5, -1}, {-2, 4}};
    int k = 2;
    vector<vector<int>> ans = kClosest(points, k);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << "(" << ans[i][0] << "," << ans[i][1] << ")" << endl;
    }

    return 0;
}
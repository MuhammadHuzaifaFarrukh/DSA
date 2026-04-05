#include <iostream>
#include <queue>
#include <limits.h>
#include <MaxHeap.hpp>
using namespace std;

// Max-Heap Approach
// Pop k-1 elements and then the kth largest will be at top
// Time Complexity : N + KLogn = O(N) if K is relatively small or O(NLogn) if K is large
// Best When K is relatively small.
int findKthLargest(vector<int> &nums, int k)
{
    priority_queue<int> pq;
    for (int num : nums)
    {
        pq.push(num);
    }
    int x = INT_MIN;
    int i = 1;
    while (!pq.empty())
    {
        x = pq.top();
        pq.pop();
        if (i == k)
        {
            break;
        }
        i++;
    }
    if (x != INT_MIN)
    {
        return x;
    }
    return 0;
}

// A little bit optimized using min-heap :
// Time Complexity : K + 2(N-K)Logk = K + NLogk - LLogk = O(NLogk)    
// Don't add all the elements in heap , instead just keep K largest elements in heap
// Best when K is too large.
/*
int findKthLargest(vector<int>& nums, int k)
{
        // Use a Min-Heap (smaller elements at the top)
        priority_queue<int, vector<int>, greater<int>> pq;

        for (int num : nums) 
        {
            pq.push(num);
            // Keep only k largest elements in the heap
            if (pq.size() > k)
            {
                pq.pop();
            }
        }

        // The top of the heap is now the kth largest
        return pq.top();
}
*/

// In both above methods , the one above is the best for the average cases , otherwise both are almost same.
int main()
{
    
    return 0;
}
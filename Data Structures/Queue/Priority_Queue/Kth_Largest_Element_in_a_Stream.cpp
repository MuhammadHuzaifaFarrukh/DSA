#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

/*
You are part of a university admissions office and need to keep track of the kth highest test score from applicants in real-time. This helps to determine cut-off marks for interviews and admissions dynamically as new applicants submit their scores.
You are tasked to implement a class which, for a given integer k, maintains a stream of test scores and continuously returns the kth highest test score after a new score has been submitted. More specifically, we are looking for the kth highest score in the sorted list of all scores.

Implement the KthLargest class:
KthLargest(int k, int[] nums) Initializes the object with the integer k and the stream of test scores nums.
int add(int val) Adds a new test score val to the stream and returns the element representing the kth largest element in the pool of test scores so far.

Input:
["KthLargest", "add", "add", "add", "add", "add"]
[[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
Output: [null, 4, 5, 5, 8, 8]

Explanation:
KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
kthLargest.add(3); // return 4
kthLargest.add(5); // return 5
kthLargest.add(10); // return 5
kthLargest.add(9); // return 8
kthLargest.add(4); // return 8

Input:
["KthLargest", "add", "add", "add", "add"]
[[4, [7, 7, 7, 7, 8, 3]], [2], [10], [9], [9]]
Output: [null, 7, 7, 7, 8]

Explanation:
KthLargest kthLargest = new KthLargest(4, [7, 7, 7, 7, 8, 3]);
kthLargest.add(2); // return 7
kthLargest.add(10); // return 7
kthLargest.add(9); // return 7
kthLargest.add(9); // return 8
*/

// Constructor KthLargest Time : O(klogk + (n-k)logk)
// Space for the Constructor , just minheap , which is O(k).
// Add() function Time : logk
// Add() function Space : O(1)
class KthLargest
{
public:
    priority_queue<int, vector<int>, greater<int>> minheap;
    int k;
    KthLargest(int k, vector<int> &nums)
    {
        this->k = k;
        for (int i = 0; i < nums.size(); i++)
        {
            add(nums[i]);
        }
    }

    int add(int val)
    {
        if (minheap.size() == k)
        {
            if (minheap.top() < val)
            {
                minheap.pop();
                minheap.push(val);
            }
        }
        else
        {
            minheap.push(val);
        }
        return minheap.top();
    }
};

// We shouldn't apply Binary Search even though they are asking Kth Largest element in a list , doing Binary search in dynamic queries would get a lot of time.

int main()
{
    int k = 3;
    vector<int> v = {4, 5, 8, 2};
    int val = 3;
    KthLargest *obj = new KthLargest(k, v);
    int param_1 = obj->add(val);
    cout << param_1 << endl;
    return 0;
}
#include <iostream>
#include <queue>
using namespace std;

int minCost(vector<int> &arr)
{

    // Create a min priority queue
    priority_queue<int, greater<int>> pq(arr.begin(), arr.end());

    // Initialize result
    int res = 0;

    // While size of priority queue is more than 1
    while (pq.size() > 1)
    {
        // Extract shortest two ropes from pq
        int first = pq.top();
        pq.pop();
        int second = pq.top();
        pq.pop();

        // Connect the ropes: update result and
        // insert the new rope to pq
        res += first + second;
        pq.push(first + second);
    }

    return res;
}

int main()
{
    return 0;
}
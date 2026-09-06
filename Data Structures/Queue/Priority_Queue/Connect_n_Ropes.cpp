#include <iostream>
#include <queue>
using namespace std;

/*
Given an array, arr[] of rope lengths, connect all ropes into a single rope with the minimum total cost.
The cost to connect two ropes is the sum of their lengths. Return the minimum possible cost.

Input: arr[] = [4, 3, 2, 6]
Output: 29
Explanation: First connect 2 and 3 to get [4, 5, 6] with a cost of 5, then connect 4 and 5 to get [9, 6] with a cost of 9, and finally connect 9 and 6 to get one rope with a cost of 15, giving a total minimum cost of 29. Any other order, such as connecting 4 and 6 first, results in a higher total cost of 38.

Input: arr[] = [4, 2, 7, 6, 9]
Output: 62
Explanation: First, connect ropes 4 and 2, which makes the array [6, 7, 6, 9]. Cost of this operation 4 + 2 = 6. Next, add ropes 6 and 6, which results in [12, 7, 9]. Cost of this operation 6 + 6 = 12. Then, add 7 and 9, which makes the array [12,16]. Cost of this operation 7 + 9 = 16. And finally, add these two which gives [28]. Hence, the total cost is 6 + 12 + 16 + 28 = 62.
*/

// 1) Brute Force (For finding the 2 smallest rope currently)
// Time : O(n^2) , time for finding smallest each time.
// Space : O(1)

// 2) By sorting the array.
// Then we pick two smallest elements , then add their cost and put them in their correct place in the array , and then shifting the array.
// Time : O(n^2)
// Space : O(logn) (due to C++ std::sort())

// 3) We use the greedy + min heap approach as we need 2 smallest ropes each time.
// We will put 2 elements in our heap if its size is more than 1.
// Then we take out 2 elements out of the min heap and add their cost to our answer.
// Then we put that rope back in the heap.
// Time : O(nlogn)
// Space : O(n)
int minCost(vector<int> &arr)
{
    // Create a min priority queue
    priority_queue<int, vector<int>, greater<int>> pq(arr.begin(), arr.end());

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
    vector<int> v = {4, 2, 7, 6, 9};
    cout << "Minimum cost : " << minCost(v) << endl;
    return 0;
}
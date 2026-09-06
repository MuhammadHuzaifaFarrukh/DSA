#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
You are given an array of integers stones where stones[i] is the weight of the ith stone.
We are playing a game with the stones. On each turn, we choose the heaviest two stones and smash them together. Suppose the heaviest two stones have weights x and y with x <= y. The result of this smash is:
If x == y, both stones are destroyed, and
If x != y, the stone of weight x is destroyed, and the stone of weight y has new weight y - x.
At the end of the game, there is at most one stone left.

Return the weight of the last remaining stone.
If there are no stones left, return 0.

Input: stones = [2,7,4,1,8,1]
Output: 1
Explanation:
We combine 7 and 8 to get 1 so the array converts to [2,4,1,1,1] then,
we combine 2 and 4 to get 2 so the array converts to [2,1,1,1] then,
we combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
we combine 1 and 1 to get 0 so the array converts to [1] then that's the value of the last stone.
*/

// 1) Brute Forcing / Sorting will lead to time : O(n^2)

// 2) We use greedy + max heap here.
// We put all the stone weights in it.
// Then we take out max weighted stones and if x!=y only then we push (x-y) otherwise we do nothing (both stones destroyed on x==y).
// We keep doing this until size 1 remains.
// When pq has 2 elements left , the final winner will be decided , whether it is last element (x!=y) or 0 (x==y).
// Time : O(nlogn)
// Space : O(n)
int lastStoneWeight(vector<int> &stones)
{
    priority_queue<int> pq(stones.begin(), stones.end());
    while (pq.size() > 1)
    {
        int x = pq.top();
        pq.pop();
        int y = pq.top();
        pq.pop();
        if (x != y)
        {
            pq.push(x - y);
        }
    }

    if (pq.empty()) // Check for empty array
    {
        return 0;
    }
    else // Last Stone left wins
    {
        return pq.top();
    }
}
int main()
{
    vector<int> v = {2, 7, 4, 1, 8, 1};
    cout << "Weight : " << lastStoneWeight(v) << endl;
    return 0;
}
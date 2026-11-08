#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

/*
You are given an integer array nums of length n and an integer k.
You must select exactly k distinct subarrays nums[l..r] of nums. Subarrays may overlap, but the exact same subarray (same l and r) cannot be chosen more than once.
The value of a subarray nums[l..r] is defined as: max(nums[l..r]) - min(nums[l..r]).
The total value is the sum of the values of all chosen subarrays.
Return the maximum possible total value you can achieve.

Input: nums = [1,3,2], k = 2
Output: 4
Explanation:
One optimal approach is:
Choose nums[0..1] = [1, 3]. The maximum is 3 and the minimum is 1, giving a value of 3 - 1 = 2.
Choose nums[0..2] = [1, 3, 2]. The maximum is still 3 and the minimum is still 1, so the value is also 3 - 1 = 2.
Adding these gives 2 + 2 = 4.

Input: nums = [4,2,5,1], k = 3
Output: 12
Explanation:
One optimal approach is:
Choose nums[0..3] = [4, 2, 5, 1]. The maximum is 5 and the minimum is 1, giving a value of 5 - 1 = 4.
Choose nums[1..3] = [2, 5, 1]. The maximum is 5 and the minimum is 1, so the value is also 4.
Choose nums[2..3] = [5, 1]. The maximum is 5 and the minimum is 1, so the value is again 4.
Adding these gives 4 + 4 + 4 = 12.
*/

// 1) Brute Force
// We generate all possible pairs and store their subarray values into an array.
// Then we sort it descendingly.
// Then we choose k from them top ones.
// Time Complexity : O(n^2logn)
// Space Complexity : O(n^2)
long long maxTotalSubarrayValue(vector<int> &nums, int k)
{
    int n = nums.size();
    vector<int> subarrayValues;

    for (int l = 0; l < n; ++l)
    {
        int max_val = INT_MIN;
        int min_val = INT_MAX;

        for (int r = l; r < n; ++r)
        {
            max_val = max(max_val, nums[r]);
            min_val = min(min_val, nums[r]);

            int current_value = max_val - min_val;
            subarrayValues.push_back(current_value);
        }
    }

    // Step 2: Sort all subarray values in descending order
    sort(subarrayValues.begin(), subarrayValues.end(), greater<int>());

    // Step 3: Sum the top k highest values
    long long total_value = 0;
    for (int i = 0; i < k && i < subarrayValues.size(); ++i)
    {
        total_value += subarrayValues[i];
    }

    return total_value;
}

// 2) Using Top-K Pattern + Heap + SegTree.
// If we want to find max total sub val for [4,2,5,1], we generate all the possible scores from answers of R , for L=0,1,2,3:
// L=0 we have R=0,1,2,3 and values : 0,2,3,4
// L=1 we have R=0,1,2,3 and values : 0,3,4
// L=2 we have R=0,1,2,3 and values : 0,4
// L=3 we have R=0,1,2,3 and values : 0
// For k=3 , we get 4+4+4=12.
// If we observe it , we started getting answer from L=0 and R=N-1 and then we can start looking for next best answers by going behind.
// So this becomes the top-k heap pattern or merge heap pattern in which we first build heap using greatest values and once we pop out first value our next best value is put from the one that we just popped.
// So we will do the same here.
// We store the val,L,R inside a tuple or {pair,(pair)}.
// Then we make a heap of n pairs for L=0 and R=N-1.
// We know that we can't get max and min queries in O(logn) time using just prefix array because they are irreversible operations.
// Hence we use segment tree for that and now for storing first n pairs , we just use max[L,N-1] to min[L,N-1] that gets answer in O(logn) time.
// Then once we have the best answers , we run a loop for k times and keep adding the answer to a variable.
// We also look for the best available pairs, once we popped out a pair, we look for the next greatest pair by (L,R-1)
// We also check if L<R because we don't want to generate a pair having L>R that would be meaningless and would only exhaust 'k' giving wrong answer.
// So we generate only those extra pairs for which L<R that is , once a pair having L==R is popped out , we stop using that 'L' and don't push R-1 for that L.
// Time Complexity :
// Segment Tree built in O(n) time
// 1 Query time : O(logn)
// N-Queries : O(nlogn)
// N Pairs(elements) pushed into heap : O(nlogn)
// last loop running for k times through n-pairs : klogn
// Total : O(nlogn + klogn).
// Space Complexity :
// Segment Trees : O(n)
// Heap Storage of n-pairs : O(n)
// Total : O(n)

class SegmentTree
{
public:
    vector<long long> tree;
    vector<int> nums;
    bool flag;
    SegmentTree(vector<int> &nums, bool flag)
    {
        tree.resize(4 * nums.size());
        this->nums = nums;
        build(0, 0, nums.size() - 1);
        this->flag = flag;
    }
    // Helper for our constructor for building a segment tree
    void build(int node, int start, int end)
    {
        if (start == end)
        {
            tree[node] = nums[start];
            return;
        }
        int mid = start + (end - start) / 2;
        build(2 * node + 1, start, mid);
        build(2 * node + 2, mid + 1, end);
        if (flag)
        {
            tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
        }
        else
        {
            tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    void update(int index, int val)
    {
        updating(0, 0, nums.size() - 1, index, val);
    }
    void updating(int node, int start, int end, int index, int val)
    {
        if (index > end || index < start)
        {
            return;
        }
        if (start == end)
        {
            tree[node] = val;
            nums[index] = val;
            return;
        }

        int mid = start + (end - start) / 2;
        updating(2 * node + 1, start, mid, index, val);
        updating(2 * node + 2, mid + 1, end, index, val);
        if (flag)
        {
            tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
        }
        else
        {
            tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    int query(int left, int right)
    {
        return range(0, 0, nums.size() - 1, left, right);
    }

    int range(int node, int start, int end, int left, int right)
    {
        // 3 Cases only:
        // Fully out of range.  (LR=2,5 and our SE=0,1 or 6,7)
        if (end < left || right < start)
        {
            if (flag)
            {
                return INT_MIN;
            }
            else
            {
                return INT_MAX;
            }
        }

        // Fully in range. (LR=2,5 and our SE=2,3 or 4,5)
        if (start >= left && end <= right)
        {
            return tree[node];
        }

        // Partially in range or Overlapping (LR=2,5 and our SE = 0,3 or 4,6)
        int mid = start + (end - start) / 2;
        int l = range(2 * node + 1, start, mid, left, right);
        int r = range(2 * node + 2, mid + 1, end, left, right);
        if (flag)
        {
            return max(l, r);
        }
        else
        {
            return min(l, r);
        }
    }
};
long long maxTotalValue(vector<int> &nums, int k)
{
    priority_queue<pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>>>, less<pair<long long, pair<int, int>>>> pq;
    SegmentTree s1(nums, 0);
    SegmentTree s2(nums, 1);
    for (int l = 0; l < nums.size(); l++)
    {
        long long val = s2.query(l, nums.size() - 1) - s1.query(l, nums.size() - 1);
        pq.push({val, {l, nums.size() - 1}});
    }
    long long result = 0;
    while (k--)
    {
        pair<long long, pair<int, int>> p = pq.top();
        int l = p.second.first;
        int r = p.second.second;
        pq.pop();
        result += p.first;
        if (l < r)
        {
            long long x = s2.query(l, r - 1) - s1.query(l, r - 1);
            pq.push({x, {l, r - 1}});
        }
    }
    return result;
}

int main()
{
    vector<int> v = {4, 2, 5, 1};
    int k = 3;
    cout << "Max Val : " << maxTotalValue(v, k) << endl;
    return 0;
}
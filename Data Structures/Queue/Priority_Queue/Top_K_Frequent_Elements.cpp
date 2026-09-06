#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Input: nums = [1,2,1,2,1,2,3,1,3,2], k = 2
Output: [1,2]

Input: nums = [1], k = 1
Output: [1]
*/

// 1) Sorting / Brute :
// We get the counts of all numbers.
// Then we push them in a vector<pair> and finally we sort them in the descending order.
// We get the 'k' elements with top frequencies easily.
// Time : O(n + mlogm) where m is the number of distinct numbers.
// Space : O(m) where m is the number of distinct numbers.
vector<int> topKFrequent(vector<int> &nums, int k)
{
    unordered_map<int, int> counts;
    for (int num : nums)
    {
        counts[num]++;
    }

    // Copy map entries into a vector of pairs
    vector<pair<int, int>> freqList;
    for (const auto &p : counts)
    {
        int freq = p.first;
        int num = p.second;
        freqList.push_back({freq, num});
    }

    // Sort descending by frequency
    sort(freqList.begin(), freqList.end(), greater<pair<int, int>>());

    // Collect top K elements
    vector<int> result;
    for (int i = 0; i < k; i++)
    {
        result.push_back(freqList[i].second);
    }

    return result;
}

// 2) Max Heap :
// Step 1: Count frequencies
// Push all unique elements into the heap
// Step 3: Extract the top K elements
// Time Complexity :
// Counting all unique elements : O(n)
// Build Max Heap by pushing all the unique pairs : O(mlogm)
// Popping K Top Elements : O(klogm)
// Total Time : O(n+mlogm + klogm) = O(n+mlogm)
// Space Complexity :
// Heap Size is unique pairs : O(m)
// Map also has unique numbers : O(m)
// Total Space : O(m) (or O(n) in the worst)
vector<int> topKFrequent(vector<int> &nums, int k)
{
    unordered_map<int, int> counts;
    for (int num : nums)
    {
        counts[num]++;
    }
    priority_queue<pair<int, int>> maxHeap;

    for (const auto &p : counts)
    {
        int freq = p.first;
        int num = p.second;
        maxHeap.push({freq, num});
    }

    vector<int> result;
    for (int i = 0; i < k; i++)
    {
        result.push_back(maxHeap.top().second);
        maxHeap.pop();
    }

    return result;
}

// 3) Min heap.
// We store the counts of all elements in an unordered map.
// Then we use min heap to store the k sized pairs only from the unordered map.
// If the size of min heap exceeds then we have to check if its top element has less frequency then the current one.
// If yes then we pop this one out and add the current one in the heap.
// We keep k most frequency elements in our heap.
// Time Complexity :
// We traverse map in O(n) time.
// Then we push / pop into heap for 'k' sized elements : O(nlogk)
// Emptying the heap : klogk
// Total Time : O(n+nlogk+klogk) = O(nlogk)
// Space Complexity :
// Map = O(m) where m are the distinct elements of nums
// Heap keeps only k sized elements.
// TOtal Space : O(m+k) (Can go to O(n) in worst )
vector<int> topKFrequent3(vector<int> &nums, int k)
{
    unordered_map<int, int> counts;
    for (int i = 0; i < nums.size(); i++)
    {
        counts[nums[i]]++;
    }

    // Min-heap storing pair<frequency, element>
    // We want frequency first so the PQ sorts by it
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    for (const auto &pair : counts)
    {
        int val = pair.first;
        int freq = pair.second;

        if (pq.size() < k)
        {
            pq.push({freq, val}); // We kept the freq first so that elements in priority queue are sorted according to frequencies rather than the key value
        }
        else
        {
            if (freq > pq.top().first)
            {
                pq.pop();
                pq.push({freq, val});
            }
        }
    }

    vector<int> result;
    while (!pq.empty())
    {
        result.push_back(pq.top().second);
        pq.pop();
    }
    return result;
}

int main()
{
    vector<int> v = {1, 1, 1, 1, 2, 2, 2, 2};
    int k = 1;
    v = topKFrequent(v, k);
    for (int num : v)
    {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

vector<int> topKFrequent(vector<int> &nums, int k)
{
    unordered_map<int, int> counts;
    for (int x : nums)
        counts[x]++;

    // Min-heap storing pair<frequency, element>
    // We want frequency first so the PQ sorts by it
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    for (const auto &pair : counts)
    {
        int val = pair.first;
        int freq = pair.second;

        pq.push({freq, val});       // We kept the freq first so that elements in priority queue are sorted according to frequencies rather than the key value
        if (pq.size() > k)
        {
            pq.pop();
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
    return 0;
}
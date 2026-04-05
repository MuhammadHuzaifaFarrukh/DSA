#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

long long pickGifts(vector<int> &gifts, int k)
{
    // 1. Build a Max-Heap from the gifts array - O(n)
    priority_queue<int> pq(gifts.begin(), gifts.end());

    // 2. Perform k operations - O(k log n)
    while (k > 0 && !pq.empty())
    {
        int richest = pq.top();
        pq.pop();

        // Calculate the remaining gifts (floor of sqrt)
        int remaining = floor(sqrt(richest));

        // Push the remaining back into the heap
        pq.push(remaining);
        k--;
    }

    // 3. Sum up all the remaining gifts
    long long totalRemaining = 0;
    while (!pq.empty())
    {
        totalRemaining += pq.top();
        pq.pop();
    }

    return totalRemaining;
}

int main()
{
    return 0;
}
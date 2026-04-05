#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int lastStoneWeight(vector<int> &stones)
{
    priority_queue<int> pq;
    for (int num : stones)
    {
        pq.push(num);
    }
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
    return 0;
}
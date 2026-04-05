#include <iostream>
#include <queue>

using namespace std;

int SumK1K2Smallest(vector<int> &nums, int k1, int k2)
{
    priority_queue<int> pq1;
    priority_queue<int> pq2;

    for (int num : nums)
    {
        pq1.push(num);
        // Keep only k1 Smallest elements in the heap
        if (pq1.size() > k1)
        {
            pq1.pop();
        }
    }

    for (int num : nums)
    {
        pq2.push(num);
        // Keep only (k2-1) Smallest elements in the heap
        if (pq2.size() > k2-1)
        {
            pq2.pop();
        }
    }

    int sum1 = 0, sum2=0;
    while (!pq1.empty())
    {
        sum1 += pq1.top();
        pq1.pop();
    }

    while (!pq2.empty())
    {
        sum2 += pq2.top();
        pq2.pop();
    }
    return (sum2 - sum1);
}
int main()
{
    vector<int> v = {20,8,22,4,12,10,14};
    int k1 = 3, k2 = 6;
    cout << "Sum between K1 and K2 Smallest Elements : " << SumK1K2Smallest(v, k1, k2) << endl;
    return 0;
}
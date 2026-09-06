#include <iostream>
#include <queue>

using namespace std;

// Given an array chocs and an integer 'T' that represents timer (in secs), return the maximum amount of chocolates that we can eat in given time.
// Assume that we can eat chocs[i] in 1 sec.
// After eating chocs[i] in 1 sec , the magician fills the same chocolate again with chocs[i]/2 only if they exist otherwise he doesn't put again.

// Input : [2,4,8,6,10] , T=5
// Output : 33
// Second 1 -> [2,4,8,6,5] , Chocs Eaten = 10.
// Second 2 -> [2,4,4,6,5] , Chocs Eaten = 10+8.
// Second 3 -> [2,4,4,3,5] , Chocs Eaten = 10+8+6.
// Second 4 -> [2,4,4,3,2] , Chocs Eaten = 10+8+6+5.
// Second 5 -> [2,2,4,3,2] , Chocs Eaten = 10+8+6+5+4.

// Using Brute Force / Sorting : O(n^2)

// We use max-heap.
// We keep eating the max number of chocolates.
// We stop if either the pq empties or either the time finishes.
// We also push x/2 if it exists.
// Time : O(n+Tlogn) , T can also be more than 'n'.
// Space : O(n)
int MagicianAndChocolates(vector<int> &chocs, int T)
{
    priority_queue<int> pq(chocs.begin(), chocs.end());
    int total = 0;
    while ((T--) && !pq.empty())
    {
        int x = pq.top();
        total += x;
        pq.pop();

        if (x / 2)
        {
            pq.push(x / 2);
        }
    }
    return total;
}
int main()
{
    vector<int> v = {2, 4, 6, 8, 10};
    int T = 5;
    cout << "Maximum Chocolates eaten are : " << MagicianAndChocolates(v, T) << endl;
    return 0;
}
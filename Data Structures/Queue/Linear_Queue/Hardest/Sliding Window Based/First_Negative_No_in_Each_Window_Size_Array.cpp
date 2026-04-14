#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

/*
// 1)
// Using the sliding logic to push and pop elements like in a circular queue we do
// We use circular queue simulation here.
// Time Complexity Overall : O(nk)


void check_negative(queue<int> q)       // Complexity : O(k)    for single iteration
{
    while (!q.empty())                  // Complexity for (n-k) Iterations : (k+1)(n-k) : O(nk + n - k^2 - k) = O(nk) , We neglected smaller terms
    {
        int x = q.front();
        if (x < 0)
        {
            cout << x << " ";
            return;
        }
        q.pop();
    }
    cout << 0 << " ";
    return;
}
void printing_queue_window(vector<int> &arr, int k)
{
    queue<int> q;
    for (int i = 0; i < k - 1; i++)     // Complexity : k+1 = O(k)
    {
        q.push(arr[i]);
    }

    for (int i = k - 1; i < arr.size(); i++)    // n-k+1 = Complexity : O(n-k)
    {
        q.push(arr[i]);
        check_negative(q);      // Complexity : O(k)
        q.pop();
    }
}
*/

// 2) We store indices of negative numbers only instead of numbers .
// Each time we will check if our window is completed or not 
// If queue is empty then print 0 otherwise check for window (i-k) and then again compare.
// This gets us Time Complexity of O(n-k) = O(n).
void printing_queue_window(vector<int> &v, int k)
{
    queue<int> q;
    for (int i = 0; i < k - 1; i++)     // O(k)
    {
        if (v[i] < 0)
        {
            q.push(i);
        }
    }
    for (int i = k - 1; i < v.size(); i++)  // O(n-k)
    {
        if (v[i] < 0)
        {
            q.push(i);
        }
        if (q.empty())
        {
            cout << 0 << " ";
        }
        else
        {
            if (q.front() <= i - k)
            {
                q.pop();
            }

            if (q.empty())
            {
                cout << 0 << " ";
            }
            else
            {
                cout << v[q.front()] << " ";
            }
        }
    }
}

int main()
{
    vector<int> v = {2, -3, -4, -2, 7, 8, 9, -10};
    int k = 3;
    printing_queue_window(v, k);

    return 0;
}

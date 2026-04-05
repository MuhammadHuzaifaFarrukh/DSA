#include <iostream>
#include <vector>
#include <deque>
using namespace std;
int main()
{
    int n, k;
    cout << "Enter number of readings: ";
    cin >> n;
    vector<int> a(n);
    cout << "Enter readings: ";
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    cout << "Enter window size k: ";
    cin >> k;
    deque<int> dq;
    cout << "Maximum in each window: ";
    for (int i = 0; i < n; i++)
    {
        while (!dq.empty() && dq.front() <= i - k)
        {
            dq.pop_front();
        }
        while (!dq.empty() && a[dq.back()] < a[i])
        {
            dq.pop_back();
        }
        dq.push_back(i);
        if (i >= k - 1) 
        {
            cout << a[dq.front()] << " ";
        }
    }
    cout << "\n";
    return 0;
}
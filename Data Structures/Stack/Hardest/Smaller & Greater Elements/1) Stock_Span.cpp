#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// We are asked to find the number of elements greater than or equal to nums[i] for each nums[i] from size() - 1 to 0.
// This problem becomes like finding next greater on left.

// 1) Brute Force : O(n^2)

// 2) Using Stack (Monotonic) : O(n)
vector<int> stock_span(vector<int> &price)
{
    stack<int> st;
    vector<int> ans(price.size(), 1);
    for (int i = price.size() - 1; i >= 0; i--)
    {
        while (!st.empty() && price[st.top()] < price[i])   // We used < instead of <= to allow equal values to be included also.
        {
            ans[st.top()] = st.top() - i;
            st.pop();
        }
        st.push(i);
    }
    // This check is done if an array like : 60,70,100 comes then no one is updated as there is no greater for each on left side.
    // But we have to put the number of elements smaller than them as well.
    while (!st.empty())
    {
        ans[st.top()] = st.top() + 1;
        st.pop();
    }
    return ans;
}
int main()
{
    vector<int> v = {100, 80, 60, 70, 60, 75, 85};
    v = stock_span(v);
    for (int n : v)
    {
        cout << n << " ";
    }
    return 0;
}
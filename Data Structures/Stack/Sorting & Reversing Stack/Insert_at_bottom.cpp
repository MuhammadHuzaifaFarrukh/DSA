#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// Using Iterative Approach :
// Uses Extra Space O(n)
void insert_at_bottom(stack<int> &st, int x)
{
    if (st.empty())
    {
        st.push(x);
        return;
    }
    stack<int> temp;
    while (!st.empty())
    {
        temp.push(st.top());
        st.pop();
    }
    st.push(x);
    while (!temp.empty())
    {
        st.push(temp.top());
        temp.pop();
    }
}

// Using Recursion :
// Doesn't Use Extra Stack
// Still Memory becomes O(n)
void insertAtBottom(stack<int> &s, int x)
{
    int x = s.top();
    s.pop();
    insertAtBottom(s, x);
    s.push(x);
}

int main()
{
    return 0;
}

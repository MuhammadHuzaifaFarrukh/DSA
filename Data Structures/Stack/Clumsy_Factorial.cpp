#include <stack>
#include <iostream>

using namespace std;
int clumsy(int n)
{
    stack<int> st;
    st.push(n);
    int op = 0; // 0:*, 1:/, 2:+, 3:-

    for (int i = n - 1; i >= 1; i--)
    {
        if (op == 0)
        {
            int val = st.top();
            st.pop();
            st.push(val * i);
        }
        else if (op == 1)
        {
            int val = st.top();
            st.pop();
            st.push(val / i);
        }
        else if (op == 2)
        {
            st.push(i);
        }
        else
        {
            st.push(-i);
        }
        op = (op + 1) % 4;
    }

    int result = 0;
    while (!st.empty())
    {
        result += st.top();
        st.pop();
    }
    return result;
}

int main()
{
    return 0;
}
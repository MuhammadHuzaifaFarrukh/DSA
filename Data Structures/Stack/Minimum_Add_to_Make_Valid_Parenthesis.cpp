#include <string>
#include <stack>
#include <iostream>

using namespace std;
int minAddToMakeValid(string s)
{
    stack<char> st;

    for (char c : s)
    {
        if (c == '(')
        {
            st.push(c);
        }
        else
        {
            // We have a ')'
            if (!st.empty() && st.top() == '(')
            {
                st.pop(); // Found a match!
            }
            else
            {
                st.push(c); // No match, this ')' needs an addition
            }
        }
    }

    // The remaining elements in the stack are all unmatched
    return st.size();
}

int main()
{
    return 0;
}
#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

// We only handle single digit / valued numbers only here.
// For handling multi digit numbers we would need to include spaces as well for separation in input.

bool isOperator(char x)
{
    return (x == '+' || x == '-' || x == '*' || x == '/');
}

string prefixToInfix(string prefix)
{
    stack<string> st;

    // Scan Right to Left
    for (int i = prefix.length() - 1; i >= 0; i--)
    {
        if (isOperator(prefix[i]))
        {
            string op1 = st.top();
            st.pop();
            string op2 = st.top();
            st.pop();

            // Build infix string
            string temp = "(" + op1 + prefix[i] + op2 + ")";
            st.push(temp);
        }
        else
        {
            st.push(string(1, prefix[i]));
        }
    }
    return st.top();
}

int main()
{
    string s = "+*ABC";
    string x = prefixToInfix(s);
    cout<<"Infix : "<<x<<endl;
    return 0;
}

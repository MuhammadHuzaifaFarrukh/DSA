#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

// Print the Bracket Numbers Opening and Closing Ones in order-wise
vector<int> print_bracket_open_close_order(string &s)
{
    int count = 0;
    stack<int> st;
    vector<int> ans;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '(')
        {
            count++;
            st.push(count);
            ans.push_back(count);
        }
        else if (s[i] == ')')
        {
            ans.push_back(st.top());
            st.pop();
        }
    }
    return ans;
}

int main()
{
    string s = "(aa(bdc))p(de)";
    vector<int> v = print_bracket_open_close_order(s);
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

// Remove the adjacent strings that are same and only keep that are not same.
// Return the stack size
int remove_adjacent_strings(vector<string> &s)
{
    stack<string> st;
    for(int i = 0 ; i<s.size() ; i++)
    {
        if(st.empty())
        {
            st.push(s[i]);
        }
        else if(st.top() == s[i])
        {
            st.pop();
        }
        else
        {
            st.push(s[i]);
        }
    }
    return st.size();
}

int main()
{
    return 0;
}
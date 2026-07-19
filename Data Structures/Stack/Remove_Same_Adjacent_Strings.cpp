#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

// Remove the adjacent strings that are same and only keep that are not same.
// Example :s = {"apple", "banana", "banana", "apple", "orange"} , Answer : st.size() = 1 which is {"orange"}
// Return the stack size
// This question is same as the Remove All Adjacent Duplicates In String

// Time : O(n)
// Space : O(n) (stack space if there is no duplicate)
int remove_adjacent_strings(vector<string> &s)
{
    stack<string> st;
    // We can combine the conditions as :
    // Pop only when !st.empty() && st.top() == s[i] otherwise push
    for (int i = 0; i < s.size(); i++)
    {
        if (st.empty())
        {
            st.push(s[i]);
        }
        else if (st.top() == s[i]) // !st.empty() && st.top() == s[i]
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
    vector<string> v = {"apple", "banana", "banana", "apple", "orange"};
    cout << " Stack size after removal of same adjacent strings : " << remove_adjacent_strings(v) << endl;
    return 0;
}

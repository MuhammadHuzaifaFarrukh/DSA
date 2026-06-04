#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

// Given a string , we need to check if its valid parenthesis and if it is ,then we need to check how far it goes valid. (Only one type of parenthesis are given).
// We need to return the length of the longest valid parenthesis in that string. There can be multiple or no valid parenthesis in the string.

// By using stack.
// We will push indices instead of parenthesis in our stack.
// We keep (-1) as our boundary value. We assume that '(' was placed at -1 index (just for our simplification).
// When we find '(' , we simply push in the stack.
// All index values in the stack represent the "Start Boundaries" of the segments currently waiting for the matching closing parenthesis.

// When we find ')' , then we need to see if the stack is empty or not.
// We also pop the top of the stack (just to make our calc not add +1 in length).
// Empty stack means ')' was the first char , or ')' arrived multiple times than the matching opening ones.
// After (-1) index is popped out and we still find ')' without its matching opening bracket , this index becomes our new boundary.
// When closing parenthesis finds its matching opening parenthesis index in stack and stack is not empty then we calculate the substring length : This Index - the Boundary of the Stack. (no need to +1 as we already popped once we found ')' ).

// Time : O(n) , Space : O(n)
int longestValidParentheses(string s)
{
    stack<int> st;
    st.push(-1); // This acts as the initial boundary
    int max_len = 0;

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(')
        {
            st.push(i);
        }
        else
        {
            st.pop();
            if (st.empty())
            {
                // No match, this index is now the new boundary
                st.push(i);
            }
            else
            {
                // Valid match found, calculate length from the last boundary
                max_len = max(max_len, i - st.top());
            }
        }
    }
    return max_len;
}

// By pushing the actual characters , we cannot keep the track of the broken valid parenthesis in middly easily.
// Also that cannot handle the valid parenthesis that occur independently ()()() or nested ones ((())) at the same time.
// Logic becomes more complex.
// It also needs a separate counter (whereas we can simply do (i-st.top() ).
int main()
{
    string s = "()))()()";
    // string t = "((((()))(()()()()()";
    cout << "Longest Valid Parenthesis Substring Length : " << longestValidParentheses(s) << endl;

    return 0;
}
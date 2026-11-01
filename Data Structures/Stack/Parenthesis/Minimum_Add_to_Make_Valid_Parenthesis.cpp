#include <string>
#include <stack>
#include <iostream>

using namespace std;

/*
A parentheses string is valid if and only if:

It is the empty string,
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
You are given a parentheses string s. In one move, you can insert a parenthesis at any position of the string.

For example, if s = "()))", you can insert an opening parenthesis to be "(()))" or a closing parenthesis to be "())))".
Return the minimum number of moves required to make s valid.

Input: s = "())"
Output: 1

Input: s = "((("
Output: 3
*/

// We use stack for this and if we see opening bracket , we add it in our stack.
// If we see closing bracket , we have to see that stack must be non-empty and previous character must be opening bracket.
// Then we have to pop it out.
// If stack's empty or if the previous one is not opening bracket , we add this to our stack as its not matching.
// We could've done this using a variable count , but that fails if we have parenthesis where we have opening more than closing , count won't be able to count them.
// So we run this algorithm similar to valid parenthesis and when it finishes , the number of brackets left will be the minimum ones that we need to add.
// Time Complexity : O(n)
// Space Complexity : O(n)
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

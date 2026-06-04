#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Brute Forcing may take upto O(n^2).

// By using Stack : 
// When we find opening brackets , just push it.
// When we find closing brackets , we need to match it ,and check if stack is empty or not also.
// If stack is empty it means that closing brackets was the first character or closing brackets was repeated many times.
// If stack is not empty , it needs to be matched with its correct closing brackets pair. (To avoid this : '({)}' where ) is closed before }  )
// If it matches , we pop this opening bracket which is at the top of stack.
// If a mismatch appears , it is not valid.
// Time : O(n) and Space : O(n)
bool isValid(string s)
{
    stack<char> st;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[')
        {
            st.push(s[i]);
        }
        else
        {
            if (st.empty())
            {
                return false;
            }

            char top = st.top();
            if ((s[i] == ')' && top == '(') || (s[i] == '}' && top == '{') || (s[i] == ']' && top == '['))
            {
                st.pop(); // Matched!
            }
            else
            {
                return false; // Mismatch!
            }
        }
    }
    return st.empty(); // Stack is Emptied once all chars popped out , and if empty string case given then this gets handled as well.
}

int main()
{
    string test = "{[()]}";
    if (isValid(test))
    {
        cout << "Valid " << endl;
    }
    else
    {
        cout << "Invalid " << endl;
    }
    return 0;
}

// Another (Same) Method but this time storing indices in the stack instead of characters :
/*
bool isValid(string s)
{
    stack<int> st;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[')
        {
            st.push(i);
        }
        else
        {
            if (st.empty())
            {
                return false;
            }

            char topChar = s[st.top()];
            if ((s[i] == ')' && topChar == '(') || (s[i] == '}' && topChar == '{') || (s[i] == ']' && topChar == '['))
            {
                st.pop();
            }
            else
            {
                return false;
            }
        }
    }
    return st.empty();
}
*/

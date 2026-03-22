#include <iostream>
#include <string>
#include <stack>

using namespace std;

// You can either evaluate directly or use conversion.
// Converting to postfix is easier to debug and evaulate an expression.

int calculate(string s)
{
    stack<int> st;
    int current_result = 0;
    int sign = 1; // 1 for '+', -1 for '-'

    for (int i = 0; i < s.length(); i++)
    {
        // 1. Skip whitespace
        if (s[i] == ' ')
            continue;

        // 2. If it's a digit, find the full number and use stoi
        if (isdigit(s[i]))
        {
            int start = i;
            while (i < s.length() && isdigit(s[i]))
            {
                i++;
            }
            // Extract substring and convert
            string numStr = s.substr(start, i - start);
            int val = stoi(numStr);

            current_result += sign * val;
            i--; // Step back because the for-loop will increment i
        }
        else if (s[i] == '+')
        {
            sign = 1;
        }
        else if (s[i] == '-')
        {
            sign = -1;
        }
        else if (s[i] == '(')
        {
            // Push current result and sign to "save" state
            st.push(current_result);
            st.push(sign);

            // Reset for expression inside brackets
            current_result = 0;
            sign = 1;
        }
        else if (s[i] == ')')
        {
            // Pop sign that was before '(', then pop the previous result
            int prev_sign = st.top();
            st.pop();
            int prev_result = st.top();
            st.pop();

            current_result = prev_result + (prev_sign * current_result);
        }
    }
    return current_result;
}

int main()
{
    // Test case: 10 plus the result of (40 - 5)
    string expr = "10 + ( 40 - 5 )";
    cout << "Result: " << calculate(expr) << endl;
    return 0;
}
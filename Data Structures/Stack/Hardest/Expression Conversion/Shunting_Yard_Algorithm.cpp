#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Shunting Yard Algorithm is used to convert Infix to Postfix Expression using Stack.
// Converting to postfix is easier to debug and evaluate an expression
// We only handle single digit / valued numbers only here.
// For handling multi digit numbers we would need to include spaces as well for separation in output.

// Function to return precedence of operators.
int prec(char c)
{
    if (c == '^')
    {
        return 3;
    }
    if (c == '*' || c == '/')
    {
        return 2;
    }
    if (c == '+' || c == '-')
    {
        return 1;
    }
    return -1; // If its not any operator like bracket or operands
}

string infixToPostfix(string s)
{
    stack<char> st;
    string result = "";

    for (int i = 0; i < s.length(); i++)
    {
        char c = s[i];

        // 1. If operand, add to result
        if (isalpha(c))
        {
            result += c;
        }
        // 2. If '(', push to stack
        else if (c == '(')
        {
            st.push('(');
        }
        // 3. If ')', pop until '('
        else if (c == ')')
        {
            while (!st.empty() && st.top() != '(')
            {
                result += st.top();
                st.pop();
            }
            st.pop(); // Remove '('
        }
        // 4. If operator
        else
        {
            while (!st.empty() && prec(s[i]) <= prec(st.top()))
            {
                result += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    // 5. Pop remaining operators
    while (!st.empty())
    {
        result += st.top();
        st.pop();
    }

    return result;
}

int main()
{
    string exp = "a+b*c";
    cout << "Postfix: " << infixToPostfix(exp) << endl;
    return 0;
}

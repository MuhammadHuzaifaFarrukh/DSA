#include <iostream>
#include <stack>
#include <string>

using namespace std;

// We only handle single digit / valued numbers only here.
// For handling multi digit numbers we would need to include spaces as well for separation in input.

bool isOperator(char x)
{
    return (x == '+' || x == '-' || x == '*' || x == '/' || x == '^');
}

string postfixToInfix(string postfix)
{
    stack<string> st;

    for (int i = 0; i < postfix.length(); i++)
    {
        char c = postfix[i];

        // 1. If operand, push as string
        if (isdigit(c))
        {
            string op(1, c); // Convert char to string
            st.push(op);        // We could also do : st.push(to_string(op))
        }
        // 2. If operator
        else if (isOperator(c))
        {
            string op2 = st.top();
            st.pop();
            string op1 = st.top();
            st.pop();

            // Build the infix string
            string temp = "(" + op1 + c + op2 + ")";
            st.push(temp);
        }
    }

    return st.top();
}

int main()
{
    string post_exp = "abc*+";
    cout << "Infix: " << postfixToInfix(post_exp) << endl;
    // Output: (a+(b*c))
    return 0;
}

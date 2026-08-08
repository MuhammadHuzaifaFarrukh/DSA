#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

// We can either evaluate directly or use conversion.
// Converting to postfix is easier to debug and evaulate an expression.
// We are given tokens[] array so multi-digits are handled automatically , no need to parse them here.

int evalPrefix(vector<string> &tokens)
{
    stack<int> st;

    for (int i = tokens.size() - 1; i >= 0; i--)
    {
        string s = tokens[i];

        if (isdigit(s[0]) || (s.size() > 1 && isdigit(s[1])))
        {
            st.push(stoi(s));
        }
        else
        {
            int op1 = st.top();
            st.pop();
            int op2 = st.top();
            st.pop();

            if (s == "+")
            {
                st.push(op1 + op2);
            }
            else if (s == "-")
            {
                st.push(op1 - op2);
            }
            else if (s == "*")
            {
                st.push(op1 * op2);
            }
            else if (s == "/")
            {
                if (op2 == 0)
                {
                    cout << "Not Possible Divison by Zero , Converting Operand 0 to 1" << endl;
                    op2 = 1;
                    // return 0;
                }
                st.push(op1 / op2);
            }
        }
    }
    return st.top();
}

int main()
{
    int n;
    cout << "Enter total number of tokens: ";
    cin >> n;

    vector<string> tokens;
    cout << "\nEnter " << n << " tokens (operands or operators like +, -, *, /):\n";

    for (int i = 0; i < n; i++)
    {
        string token;
        cout << "Token [" << i + 1 << "]: ";
        cin >> token; // Automatically handles whitespaces and single tokens cleanly
        tokens.push_back(token);
    }

    // Display the entered expression cleanly
    cout << "\nEvaluating Prefix Expression: [ ";
    for (const string &t : tokens)
    {
        cout << t << " ";
    }
    cout << "]\n";

    // Compute and display result
    int result = evalPrefix(tokens);
    cout << "Result: " << result << endl;

    return 0;
}

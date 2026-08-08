#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

// We are given tokens[] array so multi-digits are handled automatically , no need to parse them here.

int evalRPN(vector<string> &tokens)
{
    stack<int> s;
    int result = 0;
    int op1 = 1;
    int op2 = 1;
    for (int i = 0; i < tokens.size(); i++)
    {
        if (tokens[i] != "+" && tokens[i] != "-" && tokens[i] != "*" && tokens[i] != "/")
        {
            s.push(stoi(tokens[i]));
        }
        else // Time to do Operations :
        {
            op2 = s.top();
            s.pop();
            op1 = s.top();
            s.pop();
            if (tokens[i] == "+")
            {
                s.push(op1 + op2);
            }
            else if (tokens[i] == "-")
            {
                s.push(op1 - op2);
            }
            else if (tokens[i] == "*")
            {
                s.push(op1 * op2);
            }
            else if (tokens[i] == "/")
            {
                if (op2 == 0)
                {
                    cout << "Division by Zero , Not Possible , changing Operand to 1" << endl;
                    op2 = 1;
                }
                s.push(op1 / op2);
            }
        }
    }
    if (s.empty()) // For Handling empty vector or malformed input vector
    {
        return 0;
    }
    return s.top();
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
        getline(cin, token);
        tokens.push_back(token);
    }

    cout << "\nEvaluating RPN Expression: [ ";
    for (string t : tokens)
    {
        cout << t << " ";
    }
    cout << "]\n";

    // Compute and display result
    int result = evalRPN(tokens);
    cout << "Result: " << result << endl;

    return 0;
}

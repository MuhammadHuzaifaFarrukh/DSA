#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

// Converting to postfix is easier to debug and evaulate an expression

bool isOperator(char x)
{
    return (x == '+' || x == '-' || x == '*' || x == '/');
}

string prefixToPostfix(string pre_exp)
{
    stack<string> s;
    // Scan Right to Left
    for (int i = pre_exp.length() - 1; i >= 0; i--)
    {
        if (isOperator(pre_exp[i]))
        {
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
            // Postfix order: Operand1 + Operand2 + Operator
            string temp = op1 + op2 + pre_exp[i];
            s.push(temp);
        }
        else
        {
            s.push(string(1, pre_exp[i]));
        }
    }
    return s.top();
}

int main()
{
    string s = "+*AVC";
    string x = prefixToPostfix(s);
    cout<<"Postfix : "<<x<<endl;
    return 0;
}
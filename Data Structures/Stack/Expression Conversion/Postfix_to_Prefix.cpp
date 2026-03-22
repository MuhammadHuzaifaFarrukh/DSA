#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

bool isOperator(char x)
{
    return (x == '+' || x == '-' || x == '*' || x == '/');
}

string postfixToPrefix(string post_exp)
{
    stack<string> s;
    for (int i = 0; i < post_exp.length(); i++)
    {
        if (isOperator(post_exp[i]))
        {
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
            // Prefix order: Operator + Operand2 + Operand1
            string temp = post_exp[i] + op2 + op1;
            s.push(temp);
        }
        else
        {
            s.push(string(1, post_exp[i]));
        }
    }
    return s.top();
}

int main()
{
    string x = "ABC+*";
    string s = postfixToPrefix(x);
    cout<<"Prefix : "<<s<<endl;
    return 0;
}
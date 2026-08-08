#include <iostream>
#include <stack>
#include <string>

using namespace std;

// We use shunting algorithm again in infix to prefix like we did in infix to postfix.
// You have two options.
// 1) Apply shunting algorithm from right to left and take ( for ) and ) for ( and reverse the output.
// 2) Reverse the whole string e.g : (A+B)*C -> C*(B+A) , then apply shunting yard algorithm and reverse the output.

// We go for the 2nd option here.
// We only handle single digit / valued numbers only here.
// For handling multi digit numbers we would need to include spaces as well for separation in output.

// Manual string reverse function
void reverseString(string &s)
{
    int n = s.length();
    for (int i = 0; i < n / 2; i++)
    {
        char temp = s[i];
        s[i] = s[n - i - 1];
        s[n - i - 1] = temp;
    }
}

// Precedence levels
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
    return -1;
}

string infixToPrefix(string infix)
{
    // 1. Manually Reverse
    reverseString(infix);

    // 2. Swap Brackets
    for (int i = 0; i < infix.length(); i++)
    {
        if (infix[i] == '(')
        {
            infix[i] = ')';
        }
        else if (infix[i] == ')')
        {
            infix[i] = '(';
        }
    }

    // 3. Shunting Yard (Modified for Prefix)
    stack<char> st;
    string tempPostfix = "";

    for (int i = 0; i < infix.length(); i++)
    {
        char c = infix[i];

        if (isalpha(c))
        {
            tempPostfix += c;
        }
        else if (c == '(')
        {
            st.push('(');
        }
        else if (c == ')')
        {
            while (!st.empty() && st.top() != '(')
            {
                tempPostfix += st.top();
                st.pop();
            }
            st.pop(); // Pop '('
        }
        else
        {
            // Tweak: For prefix reversal, we pop only if top has HIGHER precedence
            // (Strictly < instead of <=)
            while (!st.empty() && prec(c) < prec(st.top()))
            {
                tempPostfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    while (!st.empty())
    {
        tempPostfix += st.top();
        st.pop();
    }

    // 4. Manually Reverse the result back
    reverseString(tempPostfix);

    return tempPostfix;
}

int main()
{
    string exp = "(A+B)*C";
    cout << "Prefix: " << infixToPrefix(exp) << endl;
    // Output: *+ABC
    return 0;
}

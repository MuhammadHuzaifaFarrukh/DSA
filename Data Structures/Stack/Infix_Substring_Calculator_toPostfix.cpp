#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cmath>
using namespace std;

int vars[26] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};

bool alphabets(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return true;
    }
    return false;
}

int prec(char c)
{
    if (c == '^')
        return 3;
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    return -1;
}

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

bool validate(string s)
{
    if (s.empty())
        return false;

    // 1. Check Start/End: Cannot start or end with a binary operator
    if (isOperator(s[0]) || isOperator(s[s.length() - 1]))
        return false;

    stack<char> st;
    bool hasOperand = false;

    for (int i = 0; i < s.length(); i++)
    {
        // Track if we've seen at least one variable (a-z)
        if (alphabets(s[i]))
        {
            hasOperand = true;
        }

        // 2. Parenthesis Matching
        if (s[i] == '(')
        {
            st.push('(');
        }
        else if (s[i] == ')')
        {
            if (st.empty())
            {
                return false;
            }
            // We won't add another if checking that if ) then ( cause we have already one parenthesis type here '()'
            st.pop();
        }

        // 3. Check for consecutive operators (e.g., "a++b")
        if (i > 0 && isOperator(s[i]) && isOperator(s[i - 1]))
        {
            return false;
        }

        // 4. Check for empty parentheses or hidden operators like "(+a)"
        // +,-,*,^,/ Operators are allowed only on the Binary Operators.
        if (i > 0 && s[i - 1] == '(' && isOperator(s[i]))
        {
            return false;
        }
    }

    // Must have at least one operand and balanced parentheses
    return st.empty() && hasOperand;
}

vector<char> toPostfix(string s)
{
    stack<char> st;
    vector<char> result;

    for (int i = 0; i < s.length(); i++)
    {
        char c = s[i];

        if (alphabets(c))
        {
            result.push_back(c);
        }

        else if (c == '(')
        {
            st.push('(');
        }

        else if (c == ')')
        {
            while (!st.empty() && st.top() != '(')
            {
                result.push_back(st.top());
                st.pop();
            }
            if (!st.empty())
            {
                st.pop();
            }
        }
        else
        {
            // ^ has associativity from right to left if we have two or more ^ in an expression.
            while (!st.empty() && st.top() != '(')
            {
                if (c == '^')
                {
                    // Right-associative: pop only if top has STRICTLY HIGHER precedence
                    if (prec(st.top()) > prec(c))
                    {
                        result.push_back(st.top());
                        st.pop();
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    // Left-associative: pop if top has EQUAL OR HIGHER precedence
                    if (prec(st.top()) >= prec(c))
                    {
                        result.push_back(st.top());
                        st.pop();
                    }
                    else
                    {
                        break;
                    }
                }
            }
            st.push(c);
        }
    }

    while (!st.empty())
    {
        result.push_back(st.top());
        st.pop();
    }

    return result;
}

bool evalPostfix(vector<char> pf, int &result)
{
    stack<int> st;

    for (int i = 0; i < pf.size(); i++)
    {
        if (alphabets(pf[i]))
        {
            st.push(vars[pf[i] - 'a']);
        }
        else
        {
            int op1, op2;
            if (st.size() < 2)
            {
                return false;
            }

            op2 = st.top();
            st.pop();
            op1 = st.top();
            st.pop();
            if (pf[i] == '+')
            {
                st.push(op1 + op2);
            }
            else if (pf[i] == '-')
            {
                st.push(op1 - op2);
            }
            else if (pf[i] == '*')
            {
                st.push(op1 * op2);
            }
            else if (pf[i] == '/')
            {
                if (op2 == 0)
                {
                    return 0;
                }
                st.push(op1 / op2);
            }
            else if (pf[i] == '^')
            {
                st.push(round(pow(op1, op2))); // Returns a double so use round() for integer division
            }
        }
    }
    if (st.empty())
    {
        return false;
    }
    result = st.top();
    return true;
}

int main()
{
    string s;
    cout << "Enter string : ";
    getline(cin, s);

    int n;
    cout << "Enter queries : ";
    cin >> n;
    cin.ignore();

    int i = 1;
    while (n--)
    {
        string t;
        cout << "Query # " << i << " : ";
        getline(cin, t);

        // For E L R , we are assuming that all have spaces between them.
        // As the restriction is only on the infix which doesn't have any space.
        // We will achieve this E L R by 4 loops.
        // This could also have been done if we just took inputs separately i.e for E , and two integers L and R.

        if (t[0] == 'E')
        {
            string sL = "", sR = "";
            int i = 1;

            // Skip non-digits to find L
            while (i < t.length() && !isdigit(t[i]))
                i++;
            // Collect digits for L
            while (i < t.length() && isdigit(t[i]))
                sL += t[i++];
            // Skip non-digits to find R
            while (i < t.length() && !isdigit(t[i]))
                i++;
            // Collect digits for R
            while (i < t.length() && isdigit(t[i]))
                sR += t[i++];

            int L = stoi(sL);
            int R = stoi(sR);

            string n = s.substr(L, R - L + 1);

            if (validate(n))
            {
                cout << "Structure is Valid \n";
                vector<char> postfix = toPostfix(n);
                int result = 0;
                if (evalPostfix(postfix, result))
                {
                    cout << "Result : " << result << endl;
                }
                else
                {
                    cout << "Result : Invalid Division by Zero " << endl;
                }
            }
            else
            {
                cout << "Structure is Invalid \n";
            }
        }
        else if (t[0] == 'U')
        {
            char varName = ' ';
            string sVal = "";

            for (int i = 1; i < t.length(); i++)
            {
                // Find the variable letter (a-z)
                if (t[i] >= 'a' && t[i] <= 'z')
                {
                    varName = t[i];
                }
                // Find the value (including negative sign and digits)
                else if (isdigit(t[i]) || t[i] == '-')
                {
                    sVal += t[i];
                }
            }
            if (varName != ' ' && !sVal.empty())
            {
                vars[varName - 'a'] = stoi(sVal); // Correctly updates the global array
            }
        }
        i++;
    }

    return 0;
}

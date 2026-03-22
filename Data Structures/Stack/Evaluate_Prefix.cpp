#include <iostream>
#include <stack>
#include <string>
using namespace std;


// You can either evaluate directly or use conversion.
// Converting to postfix is easier to debug and evaulate an expression.

int evalPrefix(string tokens[], int n)
{
    stack<int> st;

    for (int i = n - 1; i >= 0; i--)
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
                    return 0; 
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
    cout << "Enter n : ";
    cin >> n;

    cin.clear();
    cin.ignore();
    string *s = new string[n];
    cout << "Enter whole expression :" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter a string [" << i << "] : ";
        getline(cin, s[i]);
        cout << endl;
    }
    int x = evalPrefix(s, n);
    cout << "Answer is : " << x << endl;

    delete[] s;
    return 0;
}
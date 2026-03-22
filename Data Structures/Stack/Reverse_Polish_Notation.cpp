#include <iostream>
#include <stack>
#include <string>
using namespace std;

int reverse_polish_notation(string tokens[], int n)
{
    std::stack<int> s;
    int op1 = 1;
    int op2 = 1;
    for (int i = 0; i < n ; i++)
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
                s.push(op1 / op2);
            }
        }
    }
    return s.top();
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
        cout<<endl;
    }
    int x = reverse_polish_notation(s, n);
    cout << "Answer is : " << x << endl;

    delete[] s;
    return 0;
}
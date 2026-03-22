#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isEqual(string s, string t)
{
    stack<char> stackS, stackT;

    for (char ch : s)
    {
        if (ch != '#')
        {
            stackS.push(ch);
        }
        else if (!stackS.empty())
        {
            stackS.pop();
        }
    }


    for (char ch : t)
    {
        if (ch != '#')
        {
            stackT.push(ch);
        }
        else if (!stackT.empty())
        {
            stackT.pop();
        }
    }

    if (stackS.size() != stackT.size())
    {
        return false;
    }

    while (!stackS.empty())
    {
        if (stackS.top() != stackT.top())
        {
            return false;
        }
        stackS.pop();
        stackT.pop();
    }

    return true;
}

int main()
{
//    string s = "ad##c";
//    string t = "ad#c";
    string s = "a##c";
    string t = "#a#c";
    if (isEqual(s, t))
    {
        cout << "Output: true" << endl;
    }
    else
    {
        cout << "Output: false" << endl;
    }

    return 0;
}

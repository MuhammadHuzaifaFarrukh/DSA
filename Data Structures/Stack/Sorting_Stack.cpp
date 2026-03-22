#include <iostream>
#include <stack>
using namespace std;

void sortStack(stack<int> &s)
{
    stack<int> tmpStack;

    while (!s.empty())
    {
        int curr = s.top();
        s.pop();

        // While temporary stack is not empty and top is greater than curr
        while (!tmpStack.empty() && tmpStack.top() > curr)
        {
            s.push(tmpStack.top());
            tmpStack.pop();
        }

        tmpStack.push(curr);
    }

    // Move everything back to original stack if you want it sorted ascending
    while (!tmpStack.empty())
    {
        s.push(tmpStack.top());
        tmpStack.pop();
    }
}

int main()
{
    stack<int> s;

    s.push(4);
    s.push(6);
    s.push(1);
    s.push(2);
    s.push(9);
    s.push(5);

    sortStack(s);
    while (!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }

    return 0;
}
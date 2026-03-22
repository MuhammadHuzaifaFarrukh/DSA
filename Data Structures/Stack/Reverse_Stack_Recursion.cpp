#include <iostream>
#include <string>
#include <stack>

using namespace std;

// 1)
// This reverses the stack without an extra stack.
// However in recursion , the space complexity is already O(n).
// This recursive function works without any helper function.
void reverse_rec(stack<int> &s, int target = -1, bool inserting = false)
{
    if (s.empty() && !inserting)
        return;

    if (!inserting)
    {
        int temp = s.top();
        s.pop();
        reverse_rec(s);             // Peeling
        reverse_rec(s, temp, true); // This is just calling the "insert" logic
    }
    else
    {
        if (s.empty())
        {
            s.push(target);
            return;
        }
        int temp = s.top();
        s.pop();
        reverse_rec(s, target, true);
        s.push(temp);
    }
}

// 2)
// This uses a helper function
// The Space Complexity is still O(n) in this recursive version.
void insertAtBottom(stack<int> &s, int val)
{
    if (s.empty())
    {
        s.push(val);
        return;
    }
    int topVal = s.top();
    s.pop();
    insertAtBottom(s, val);
    s.push(topVal);
}

void reverse_rec2(stack<int> &s)
{
    if (s.empty())
        return;

    int topVal = s.top();
    s.pop();
    reverse_rec2(s);
    insertAtBottom(s, topVal);
}

// 3)
// This function uses another stack making space complexity O(n).
// This is the best and efficient version.
stack<int> reverse(stack<int> &a)
{
    stack<int> b;
    while (!a.empty())
    {
        b.push(a.top());
        a.pop();
    }
    return b;
}

int main()
{
    stack<int> s;

    s.push(9);
    s.push(6);
    s.push(5);
    s.push(4);
    s.push(2);
    s.push(1);
    
    reverse(s);
    // reverse_rec(s);
    // reverse_rec2(s);

    while (!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }
    return 0;
}
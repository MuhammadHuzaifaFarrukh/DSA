#include <iostream>
#include <stack>
#include <queue>

using namespace std;

class MyQueue
{
    stack<int> s1;

public:
    MyQueue()
    {
    }

    void push(int x)
    {
        s1.push(x);
    }

    int pop()       // This pop() also removes the value and returns it .
    {
        int x = 0;
        if (!s1.empty())
        {
            stack<int> s2;
            while (!s1.empty())
            {
                s2.push(s1.top());
                s1.pop();
            }
            x = s2.top();
            s2.pop();
            while (!s2.empty())
            {
                s1.push(s2.top());
                s2.pop();
            }
        }
        return x;
    }

    int peek()      // Returns the last element , not remove
    {
        stack<int> s2;
        s2 = s1;
        int x = 0;
        while (!s2.empty())
        {
            x = s2.top();
            s2.pop();
        }
        return x;
    }

    bool empty()
    {
        return s1.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

int main()
{
    return 0;
}
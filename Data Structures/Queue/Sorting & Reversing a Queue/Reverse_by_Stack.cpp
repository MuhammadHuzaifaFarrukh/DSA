#include <iostream>
#include <queue>
#include <stack> // Required for this method

using namespace std;

void reverseByStack(queue<int> &q)
{
    stack<int> s;

    // Step 1: Move all elements from Queue to Stack
    while (!q.empty())
    {
        s.push(q.front());
        q.pop();
    }

    // Step 2: Move all elements back from Stack to Queue
    while (!s.empty())
    {
        q.push(s.top());
        s.pop();
    }
}

int main()
{
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);

    reverseByStack(q);

    while(!q.empty())
    {
        q.pop();
        cout<<q.front()<<" ";
    }
    cout<<endl;
    return 0;
}
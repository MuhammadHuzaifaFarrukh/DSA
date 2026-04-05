#include <iostream>
#include <queue>
#include <stack> // Required for this method

using namespace std;

void reverseByRecursion(queue<int> &q)
{
    // Base Case: If queue is empty, stop
    if (q.empty())
    {
        return;
    }

    // Step 1: Dequeue the front element and store it in the current function call
    int val = q.front();
    q.pop();

    // Step 2: Recursive call for the remaining elements
    reverseByRecursion(q);

    // Step 3: Enqueue the stored element back (this happens as the recursion unwinds)
    q.push(val);
}

int main()
{
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);

    reverseByRecursion(q);

    while (!q.empty())
    {
        q.pop();
        cout << q.front() << " ";
    }
    cout << endl;
    return 0;
}
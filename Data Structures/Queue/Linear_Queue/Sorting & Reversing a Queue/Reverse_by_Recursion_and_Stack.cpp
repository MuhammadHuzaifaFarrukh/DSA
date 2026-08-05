#include <iostream>
#include <queue>
#include <stack> // Required for this method

using namespace std;

// 1) By using recursion :
// We just pop out all the elements of the queue until its empty.
// Then we put those elements in the order they were popped out.
// Suppose we put 1,2,3,4,5 in the queue.
// Now we pop all out calling the function again and again.
// Now we had the function calls when queue became empty : 5,4,3,2,1.
// So queue is filled exactly like this : 5,4,3,2,1.
// We didn't need to call any insertAtBottom function to place at bottom because queue data structure is FIFO and the first one that we popped out , is at the last in our call stack.
// Call stack reverses the elements of our queue , the last element popped out of the queue is the first one in the call stack.
// So we just follow the order of the call stack.
// Time : O(n)
// Space : O(n)
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

// 2) Reverse by stack.
// Time : O(n)
// Space : O(n)
void reverseByStack(queue<int> &q)
{
    stack<int> st;
    while (!q.empty())
    {
        st.push(q.front());
        q.pop();
    }
    while (!st.empty())
    {
        q.push(st.top());
        st.pop();
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

    reverseByRecursion(q);
    // reverseByStack(q);
    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
    return 0;
}
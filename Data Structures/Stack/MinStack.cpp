#include <iostream>
#include <stack>

using namespace std;

/*
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

Implement the MinStack class:

MinStack() initializes the stack object.
void push(int value) pushes the element value onto the stack.
void pop() removes the element on the top of the stack.
int top() gets the top element of the stack.
int getMin() retrieves the minimum element in the stack.
You must implement a solution with O(1) time complexity for each function.
*/

// We can use 2 Stacks
// One for normal values.
// One for the minimum
// All values , minimum or not are stored in our st stack.
// When we see first value , that can be our minimum so we also save it in our min stack.
// Then if we encounter any value less than the last one in min stack , then we save it again inside minstack.
// Our min stack contains the minimum at each depth of the stack.
// It must always have the exact same number of elements as st, growing and shrinking in lockstep.

// Time for each function : O(1)
// Space : O(2n) = O(n)
class MinStack
{
public:
    stack<int> st;
    stack<int> minSt;

    void push(int value)
    {
        st.push(value);                            // Any value encountered is pushed here.
        if (minSt.empty() || value <= minSt.top()) // If we get any value <= min stack top , then it goes inside minstack otherwise the previous value of min stack is again pushed repeating it. This is done to keep the elements of the min stack same as the st stack for our ease.
        {
            minSt.push(value);
        }
        else
        {
            minSt.push(minSt.top());
        }
    }

    void pop()
    {
        st.pop();
        minSt.pop();
        // We must use pop for both because we are putting values at each step for both stacks.
        // Even though minSt may contain repeated min values , we still pop it to keep it at same number of elements as st stack for our ease.
    }

    int top()
    {
        return st.top();
        // We can just return the stack's top.
    }

    int getMin()
    {
        return minSt.top();
        // From our setup , we can easily return the minSt.top()
    }
};

int main()
{
    return 0;
}
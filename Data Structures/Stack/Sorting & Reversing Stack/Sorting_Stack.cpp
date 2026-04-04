#include <iostream>
#include <stack>
#include <limits.h>
using namespace std;

// Used Insertion Sort (Natural) O(n^2):
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

// Bubble Sort O(n^2):
void bubbleSortStack(stack<int> &s)
{
    int n = s.size();

    for (int pass = 0; pass < n - 1; pass++)
    {
        stack<int> tmpStack;

        for (int i = 0; i < n - 1 - pass; i++)
        {
            int first = s.top();
            s.pop();
            int second = s.top();
            s.pop();

            // larger goes down (to tmpStack first)
            if (first > second)
            {
                tmpStack.push(first);
                s.push(second);
            }
            else
            {
                tmpStack.push(second);
                s.push(first);
            }
        }

        // pour tmpStack back to s
        while (!tmpStack.empty())
        {
            s.push(tmpStack.top());
            tmpStack.pop();
        }
    }
}

// Selection Sort O(n^2):
void selectionSortStack(stack<int> &s)
{
    int n = s.size();

    for (int pass = 0; pass < n - 1; pass++)
    {
        // Step 1: find minimum
        stack<int> tmpStack;
        int size = s.size();
        int minVal = INT_MAX;

        // find min
        for (int i = 0; i < size; i++)
        {
            int curr = s.top();
            s.pop();
            if (curr < minVal)
                minVal = curr;
            tmpStack.push(curr);
        }

        // pour back to s
        while (!tmpStack.empty())
        {
            s.push(tmpStack.top());
            tmpStack.pop();
        }

        // Step 2: remove minVal from s
        bool removed = false;
        for (int i = 0; i < size; i++)
        {
            int curr = s.top();
            s.pop();
            if (curr == minVal && !removed)
            {
                removed = true; // skip it (removes it)
            }
            else
            {
                tmpStack.push(curr);
            }
        }

        // pour back to s
        while (!tmpStack.empty())
        {
            s.push(tmpStack.top());
            tmpStack.pop();
        }

        // Step 3: push minVal to bottom
        // to send to bottom, pour everything to tmp, push min, pour back
        while (!s.empty())
        {
            tmpStack.push(s.top());
            s.pop();
        }
        tmpStack.push(minVal);
        while (!tmpStack.empty())
        {
            s.push(tmpStack.top());
            tmpStack.pop();
        }
    }
}

// Use a vector to take all stack elements and then sort them efficiently and then again put back in the stack.

int main()
{

    return 0;
}

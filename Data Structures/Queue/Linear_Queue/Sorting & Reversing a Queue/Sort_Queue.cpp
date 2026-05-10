#include <iostream>
#include <queue>
#include <limits.h>
using namespace std;

// Complexity O(n^2)
// Not Stable to use on a Queue
queue<int> selectionSortQueue(queue<int> q)
{
    queue<int> sorted;

    while (!q.empty())
    {
        // Step 1: Find minimum in queue
        int size = q.size();
        int minVal = INT_MAX;

        // peek all elements to find min
        for (int i = 0; i < size; i++)
        {
            int curr = q.front();
            q.pop();
            if (curr < minVal)
                minVal = curr;
            q.push(curr); // put back
        }

        // Step 2: Remove FIRST occurrence of minVal
        bool removed = false;
        for (int i = 0; i < size; i++)
        {
            int curr = q.front();
            q.pop();
            if (curr == minVal && !removed)
            {
                removed = true; // skip it (this removes it)
            }
            else
            {
                q.push(curr); // put back everything else
            }
        }

        // Step 3: minVal is now sorted
        sorted.push(minVal);
    }

    return sorted;
}

// Stable than Selection Sort even if Complexity is same O(n^2)
queue<int> bubbleSortQueue(queue<int> q)
{
    int n = q.size();

    for (int pass = 0; pass < n - 1; pass++)
    {
        int comparisons = n - 1 - pass; // each pass, one less comparison needed

        for (int i = 0; i < comparisons; i++)
        {
            // grab front two elements
            int first = q.front();
            q.pop();
            int second = q.front();
            q.pop();

            // put smaller first, larger second
            if (first <= second)
            {
                q.push(first);
                q.push(second);
            }
            else
            {
                q.push(second);
                q.push(first);
            }
        }

        // move the last unsorted element to rear
        // (it's already at front after comparisons, just cycle it)
        int last = q.front();
        q.pop();
        q.push(last);
    }

    return q;
}

// Then we can also do that put all queue elements in vector , sort it efficiently and put them in queue back.

// Other Sorting may not work on a queue.

int main()
{
    queue<int> q;
    q.push(5);
    q.push(2);
    q.push(8);
    q.push(1);
    q.push(9);
    q.push(3);

    cout << "Original: ";
    queue<int> temp = q;
    while (!temp.empty())
    {
        cout << temp.front() << " ";
        temp.pop();
    }

    queue<int> sorted = bubbleSortQueue(q);

    cout << "\nSorted:   ";
    while (!sorted.empty())
    {
        cout << sorted.front() << " ";
        sorted.pop();
    }
    cout << endl;

    return 0;
}
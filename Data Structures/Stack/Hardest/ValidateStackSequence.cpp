#include <iostream>
#include <stack>
#include <vector>
using namespace std;

bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
{
    std::stack<int> st; // Real stack container
    int j = 0;          // Pointer to track where we are in 'popped'

    for (int x : pushed)
    {
        st.push(x); // Push the current element onto the stack

        // Check if the top of the stack is what we need to pop next
        // We use a while loop because one push might allow multiple pops
        while (!st.empty() && st.top() == popped[j])
        {
            st.pop();
            j++; // Move to the next element we're looking for in 'popped'
        }
    }

    // If the sequence is valid, we should have popped everything we pushed
    return st.empty();
}

int main()
{

    return 0;
}
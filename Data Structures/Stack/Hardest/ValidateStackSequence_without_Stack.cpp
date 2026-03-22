#include <iostream>
#include <stack>
#include <vector>
using namespace std;
bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
{
    vector<int> st; // Our simulation stack
    int j = 0;      // Pointer for the popped array

    for (int x : pushed)
    {
        st.push_back(x); // Always push the current element

        // While stack isn't empty and the top matches the next popped element
        while (!st.empty() && st.back() == popped[j])
        {
            st.pop_back();
            j++; // We found a match, move to the next popped requirement
        }
    }

    // If all elements were popped correctly, the stack will be empty
    return st.empty();
}

int main()
{
    
    return 0;
}
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

// This is another variant of next greater element.
// We have to find the next greater element for each element , even if we can find for last element
// We have to treat our given array as circular array.


// We treat nums1 and num2 = nums only
// And Find the next greater for each element in the nums by treating it as circular array.
// Total elements 'n' so we check each element 2*n-1 times .
// As the last element has to be checked again in a rotation one more time.
vector<int> nextGreaterElements(vector<int> &nums)
{
    int n = nums.size();
    vector<int> res(n, -1); // Initialize all to -1
    stack<int> st;

    for (int i = 0; i < 2 * n; i++)
    {
        int currentIdx = i % n;
        int currentVal = nums[currentIdx];

        while (!st.empty() && nums[st.top()] < currentVal)
        {
            res[st.top()] = currentVal;
            st.pop();
        }

        // Only push indices during the first pass (0 to n-1)
        if (i < n)
        {
            st.push(i);
        }
    }
    return res;
}

int main()
{
    return 0;
}

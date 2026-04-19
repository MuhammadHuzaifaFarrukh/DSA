#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

// This is another variant of next greater element.
// We have to find the next greater element on right side for each element , even if we can find for last element
// We have to treat our given array as circular array.

// 1) Brute Force Method : O(n^2)

// 2) Another Method is to use Stack and apply same logic which we did for all next greater / smaller elements but we will check in (nums + nums) 1D array that is of 2 times its length
// Total elements 'n' so we check each element 2*n-1 times .
// This takes O(n) Time Complexity and Space also O(n).
// Others also used O(n) space as stack where we stored our indices.
// But here even more memory , like double sized array is being created.
// So Space Complexity : n+n = 2n = O(n)

// 3) This Method also uses Stack but this time we don't use another double sized array.
// We make the use of (%) Modulo Operator
// Total elements 'n' so we check each element 2*n-1 times .
// As the last element has to be checked again in a rotation one more time.
vector<int> nextGreaterElements(vector<int> &nums)
{
    int n = nums.size();
    vector<int> res(n, -1); // Initialize all to -1
    stack<int> st;

    for (int i = 0; i < 2 * n; i++)
    {
        while (!st.empty() && nums[st.top()] < nums[i % n])
        {
            res[st.top()] = nums[i % n];
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

// 4) Similarly we can apply that other method from size()-1 to 0 as well with same above approach with some things changed 

int main()
{
    vector<int> v = {6, 10, 7, 4, 8, 9, 4};
    v = nextGreaterElements(v);
    for (int n : v)
    {
        cout << n << " ";
    }
    return 0;
}

#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

// This problem asks to find the smaller number of each element nums[i] to its left side.
// For first element , its always gonna be -1 (as there is no left number present to the left most)

// 1) Brute Force : O(n^2)

// Both approaches which we used for next greater / smaller element to the right will work on it exactly but only in changed direction that's all.

// 2) We keep those elements' indexes in the stack whose next smaller we have to find (in ascending order).
// We store the indices of the elements of nums in stack which would correspond to numbers in ascending order.
// We then check the next elements if we find any smaller one , we go to the index stored in stack and check them if the current value is their next or not.
// Since we push each element only once , and then pop each element once , each element goes through only two operations (push and pop) once.
// Total operations = N (pushes) + (at most) N (pops) = 2N = O(N)

// This time we start from size() - 1 to 0 instead of 0 to size() - 1
vector<int> left_next_smaller(vector<int> &nums)
{
    stack<int> st;
    vector<int> ans(nums.size(), -1);
    for (int i = nums.size() - 1; i >= 0; i--)
    {
        while (!st.empty() && nums[st.top()] > nums[i])
        {
            ans[st.top()] = nums[i];
            st.pop();
        }
        st.push(i);
    }
    return ans;
}

// 3) The Other Method with changed Approach while using stack : O(n)
// This time we start from 0 to size() - 1.
// Both of these approaches are similar to the next greater / smaller elements at right or left.
vector<int> left_next_smaller2(vector<int> &nums)
{
    stack<int> st;
    vector<int> ans(nums.size(), -1);
    for (int i = 0; i < nums.size() ; i++)
    {
        while (!st.empty() && nums[st.top()] >= nums[i])
        {
            st.pop();
        }
        if(!st.empty())
        {
            ans[i] = nums[st.top()];
        }
        st.push(i);
    }
    return ans;
}

int main()
{
    vector<int> v = {4, 13, 11, 5, 9, 7, 8, 6};
    v = left_next_smaller2(v);
    for (int n : v)
    {
        cout << n << " ";
    }
    cout << endl;
    return 0;
}

// There are total 4 ways to solve the smaller / greater number on left / right sides.
// If we have to find smaller at left then for last to left side , iterate from size()-1 to 0.
// If we have to find smaller at left then for first to right side , iterate from 0 to size()-1 with some changed method that we saw above.
// If we have to find smaller at right then for first to right side , iterate from 0 to size()-1.
// If we have to find smaller at right then for last to left side , iterate from size()-1 to 0 with some changed method that we saw above.

// All use Monotonic Stack.

// All of these hold true for next greater element either at left or right side.
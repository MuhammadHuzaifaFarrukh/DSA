#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// This problem asks to find the next smaller of each nums[i] on right and if we can't find then store -1 there
// The Last ELement will always have -1 as there is no element to its right.

// 1) Use Brute Force : O(n^2)

// 2) Using Stack (Monotonic Stack): O(n)
// We keep those elements' indexes in the stack whose next smaller we have to find (in ascending order).
// We store the indices of the elements of nums in stack which would correspond to numbers in ascending order.
// We then check the next elements if we find any smaller one , we go to the index stored in stack and check them if the current value is their next or not.
// Since we push each element only once , and then pop each element once , each element goes through only two operations (push and pop) once.
// Total operations = N (pushes) + (at most) N (pops) = 2N = O(N)

vector<int> next_smaller(vector<int> &nums)
{
    stack<int> st;
    vector<int> ans(nums.size(), -1);
    for (int i = 0; i < nums.size(); i++)
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

// 2) Checking from backwards using Stack : O(n)
// Similarly the other method which we used with next greater element (starting from i = size() - 1) can also be used in the same way. 
vector<int> next_smaller2(vector<int> &nums)
{
    stack<int> st;
    vector<int> ans(nums.size(), -1);
    for (int i = nums.size()-1 ; i>=0 ; i--)
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
    vector<int> v = {7, 9, 12, 10, 14, 8, 3, 6, 9};
    v = next_smaller2(v);
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
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
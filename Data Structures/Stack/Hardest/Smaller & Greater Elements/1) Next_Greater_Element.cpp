#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Different Variants of this problem are.
// First one is the simple which asks to find the next greater of each nums[i] and if we can't find then store -1 there
// The Last ELement will always have -1 as there is no element to its right.

// 1) Use Brute Force : O(n^2)


// 2) Using Stack (Monotonic Stack): O(n)

// We store the indices of the elements of nums in stack which would correspond to numbers in descending order.
// We then check the next elements if we find any greater one , we go to the index stored in stack and check them if the current value is their next or not.
// Since we push each element only once , and then pop each element once , each element goes through only two operations (push and pop) once.
// Total operations = N (pushes) + (at most) N (pops) = 2N = O(N)

vector<int> next_greater(vector<int> &nums)
{
    stack<int> st;
    vector<int> ans(nums.size(), -1);
    for (int i = 0; i < nums.size(); i++)
    {
        while (!st.empty() && nums[st.top()] < nums[i])
        {
            ans[st.top()] = nums[i];
            st.pop();
        }
        st.push(i);
    }
    return ans;
}

int main()
{
    vector<int> v = {8, 6, 4, 7, 4, 9, 10, 8, 12};
    v = next_greater(v);
    for (int i = 0; i < v.size(); i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;
    return 0;
}

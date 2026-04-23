#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <climits>
using namespace std;

// We have to find the minimum of every window size of a given array and then find maximum from those minimum elements.

// 1) Brute Force : O(n^3)
// TLE occurs here.
vector<int> max_of_min_win(vector<int> &nums)
{
    vector<int> ans(nums.size(), 0);
    for (int i = 0; i < nums.size(); i++)
    {
        for (int j = 0; j < nums.size() - i; j++)
        {
            int num = INT_MAX;
            for (int k = j; k < j + i + 1; k++)
            {
                num = min(nums[k], num);
            }
            ans[i] = max(ans[i], num);
        }
    }
    return ans;
}

// 2) Using Stack : O(n)
// We find the Next Smallest Left and Right for each element.
// Then we : NSR - NSL - 1 to get the range (general)
// Then we only update the last value in that range.
// After all this , if there remains any zero value , then we again update that one also.

// If we tried to update all the values in the range then Time would become O(n^2) instead of O(n).
vector<int> max_of_min_win2(vector<int> &nums)
{
    vector<int> ans(nums.size(), 0);
    stack<int> st;
    int index;
    int range;
    for (int i = 0; i < nums.size(); i++)
    {
        while (!st.empty() && nums[st.top()] > nums[i])
        {
            index = st.top();
            st.pop();
            range = i;
            if (st.empty())
            {
                range = i;
            }
            else
            {
                range = i - st.top() - 1;
            }
            ans[range - 1] = max(ans[range - 1], nums[index]); // This gets us the window size : range - 1
        }
        st.push(i);
    }
    while (!st.empty())
    {
        index = st.top();
        st.pop();
        if (st.empty())
        {
            range = nums.size();
        }
        else
        {
            range = nums.size() - st.top() - 1;
        }
        ans[range - 1] = max(ans[range - 1], nums[index]);
    }

    for (int i = nums.size() - 2; i >= 0; i--)
    {
        ans[i] = max(ans[i], ans[i + 1]);
    }
    return ans;
}

int main()
{
    vector<int> arr = {70, 30, 20, 10, 10, 10, 10};
    arr = max_of_min_win2(arr);
    for (int num : arr)
    {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
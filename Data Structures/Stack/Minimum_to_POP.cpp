#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// 1) Can be solved by using Two Stacks by pushing all elements and checking min elements turn by turn : O(n^2)

// 2) Only 1 Stack and keep only minimum ones till some range : O(n)
vector<int> minimum_element_pop(vector<int> &nums)
{
    if (nums.size() == 1)
    {
        return nums;
    }
    stack<int> st;
    vector<int> ans;
    for (int i = 0; i < nums.size(); i++)
    {
        if (st.empty())
        {
            st.push(nums[i]);
        }
        else
        {
            st.push(min(st.top(), nums[i]));
        }
    }
    while (!st.empty())
    {
        ans.push_back(st.top());
        st.pop();
    }
    return ans;
}
int main()
{
    vector<int> v = {2, 1, 3, 5, 0, 6};
    v = minimum_element_pop(v);
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
    return 0;
}
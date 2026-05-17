#include <iostream>
#include <stack>
#include <vector>
using namespace std;

void reverse_array(vector<int> &nums)
{
    stack<int> st;
    for (int i = 0; i < nums.size(); i++)
    {
        st.push(nums[i]);
    }
    for (int i = 0; i < nums.size(); i++)
    {
        nums[i] = st.top();
        st.pop();
    }
}

int main()
{
    return 0;
}
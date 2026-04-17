#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Check Adjacent (from left for all elements except first)
// Both Non-Negative / Negative numbers can exist together
// However Negative and Non-Negative cannot and must be removed from array.

// 1) Make a Boolean Array for numbers and a last index pointer that mimics stack behaviour

// 2) Use Stack (Best , Cleaner Code) , a vector can also be used but its operations of insertion and removal are not in O(1)
// Time Complexity of both is O(n)
vector<int> make_array_Beautiful(vector<int> &nums)
{
    if (nums.size() == 1)
    {
        return nums;
    }
    stack<int> neighbour;
    for (int i = 0; i < nums.size(); i++)
    {
        if (neighbour.empty())
        {
            neighbour.push(nums[i]);
        }
        else if (nums[i] >= 0)
        {
            if (neighbour.top() >= 0)
            {
                neighbour.push(nums[i]);
            }
            else
            {
                neighbour.pop();
            }
        }
        else
        {
            if (neighbour.top() < 0)
            {
                neighbour.push(nums[i]);
            }
            else
            {
                neighbour.pop();
            }
        }
    }
    vector<int> ans(neighbour.size());
    for (int i = ans.size() - 1; i >= 0; i--)
    {
        ans[i] = neighbour.top();
        neighbour.pop();
    }
    return ans;
}
int main()
{
    vector<int> v = {2, 3, 5, -4, 6, -2, -8, 9};
    v = make_array_Beautiful(v);
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
    return 0;
}
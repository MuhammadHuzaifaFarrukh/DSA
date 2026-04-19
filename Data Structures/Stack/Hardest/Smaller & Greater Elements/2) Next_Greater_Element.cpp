#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

// This one is another variant of the stack question of next greater element.
// For each element in nums1, you must find its position in nums2 and then find the first element to its right in nums2 that is greater than it.
// The Last ELement will always have -1 as there is no element to its right.

// 1) Brute Force : O(n^2)

// 2) Using Stack : O(n1*n2)
// Here we find the next greater of nums2 by any of the method we used by stack (2 methods ; from start and from end) , then we take our answer array and compare its positions.
// So Space Complexity : n+n = 2n = O(n) , we take another vector just for nums2 greater vals.
// The Last Searching comparison is of n1*n2 so Time Complexity : O(n1*n2).
vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2)
{
    int n2 = nums2.size();
    vector<int> next_vals(n2, -1);
    stack<int> st;

    // Monotonic Stack to find next greater for all of nums2
    for (int i = 0; i < n2; i++)
    {
        while (!st.empty() && nums2[st.top()] <= nums2[i])
        {
            next_vals[st.top()] = nums2[i];
            st.pop();
        }
        st.push(i);
    }

    vector<int> result(nums1.size(), -1);
    for (int i = 0; i < nums1.size(); i++)
    {
        //  Manual search for the element in nums2
        for (int j = 0; j < n2; j++)
        {
            if (nums1[i] == nums2[j])
            {
                result[i] = next_vals[j];
                break;
            }
        }
    }
    return result;
}

// 3) Same as above , but finding the next greater of nums2 by using stack from other method as discussed in all other next greater / smaller elements
// The Last Searching comparison is of n1*n2 so Time Complexity : O(n1*n2).
int main()
{
    vector<int> v1 = {4, 1, 2}, v2 = {1, 6, 4, 2};
    vector<int> v3 = nextGreaterElement(v1, v2);
    for (int i : v3)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}

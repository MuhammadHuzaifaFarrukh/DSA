#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

// We have to find the index of the celebrity :
// Celebrity is the one who knows no one (0) but everyone knows it (1).

// 1) Brute Force Approach : Time Complexity : O(n^2).
// 2) It can also be solved by graph by making a vector of lists but O(n^2). (Similar to Brute Force Approach)

// 3) Stack : Time Complexity : O(n) and O(n) Space
// We use stacks to keep the two elements.
// If both know or none of them know each other then it makes no one a celebrity.
// If one knows (1) and other doesn't (0) , then the other who doesn't know can be a celebrity.

int celebrity(vector<vector<int>> &nums)
{
    stack<int> st;
    for (int i = nums.size() - 1; i >= 0; i--)
    {
        st.push(i);
    }
    while (st.size() > 1)
    {
        int first = st.top();
        st.pop();
        int second = st.top();
        st.pop();
        // First knows second but second does not know first .
        // In this case celebrity can be the second one.
        if (nums[first][second] == 1 && nums[second][first] == 0)
        {
            st.push(second);
        }
        // First does not know second but second knows first .
        // In this case celebrity can be the first one.
        else if (nums[first][second] == 0 && nums[second][first] == 1)
        {
            st.push(first);
        }
    }

    if (st.empty()) // If both know each other then both are not celebrities
    {
        return -1;
    }

    // It is possible that last element in our stack may still not be a celebrity , all other elements may be checked and leave us a last element
    // All elements while checking may know each other so we will keep popping so last element in stack remains unchecked.

    // You can check this in two ways.
    // 1) Check that for celebrity : its rows are zero and columns are all 1 except it.
    // 2) For Celebrity : its rows sum is 0 , and columns sum is (nums.size()-1). (Second one uses less checks).

    int x = st.top();
    st.pop();
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[x][i] != 0)
        {
            return -1;
        }
        if (nums[i][x] != 1 && i != x)
        {
            return -1;
        }
    }
    return x;
}

// 4) Two Pointers Approach : O(n) Time and O(1) Space
int celebrity(vector<vector<int>> &nums)
{
    int n = nums.size();
    int left = 0;
    int right = n - 1;

    // Step 1: Find the candidate
    while (left < right)
    {
        if (nums[left][right] == 1)
        {
            // left knows right, left is not a celebrity
            left++;
        }
        else
        {
            // left doesn't know right, right is not a celebrity
            right--;
        }
    }

    int candidate = left;

    // Step 2: Verification
    for (int i = 0; i < n; i++)
    {
        if (i != candidate)
        {
            // Celebrity knows NO ONE (row must be 0)
            // EVERYONE knows the celebrity (column must be 1)
            if (nums[candidate][i] == 1 || nums[i][candidate] == 0)
            {
                return -1;
            }
        }
    }

    return candidate;
}


int main()
{
    vector<vector<int>> v =
        {
            {0, 1, 0, 1, 1},
            {0, 0, 0, 1, 1},
            {0, 1, 0, 1, 0},
            {0, 0, 0, 0, 0},
            {1, 0, 1, 1, 0}};
    // Check index 3 , it is full of zeros , it knows no one but everyone else knows that index (1).
    cout << "Celebrity : " << celebrity(v) << endl;

    return 0;
}
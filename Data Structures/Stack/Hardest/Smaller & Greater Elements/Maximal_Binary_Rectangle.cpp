#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// We are given a binary rectangle and asked to find max area (same as the largest rectangle area in histogram).
// 1) With Brute Force : Time Complexity is O(m^3 * n^3).

// 2) So for this , we make a vector of each row of the 2d array , then pass it to the largest rectangle function and keep doing this for each row.
// Time Complexity : O(mn).


int largestRectangleArea(vector<int> &heights);
int maximalRectangle(vector<vector<char>> &matrix)
{
    int large = 0;
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<int> temp(cols, 0);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] == '1')
            {
                temp[j] += 1;
            }
            else
            {
                temp[j] = 0;
            }
        }
        large = max(large, largestRectangleArea(temp));
    }
    return large;
}

int main()
{
    vector<vector<char>> v =
        {
            {'1', '0', '1', '0', '0'},
            {'1', '0', '1', '1', '1'},
            {'1', '1', '1', '1', '1'},
            {'1', '0', '0', '1', '0'}};
    cout << "Maximum Area Rectangle in 2D Matrix : " << maximalRectangle(v) << endl;

    return 0;
}

// Helper Function
int largestRectangleArea(vector<int> &heights)
{
    stack<int> st;
    int index;
    int ans = 0;
    for (int i = 0; i < heights.size(); i++)
    {
        while (!st.empty() && heights[st.top()] > heights[i])
        {
            index = st.top();
            st.pop();
            if (!st.empty())
            {
                ans = max(ans, heights[index] * (i - st.top() - 1));
            }
            else
            {
                ans = max(ans, heights[index] * i);
            }
        }
        st.push(i);
    }
    while (!st.empty())
    {
        index = st.top();
        st.pop();
        if (!st.empty())
        {
            ans = max(ans, (int)(heights[index] * (heights.size() - st.top() - 1)));
        }
        else
        {
            ans = max(ans, (int)(heights[index] * heights.size()));
        }
    }
    return ans;
}
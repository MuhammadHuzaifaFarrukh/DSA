#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
// We have to find the largest rectangle area overall in the histogram.
// The method we will use (next smaller left and right) will work here.
// It won't work if we are asked to find the maximum for each rectangle.

// 1) With Brute Force , where we compare first rectangle with all other for area then next one for all area and so on till n rectangles (n by m) then the time complexity becomes : O(nm)

// 2) Using Monotonic Stack (Next Smaller Left and Right)
// We find Next Smaller Right for the given array
// We find Next Smaller Left for the given array
// Then we find the maximum area for each height using formula : heights[i] * (right[i] - left[i] - 1)
// This (right[i] - left[i] -1) is the width of the rectangle , which we find using the Next Smaller Left and Right.
// This tells that for each maximum height , how far can its width go in right or left direction.
// Time Complexity : O(n)
// Space Complexity : n+n+n = 3n = O(n)
int largestRectangleArea(vector<int> &heights)
{
    vector<int> right(heights.size(), heights.size());
    vector<int> left(heights.size(), -1);
    stack<int> st;
    // Find Next Greater Right
    for (int i = 0; i < heights.size(); i++)
    {
        while (!st.empty() && heights[st.top()] > heights[i])
        {
            right[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    // We need stack for finding next smaller left also so we can either clear it simply , or we can store the heights.size() in it and above we won't initialize it with heights.size()
    while (!st.empty())
    {
        // right[st.top()] = heights.size();
        st.pop();
    }

    // Find Next Greater Left
    for (int i = heights.size() - 1; i >= 0; i--)
    {
        while (!st.empty() && heights[st.top()] > heights[i])
        {
            left[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }

    // We can either clear it simply , or we can store the -1 in it and above we won't initialize it with -1.
    while (!st.empty())
    {
        // left[st.top()] = -1;
        st.pop();
    }

    int ans = 0;
    for (int i = 0; i < heights.size(); i++)
    {
        ans = max(ans, heights[i] * (right[i] - left[i] - 1));
    }
    return ans;
}

// 3) Another method for this is the same as above but now we do it in 1 pass instead of 3 passes above.
// We keep finding the next smaller right (which is 'i')
// When we find the next smaller right , we pop once more and get the next smaller left (st.top()) as elements are stored in stack in ascending order so the next smaller left of that element will be just left to it.
// Then we need to see if stack is empty or not.
// If not empty then our formula for area is : heights[index] * (i-st.top()-1) , same as above.
// If stack is empty then it means we couldn't find the Next smaller left so we have area : heights[index] * (i).

// Once the for() loop finishes , we need to check if stack is empty or not
// If it is empty it means that we couldn't find the next smaller right so : heights[index] * (n-st.top()-1)
// If it is not empty it means that we couldn't find the next smaller right and left either so : heights[index] * n

// Time Complexity : O(n)
// Space Complexity : n = O(n)
int largestRectangleArea2(vector<int> &heights)
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

int main()
{
    vector<int> h = {2, 1, 5, 6, 2, 3};
    cout << "Largest Rectangle Area :  " << largestRectangleArea(h) << endl;

    return 0;
}
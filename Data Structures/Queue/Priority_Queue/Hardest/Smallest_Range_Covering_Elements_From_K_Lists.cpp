#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

/*
You have k lists of sorted integers in non-decreasing order. Find the smallest range that includes at least one number from each of the k lists.
We define the range [a, b] is smaller than range [c, d] if b - a < d - c or a < c if b - a == d - c.

Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
Output: [20,24]
Explanation:
List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
List 2: [0, 9, 12, 20], 20 is in range [20,24].
List 3: [5, 18, 22, 30], 22 is in range [20,24].

Input: nums = [[1,2,3],[1,2,3],[1,2,3]]
Output: [1,1]

Input: nums = [[1]]
Output: [1,1]
*/

// 1) Brute Force
// We keep all elements from list to a new vector temp.
// Then we take all possible ranges from the list using this new vector and match if each possible range is valid range or not.
// We found its validity by comparing that range across all the lists.
// If its valid , we check to see if our answer can be updated or not (if we found a new smaller range).
// If its not valid , we do nothing and get the new possible range.
// Time Complexity :
// Let k be number of rows and m be number of elements in each list.
// Let this (mk) = n as the size of temp new vector.
// We get all possible ranges by iterating twice nestedly on temp vectir : (mk)^2.
// Then we see through all elements for checking if this range contains the list elements , which we go through all (mk) elements for each (mk)^2 iterations.
// Total time : O((mk)^3) or O(n^3)

// Space Complexity :
// A new vector contains all (mk) elements.
// Space : O(mk) or O(n)
vector<int> smallestRange(vector<vector<int>> &nums)
{
    vector<int> temp;
    for (int i = 0; i < nums.size(); i++)
    {
        for (int j = 0; j < nums[i].size(); j++)
        {
            temp.push_back(nums[i][j]);
        }
    }
    vector<int> ans(2);
    ans[0] = INT_MIN;
    ans[1] = INT_MAX;

    for (int i = 0; i < temp.size(); i++)
    {
        for (int j = i; j < temp.size(); j++)
        {
            int maximum = max(temp[i], temp[j]);
            int minimum = min(temp[i], temp[j]);
            int founds = 0;
            for (int k = 0; k < nums.size(); k++)
            {
                for (int l = 0; l < nums[k].size(); l++)
                {
                    if (nums[k][l] >= minimum && nums[k][l] <= maximum)
                    {
                        founds++;
                        break;
                    }
                }
                if (founds == nums.size())
                {
                    // We found a valid range.
                    if (maximum - minimum < (long long)ans[1] - (long long)ans[0])
                    {
                        ans[0] = minimum;
                        ans[1] = maximum;
                    }
                    break;
                }
            }
        }
    }
    return ans;
}

// Binary Search and Quickselect fail here totally.

// 2) Min-Heap.
// We make pairs of all the numbers from the given 2d array into pair vector and make min heap from it for those 'k' elements of first column.
// We keep (value ,row , column).
// Then we have to get our first range from the first column of k rows.
// That would be the maximum and minimum from those k rows.
// We can find maximum as it is , but minimum faster as we had put all the 'k' elements of first column in min heap.
// Once  we have our first range , we can check for the next range.
// We know that we can decrease the range by either maximizing the first element or minimizing the second element [first, second].
// Since the lists are given in sorted ascending order , it is not possible to decrease the second element.
// So we try to increase the  first element.
// We pop out the smallest element , check if its next exist , that might become the next min/max.
// Also we update our maximum since this new element could be our maximum so we check if the popped out element's next element is the new maximum.
// Then we change our minimum also.
// Now once we have got another range , we check if this new range is smaller than the previous one.
// If yes then we update our answer , if no or same amount of elements as in previous range , then we don't update.
// Once we see that any of the 'k' lists next does not exist , we simply stop there , because the range won't cover as this list is finished now , so we also keep just 'k' elements in our min heap and let the loop run till our heap is of 'k' size.
// Time Complexity :
// Time to build Heap from 'k' elements : O(k)
// All elements popped/pushed : (mk-k)logk.
// Total Time : O(k + (mk-k)logk) = O(mklogk) or O(nlogk) where n=mk.
// Space Complexity :
// We store only O(k) elements in our min heap at a time.
// Extra Space : O(k)
// Total Space : O(k)
vector<int> smallestRange2(vector<vector<int>> &nums)
{
    vector<pair<int, pair<int, int>>> v;
    for (int i = 0; i < nums.size(); i++)
    {
        v.push_back({nums[i][0], {i, 0}});
    }
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq(v.begin(), v.end());
    vector<int> ans(2);

    int maximum = INT_MIN, minimum;
    for (int i = 0; i < nums.size(); i++)
    {
        maximum = max(maximum, nums[i][0]);
    }
    minimum = pq.top().first;
    ans[0] = minimum;
    ans[1] = maximum;
    while (pq.size() == nums.size())
    {
        int i = pq.top().second.first;
        int j = pq.top().second.second;
        int val = pq.top().first;
        pq.pop();

        if (j + 1 < nums[i].size())
        {
            pq.push({nums[i][j + 1], {i, j + 1}});
            if (nums[i][j + 1] > maximum)
            {
                maximum = nums[i][j + 1];
            }
            minimum = pq.top().first;
        }

        if (maximum - minimum < ans[1] - ans[0])
        {
            ans[0] = minimum;
            ans[1] = maximum;
        }
    }
    return ans;
}
int main()
{
    vector<vector<int>> v = {{4, 10, 15, 24, 26}, {0, 9, 12, 20}, {5, 18, 22, 30}};
    vector<int> ans = smallestRange2(v);
    cout << " Range : [" << ans[0] << "," << ans[1] << "]" << endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <deque>
#include <climits>
#include <queue>
using namespace std;

// 1) Brute Force Sliding : (Use simple sliding window) : k*(n-k) = O(nk)
vector<int> maxSlidingWindow1(vector<int> &nums, int k)
{
    if (k == 0)
    {
        return vector<int>{};
    }
    if (k == 1)
    {
        return nums; // Can use move(nums) , but if compiler supports NRVO then don't write move(nums) .
        // However if there are global variable returning or if-else with different objects/var returning then compiler will choose to refuse NRVO and go to copying.
    }
    vector<int> v;
    for (int i = 0; i <= nums.size() - k; i++) // Runs n-k times
    {
        int big = INT_MAX;
        for (int j = i; j < i + k; j++) // Runs k times , total = k(n-k)
        {
            big = max(big, nums[j]);
        }
        v.push_back(big);
    }
    return v;
}

// 2) Use a Priority Queue and store numbers and then select maximum in each window. (Looks Simple)
// O(N K Logk) which is even more than above solution
/*
vector<int> maxSlidingWindow2(vector<int> &nums, int k)
{
    vector<int> result;
    int n = nums.size();

    // Loop through every possible window start
    for (int i = 0; i <= n - k; i++)
    {
        priority_queue<int> pq; // Fresh PQ for every window

        // Fill the PQ with the k elements of the current window
        for (int j = i; j < i + k; j++)
        {
            pq.push(nums[j]);
        }

        // The max of THIS specific window
        result.push_back(pq.top());
    }
    return result;
}
*/

// 3) Use a Priority Queue and pair to store numbers and their positions as we are gonna keep only one pq so all numbers have to be stored inside it.
// It would still take O(nlogn)
/*
vector<int> maxSlidingWindow3(vector<int>& nums, int k)
{
    // Max-heap storing {value, index}
    priority_queue<pair<int, int>> pq;
    vector<int> result;

    for (int i = 0; i < nums.size(); i++)
    {
        // 1. Add current element to the heap
        pq.push({nums[i], i});

        // 2. Start processing once the first window is complete
        if (i >= k - 1)
        {
            // 3. "Lazy Removal": Remove the top if it's outside the window [i-k+1, i]
            while (pq.top().second <= i - k )
            {
                pq.pop();
            }

            // 4. The top is now guaranteed to be the max of the current window
            result.push_back(pq.top().first);
        }
    }

    return result;
}
*/

// 4) 
// Using Deque : Normal Queue isn't required because we need to push_back also in this case. O(n).
// Time Complexity : O(n) as we are only going forward towards elements once and not going back.

// We store the k-1 indices in the deque.
// Then for each index we check that the nums[i] > nums[the last one].
// If true then we keep popping it untill false and then push back 'i' , and we do this even in our k-1 to n condition.
// Then in k-1 to n , we check additional that if that which elements should be in the current window so we pop them out as well.


// Basic idea is to have max elements at the front of the deque.
vector<int> maxSlidingWindow4(vector<int> &nums, int k)
{
    if (k == 0)
    {
        return vector<int>{};
    }
    if (k == 1)
    {
        return nums; // Can use move(nums) , but if compiler supports NRVO then don't write move(nums) .
        // However if there are global variable returning or if-else with different objects/var returning then compiler will choose to refuse NRVO and go to copying.
    }
    deque<int> dq;
    vector<int> ans;

    for (int i = 0; i < k - 1; i++)
    {
        if (dq.empty())
        {
            dq.push_back(i);
        }
        else
        {
            while (!dq.empty() && nums[i] > nums[dq.back()])
            {
                dq.pop_back();
            }
            dq.push_back(i);
        }
    }

    for (int i = k - 1; i < nums.size(); i++)
    {
        while (!dq.empty() && nums[i] > nums[dq.back()])
        {
            dq.pop_back();
        }
        dq.push_back(i);
        if (dq.front() <= i - k)
        {
            dq.pop_front();
        }
        ans.push_back(nums[dq.front()]);
    }
    return ans;
}


// Same as above but the conditions are written combined. (Above is easier to understand).
// Time Complexity : O(n) as we are only going forward towards elements once and not going back.
vector<int> maxSlidingWindow5(vector<int> &nums, int k)
{
    if (k == 0)
    {
        return vector<int>{};
    }
    if (k == 1)
    {
        return nums; // Can use move(nums) , but if compiler supports NRVO then don't write move(nums) .
        // However if there are global variable returning or if-else with different objects/var returning then compiler will choose to refuse NRVO and go to copying.
    }
    deque<int> dq;
    vector<int> ans;
    // cout << "Maximum in each window: ";
    for (int i = 0; i < nums.size(); i++)
    {
        while (!dq.empty() && dq.front() <= i - k)
        {
            dq.pop_front();
        }
        while (!dq.empty() && nums[dq.back()] < nums[i])
        {
            dq.pop_back();
        }
        dq.push_back(i);
        if (i >= k - 1)     // For the first one , 0 to k-1 answer
        {
            ans.push_back(nums[dq.front()]);
        }
    }

    return ans;
}

int main()
{
    vector<int> a = {4, 3, 7, 5, 2, 3, 1, 2, 8, 7};
    int k = 4;

    vector<int> x = maxSlidingWindow4(a, k);
    for (int i = 0; i < x.size(); i++)
    {
        cout << x[i] << " ";
    }
    cout << "\n";
    return 0;
}
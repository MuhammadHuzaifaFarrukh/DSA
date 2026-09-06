#include <iostream>
#include <queue>

using namespace std;

/*
Given an array arr[] of positive integers and two integers k1 and k2, find the sum of all array elements whose values lie between the k1-th smallest and the k2-th smallest (both k1th and k2th smallest are not included) of the array.

Input: arr[] = [20, 8, 22, 4, 12, 10, 14], k1 = 3, k2 = 6
Output: 26
Explanation: 3rd smallest is 10 and 6th smallest is 20. Sum of all between k1-th and k2-th is 12 + 14 = 26.

Input: arr[] = [1, 2, 3, 4, 5], k1 = 1, k2 = 5
Output: 9
Explanation: 1st smallest is 1 and 5th smallest is 5. Sum of all between k1-th and k2-th is 2 + 3 + 4 = 9.

Input: arr[] = [5, 6, 7], k1 = 2, k2 = 3
Output: 0
Explanation: The 2nd smallest is 6 and the 3rd smallest is 7. Since there are no strictly between 6 and 7, the required sum is 0.
*/

// We use Max Heap for the smallest kth numbers.
// We build a Max heap pq1 for k1 and pq2 for k2 as k2-1.
// Then we find the k1 and k2 smallest number.
// We find sum of numbers smaller than 2nd smallest number.
// We find sum of numbers smaller than 1st smallest number.
// Then we subtract them both to get our answer.
// Time Complexity :
// Heap building time : k1+(k2-1).
// Then we run through (n-k1) and (n-k2+1) to elements to pop or push that gives us : (n-k1)logk1 + (n-k2+1)logk2 time.
// Summing and Popping out those k1 and (k2-1) elements : k1logk1 + (k2-1)log(k2-1).
// If we find overall time it becomes :
// O(k1 + k2 + (n-k1)logk1 + (n-k2)logk2 + k1logk1 + k2logk2)
// Simplifying (for worst case) :
// O(nlogk1 + nlogk2) = O(nlogk2) since k2>k1.

// Space Complexity :
// O(k1+k2) = O(k2) since k2 > k1.
int sumBetweenK1K2(vector<int> &nums, int k1, int k2)
{
    priority_queue<int> pq1(nums.begin(), nums.begin() + k1);
    priority_queue<int> pq2(nums.begin(), nums.begin() + k2 - 1);

    for (int i = k1; i < nums.size(); i++)
    {
        if (nums[i] < pq1.top())
        {
            pq1.pop();
            pq1.push(nums[i]);
        }
    }

    for (int i = k2 - 1; i < nums.size(); i++)
    {
        if (nums[i] < pq2.top())
        {
            pq2.pop();
            pq2.push(nums[i]);
        }
    }

    int sum1 = 0, sum2 = 0;
    while (!pq1.empty())
    {
        sum1 += pq1.top();
        pq1.pop();
    }

    while (!pq2.empty())
    {
        sum2 += pq2.top();
        pq2.pop();
    }
    return (sum2 - sum1);
}

int main()
{
    vector<int> v = {20, 8, 22, 4, 12, 10, 14};
    int k1 = 3, k2 = 6;
    cout << "Sum between K1 and K2 Smallest Elements : " << sumBetweenK1K2(v, k1, k2) << endl;
    return 0;
}
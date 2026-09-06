#include <iostream>
#include <queue>
#include <deque>
#include <limits.h>

using namespace std;

/*
You are given a sorted integer array arr containing 1 and prime numbers, where all the integers of arr are unique. You are also given an integer k.
For every i and j where 0 <= i < j < arr.length, we consider the fraction arr[i] / arr[j].
Return the kth smallest fraction considered. Return your answer as an array of integers of size 2, where answer[0] == arr[i] and answer[1] == arr[j].

Input: arr = [1,2,3,5], k = 3
Output: [2,5]
Explanation: The fractions to be considered in sorted order are:
1/5, 1/3, 2/5, 1/2, 3/5, and 2/3.
The third fraction is 2/5.

Input: arr = [1,7], k = 1
Output: [1,7]
*/

// 1) Brute Force :
// Generate all Sets of fractions -> N^2
// Sort them -> N^2LogN
// Then find the Kth fraction easily.
// Total Time : O(n^2logn) and Space : O(n^2)

// 2) Min Heap.
// We generate all the pairs keeping first value as fractional , then next as indexes of numerator and denominator.
// Then we put them all inside min-heap.
// Then we pop k-1 elements and get the kth smallest fraction easily.
// Time Complexity :
// Generating all pairs -> n^2
// Making min heap of all the pairs -> n^2logn.
// Popping out k pairs : klogn.
// Total Time : O(n^2logn + klogn) = O(n^2logn)
// Extra SPace : O(n^2)
// Total Space : O(n^2)
vector<int> kthSmallestPrimeFraction(vector<int> &nums, int k)
{
    vector<pair<double, pair<int, int>>> v;
    for (int i = 0; i < nums.size(); i++)
    {
        for (int j = i + 1; j < nums.size(); j++)
        {
            v.push_back({nums[i] / (double)nums[j], {i, j}});
        }
    }
    priority_queue<pair<double, pair<int, int>>, vector<pair<double, pair<int, int>>>, greater<pair<double, pair<int, int>>>> pq(v.begin(), v.end());

    while (k > 1)
    {
        pq.pop();
        k--;
    }
    return {nums[pq.top().second.first], nums[pq.top().second.second]};
}

// 2) Min-Heap Optimized
// We know that possible numerators are all indexes from 0 to n-2 so.
// We store the first smallest fractions pairs from 0 to n-2 numerators and denominators as n-1.
// So we have stored almost n elements in our min heap.
// Now we keep running our min-heap for the rest of the elements (k-1) times.
// We pop out the smallest fraction and see if we can still continue to generate another fraction that may be a little larger but still smaller using this one by increasing its denominator while keeping its numerator same.
// So we just check if j-1>i  so that we can have a valid fraction , if yes then we push it in our heap else we don't.
// We keep doing it for k-1 times.
// Also we can run our first loop for selection min(n-1,k) because k can be larger as we have to deal with pairs and similarly n can be larger as well.
// So if we just keep (n-1) pairs where n-1 < k , or if we keep k pairs where k < n-1 ,it still works.
// In first case , once we've generated n-1 fracs , we can reach to k easily as generated n-1 fracs means here generated almost all pairs.
// Similarly if k<n-1 then we just need those k fracs , not more beyond , although there's no issue still it will take much time.

// Time Complexity :
// Time to push min(k,n) pairs : min(k,n)log(min(n,k)).
// Time to pop/push k times : klog(min(n,k))
// Total Time : O(min(k,n)log(min(n,k)) + klog(min(n,k))) = O(min(k,n)log(min(n,k)))

// Space Complexity :
// We keep only min(n,k) elements in our heap.
// Total Space : O(min(n,k)).
vector<int> kthSmallestPrimeFraction2(vector<int> &nums, int k)
{
    priority_queue<pair<double, pair<int, int>>, vector<pair<double, pair<int, int>>>, greater<pair<double, pair<int, int>>>> pq;
    for (int i = 0; i < nums.size() - 1; i++) // Can be optimized by running loop i < (min (n-1 , k))
    {
        pq.push({nums[i] / double(nums[nums.size() - 1]), {i, nums.size() - 1}});
    }

    while (k > 1)
    {
        int i = pq.top().second.first;
        int j = pq.top().second.second;
        pq.pop();

        if (j - 1 > i)
        {
            pq.push({(double)nums[i] / nums[j - 1], {i, j - 1}});
        }

        k--;
    }
    return {pq.top().second.first, pq.top().second.second};
}

// 3) Binary Search on Answer Range :
// Our answer lies in 0 < Ans < 1.0
// So we start at 0 and end at 1.0
// This time , our mid can be a decimal value as well.

// THen we see how many fractions are less than equal to our mid.
// We don't check using Division since division can vary in points , we use Multiplication instead.
// We see if count >= k , this could be our ans , and so we try to compress our range.
// We don't write end = mid-1 because just even a small -1 can skip many fractions and similary we don't do start = mid+1 because of the same reason.
// That's why we just write end=mid or start = mid.
// Now when we do this , when start and end are very close to each other , mid gets infinitely closer to both , but due to how computers store decimals (IEEE 754 floating-point precision limits) , start may never equal end.
// So if we write start <= end , loop would never terminate.
// Because floating-point arithmetic updates start = mid or end = mid directly without adding or subtracting 1, the distance between start and end shrinks infinitely, but start never becomes strictly greater than end.
// SO that's why we wrote : (end-start) < 10^-9.
// This means to keep dividing the search space until the search window is smaller than 0.000000001; once start and end are that close, stop the loop.

// Time Complexity : O(nlog(1/e))
// This outer loop range is almost 30 iterations , so we could also just run this loop as for(int iter ; iter<=50 ; iter++) and then we would simply run our two pointer irrespective or start and end , although their values will still be used , they just won't be the condition for the outer loop now.
// Space Complexity : O(1)
vector<int> kthSmallestPrimeFraction3(vector<int> &arr, int k)
{
    int n = arr.size();

    double start = 0.0;
    double end = 1.0;

    int ans_num = 0;
    int ans_den = 1;

    while (end <= start)
    {
        double mid = start + (end - start) / 2.0;

        int count = 0;
        int j = 1;
        int max_num = 0, max_den = 1; // Tracks largest fraction <= mid

        // Count fractions <= mid
        for (int i = 0; i < n; i++)
        {
            while (j < n && arr[i] > mid * arr[j])
            {
                j++;
            }
            count += (n - j);
            if (j < n && arr[i] * max_den > max_num * arr[j])
            {
                max_num = arr[i];
                max_den = arr[j];
            }
        }

        if (count >= k)
        {
            ans_num = max_num;
            ans_den = max_den;
            end = mid;
        }
        else
        {
            start = mid;
        }
    }

    return {ans_num, ans_den};
}

int main()
{
    int k = 4;
    vector<int> v = {1, 3, 5, 7};
    vector<int> ans = kthSmallestPrimeFraction2(v, k);
    cout << "Kth smallest Fraction : " << ans[0] / (double)ans[1] << endl;
    return 0;
}
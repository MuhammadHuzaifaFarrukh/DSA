#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
using namespace std;

/*
An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.
Given an integer n, return the nth ugly number.

Input: n = 10
Output: 12
Explanation: [1, 2, 3, 4, 5, 6, 8, 9, 10, 12] is the sequence of the first 10 ugly numbers.

Input: n = 1
Output: 1
Explanation: 1 has no prime factors, therefore all of its prime factors are limited to 2, 3, and 5.
*/

// 1) Brute Force :
// We check for every integer starting from 1.
// If it is an ugly number , we increase the count.
// Once count reaches 'n' , we return our answer.
// Time Complexity :
// Outer Loop runs Un where Un is the value of the nth Ugly Number (for n = 1690 ~ 2.2*10^9).
// Inner check runs in logUn time.
// Total Time : O(Un*logUn) (Very Large)
// Space Complexity :
// O(1)
bool isUgly(int n);
int nthUglyNumber(int n)
{
    int ans = 1;
    int count = 0;
    while (count < n)
    {
        if (isUgly(ans))
        {
            count++;
        }

        if (count == n)
        {
            return ans; // Found the n-th ugly number
        }

        ans++; // Test the next integer
    }
    return ans;
}

bool isUgly(int n)
{
    // 1. Handle non-positive numbers (Ugly numbers are positive)
    if (n <= 0)
    {
        return false;
    }
    // 2. Repeatedly divide by the allowed prime factors
    // Using while loops is safer and faster than a for loop up to n/2
    while (n % 2 == 0)
    {
        n /= 2;
    }
    while (n % 3 == 0)
    {
        n /= 3;
    }
    while (n % 5 == 0)
    {
        n /= 5;
    }

    // 3. If n becomes 1, it only had 2, 3, or 5 as factors
    return n == 1;
}

// 2) Min Heap + Hash Table
// We know that first ugly number starts from 1 so we insert 1 in heap and set.
// Then we run a loop n times , and we only generate the next ugly numbers.
// We pop the minimum value out and push its 2,3,5 multiples by multiplying this popped out value with 2,3,5 and pushing them in heap again.
// Before pushing we also check if they have occurred before or not , so that's why we use a hash set for this.
// Time :
// We start by pushing 1 element.
// Then we keep pushing 3 element each time , so our heap grows ~ 3n (or a little precisely 2n+1).
// So we iterate 'n' times and keep pushing and popping through 'n' elements  = nlogn.
// Total Time : O(nlogn)
// Space :
// Heap also stores at most 3n elements at each step :
// Remove 1 element, add 3 elements -> Net change: +2 elements.
// In the absolute worst case where zero duplications occur (though might not be possible),
// We get 1 + n(3-1) = 2n+1.
// So Total Space either by Set / Heap = 2n+1 = O(n)
// Total Space : O(n)
int nthUglyNumber(int n)
{
    unordered_set<long long> s;
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    pq.push(1);
    s.insert(1);

    long long ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans = pq.top();
        pq.pop();
        long long val = ans * 2;
        if (!s.count(val))
        {
            s.insert(val);
            pq.push(val);
        }

        val = ans * 3;
        if (!s.count(val))
        {
            s.insert(val);
            pq.push(val);
        }

        val = ans * 5;
        if (!s.count(val))
        {
            s.insert(val);
            pq.push(val);
        }
    }
    return (int)ans;
}
int main()
{
    return 0;
}
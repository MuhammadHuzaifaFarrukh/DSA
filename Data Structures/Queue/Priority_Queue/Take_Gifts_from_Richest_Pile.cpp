#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

/*
You are given an integer array gifts denoting the number of gifts in various piles. Every second, you do the following:

Choose the pile with the maximum number of gifts.
If there is more than one pile with the maximum number of gifts, choose any.
Reduce the number of gifts in the pile to the floor of the square root of the original number of gifts in the pile.
Return the number of gifts remaining after k second.

Input: gifts = [25,64,9,4,100], k = 4
Output: 29
Explanation:
The gifts are taken in the following way:
- In the first second, the last pile is chosen and 10 gifts are left behind.
- Then the second pile is chosen and 8 gifts are left behind.
- After that the first pile is chosen and 5 gifts are left behind.
- Finally, the last pile is chosen again and 3 gifts are left behind.
The final remaining gifts are [5,8,9,4,3], so the total number of gifts remaining is 29.

Input: gifts = [1,1,1,1], k = 4
Output: 4
Explanation:
In this case, regardless which pile you choose, you have to leave behind 1 gift in each pile.
That is, you can't take any pile with you.
So, the total gifts remaining are 4.
*/

// 1) Brute Forcing / Sorting will lead to time : O(n^2)

// 2) We use max-heap + greedy here.
// We choose the max gift and take its floor(sqrt(x)).
// We just run it for 'k' times.
// We are just pushing and popping in each iteration so pq never ends.
// Time : O(n+klogn) , where k can be more than 'n'.
// Space : O(n)
long long pickGifts(vector<int> &gifts, int k)
{
    // 1. Build a Max-Heap from the gifts array - O(n)
    priority_queue<int> pq(gifts.begin(), gifts.end());

    // 2. Perform k operations - O(k log n)
    while (k > 0 && !pq.empty())
    {
        int richest = pq.top();
        pq.pop();

        // Calculate the remaining gifts (floor of sqrt)
        int remaining = floor(sqrt(richest));
        // sqrt(richest) can be done as well as we are using integer variables.

        // Push the remaining back into the heap
        pq.push(remaining);
        k--;
    }

    // 3. Sum up all the remaining gifts
    long long totalRemaining = 0;
    while (!pq.empty())
    {
        totalRemaining += pq.top();
        pq.pop();
    }

    return totalRemaining;
}

int main()
{
    vector<int> v = {25, 64, 9, 4, 100};
    int k = 4;
    cout << "Number of Gifts Remaining :" << pickGifts(v, k) << endl;
    return 0;
}
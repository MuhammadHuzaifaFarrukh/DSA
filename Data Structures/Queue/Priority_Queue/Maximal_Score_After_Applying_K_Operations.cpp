#include <iostream>
#include <queue>
using namespace std;
/*
You are given a 0-indexed integer array nums and an integer k. You have a starting score of 0.

In one operation:

choose an index i such that 0 <= i < nums.length,
increase your score by nums[i], and
replace nums[i] with ceil(nums[i] / 3).
Return the maximum possible score you can attain after applying exactly k operations.
The ceiling function ceil(val) is the least integer greater than or equal to val.

Input: nums = [10,10,10,10,10], k = 5
Output: 50
Explanation: Apply the operation to each array element exactly once. The final score is 10 + 10 + 10 + 10 + 10 = 50.

Input: nums = [1,10,3,3,3], k = 3
Output: 17
Explanation: You can do the following operations:
Operation 1: Select i = 1, so nums becomes [1,4,3,3,3]. Your score increases by 10.
Operation 2: Select i = 1, so nums becomes [1,2,3,3,3]. Your score increases by 4.
Operation 3: Select i = 2, so nums becomes [1,2,1,3,3]. Your score increases by 3.
The final score is 10 + 4 + 3 = 17.
*/

// 1) Brute Forcing / Sorting will lead to time : O(n^2)

// 2) We use max-heap + greedy here.
// We perform the operations 'k' times.
// We add the maximum value from our pq.
// Then we push its ceil(nums[i]/3) , to make ceil() work perfectly we cast it to double temporarily.
// We can also use a formula instead of this ceil as ceil(a/b) is also equal to (a+b-1)/b.
// So if we see nums[i]/3 , it becomes : (nums[i]+3-1)/3 = (nums[i]+2)/3.
// We are just pushing and popping in each iteration so pq never ends.
// Time : O(n+klogn)  , where k can be more than 'n'.
// Space : O(n)
long long maxKelements(vector<int> &nums, int k)
{
    // 1. Build a Max-Heap from the array
    priority_queue<int> pq(nums.begin(), nums.end());
    long long score = 0;

    // 2. Perform k operations
    while (k--)
    {
        // Get the current maximum
        int maxVal = pq.top();
        pq.pop();

        // Add to total score
        score += maxVal;

        // Replace with ceil(maxVal / 3) and push back
        // Using ceil(maxVal/3) may do Overflow or some errors so we use simplified formula
        // Formula for ceil(a/b) is (a + b - 1) / b
        pq.push((maxVal + 2) / 3);

        // We can also use just this line instead of this formula :
        // pq.push(ceil((double)maxVal/3));
    }
    return score;
}

int main()
{
    vector<int> v = {1, 10, 3, 3, 3};
    int k = 2;
    cout << "Maximal Score : " << maxKelements(v, k) << endl;
    return 0;
}
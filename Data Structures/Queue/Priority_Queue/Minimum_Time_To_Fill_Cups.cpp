#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

/*
You have a water dispenser that can dispense cold, warm, and hot water. Every second, you can either fill up 2 cups with different types of water, or 1 cup of any type of water.
You are given a 0-indexed integer array amount of length 3 where amount[0], amount[1], and amount[2] denote the number of cold, warm, and hot water cups you need to fill respectively.
Return the minimum number of seconds needed to fill up all the cups.

Input: amount = [1,4,2]
Output: 4
Explanation: One way to fill up the cups is:
Second 1: Fill up a cold cup and a warm cup.
Second 2: Fill up a warm cup and a hot cup.
Second 3: Fill up a warm cup and a hot cup.
Second 4: Fill up a warm cup.
It can be proven that 4 is the minimum number of seconds needed.

Input: amount = [5,4,4]
Output: 7
Explanation: One way to fill up the cups is:
Second 1: Fill up a cold cup, and a hot cup.
Second 2: Fill up a cold cup, and a warm cup.
Second 3: Fill up a cold cup, and a warm cup.
Second 4: Fill up a warm cup, and a hot cup.
Second 5: Fill up a cold cup, and a hot cup.
Second 6: Fill up a cold cup, and a warm cup.
Second 7: Fill up a hot cup.

Input: amount = [5,0,0]
Output: 5
Explanation: Every second, we fill up a cold cup.
*/

// 1) Solving using Max Heap :
// We know that when we have [1,4,2] -> [1,3,1] -> [0,2,1] -> [0,1,0] -> [0,0,0].
// So we always kept taking the max 2 elements at a time in our array.
// We kept doing this until we found the max element as 0.
// So we take the first element and pop it , then for the 2nd element we take it and pop it out , then we subtract 1 from both and push them again.
// Also , if we get an input like [5,0,0] , then this input doesn't have any 2nd max > 0 , so that's why we need to put a check right after we pop the first max > 0.
// Time Complexity : O(S) = O(1) where S = amount[0] + amount[1] + amount[2].
// Space Complexity : O(1) as Heap holds at most 3 elements only.
int fillCups(vector<int> &amount)
{
    priority_queue<int> pq(amount.begin(), amount.end());
    int seconds = 0;
    while (pq.top() != 0)
    {
        int x1 = pq.top();
        pq.pop();

        if (pq.top() != 0)
        {
            int x2 = pq.top();
            pq.pop();
            x2--;
            pq.push(x2);
        }

        x1--;
        pq.push(x1);
        seconds++;
    }
    return seconds;
}

// 2) Can be solved using Binary Search as well.

// 3) Maths :
// We know that there are total 3 cups.
// If the largest cup is even greater than the sum of the other 2 cups combined then we are bottlenecked by the maximum ,so this maximum is our answer.
// Otherwise , no single type dominates , in this case , we can pair can 2 cups to get our answer.
// If sum of all is even , we pair every 2 cups , so it is sum/2.
// If sum of all is odd , we are left with 1 cup at the end at the last second then we need to add +1 as well for that odd cup.
// Doing (sum+1)/2 will make it totally work for even and odd also.
// Time : O(1)
// Space : O(1)
int fillCups(vector<int> &amount)
{
    int maximum = max(amount[0], max(amount[1], amount[2]));
    int sum = amount[0] + amount[1] + amount[2];
    if (maximum > (sum - maximum))
    {
        return maximum;
    }
    else
    {
        return (sum + 1) / 2;
    }
}

int main()
{
    vector<int> v = {1, 4, 2};
    cout << "Minimum Time to fill these Cups : " << fillCups(v) << endl;
    return 0;
}
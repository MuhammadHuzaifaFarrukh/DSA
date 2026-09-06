#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

/*
You are given an integer array heights representing the heights of buildings, some bricks, and some ladders.
You start your journey from building 0 and move to the next building by possibly using bricks or ladders.
While moving from building i to building i+1 (0-indexed),
If the current building's height is greater than or equal to the next building's height, you do not need a ladder or bricks.
If the current building's height is less than the next building's height, you can either use one ladder or (h[i+1] - h[i]) bricks.
Return the furthest building index (0-indexed) you can reach if you use the given ladders and bricks optimally.

Input: heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
Output: 4
Explanation: Starting at building 0, you can follow these steps:
- Go to building 1 without using ladders nor bricks since 4 >= 2.
- Go to building 2 using 5 bricks. You must use either bricks or ladders because 2 < 7.
- Go to building 3 without using ladders nor bricks since 7 >= 6.
- Go to building 4 using your only ladder. You must use either bricks or ladders because 6 < 9.
It is impossible to go beyond building 4 because you do not have any more bricks or ladders.

Input: heights = [4,12,2,7,3,18,20,3,19], bricks = 10, ladders = 2
Output: 7

Input: heights = [14,3,19,3], bricks = 17, ladders = 0
Output: 3
*/

// We use a Min-Heap + Greedy here.
// We will iterate from all heights array.
// Then we check if the next climb needs ladder/bricks or not.
// If climb > 0 , it means we need either ladder or bricks.
// So we push this climb into our min heap.
// Then we check if the size of min heap exceeds ladders , which means that we should use bricks for the minimum climb instead of doing it with ladders.
// So we check if we can use bricks for this minimum climb, if not (bricks - x < 0) , then it means we cannot reach the next building and we return.
// Otherwise we update bricks and move on.
// Time : O(nlogL) where L is the number of ladders held by our min-heap , as soon as climbs become more than ladder we immediately pop it , so each push / pop takes O(logL) time.
// Space : O(L) where L is the number of ladders held by our min-heap.
int furthestBuilding(vector<int> &heights, int bricks, int ladders)
{
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < heights.size() - 1; i++)
    {
        int climb = (heights[i + 1] - heights[i]);
        if (climb > 0)
        {
            pq.push(climb);
            if (pq.size() > ladders)
            {
                int x = pq.top();
                pq.pop();
                if (bricks - x < 0)
                {
                    return i;
                }
                bricks -= x;
            }
        }
    }
    return heights.size() - 1;
}

// Using max-heap.
// We flip our choice.
// When we see a climb>0 , we push it in our max heap.
// We subtract it from our bricks , if it becomes < 0 , it means we are out of bricks.
// So we pop the max value of climb and use a ladder for it.
// If we are out of ladders as well , then we stop right there.
// If we are able to use a ladder , then we add the max value of climb in the bricks as we had used a ladder for it.
// Time : O(nlogn)
// Space : O(n)
int furthestBuilding2(vector<int> &heights, int bricks, int ladders)
{
    priority_queue<int> pq;
    for (int i = 0; i < heights.size() - 1; i++)
    {
        int climb = (heights[i + 1] - heights[i]);
        if (climb > 0)
        {
            pq.push(climb);
            bricks -= climb;
            if (bricks < 0)
            {
                int x = pq.top();
                pq.pop();
                if (ladders == 0)
                {
                    return i;
                }
                ladders--;
                bricks += x;
            }
        }
    }
    return heights.size() - 1;
}

int main()
{
    vector<int> heights = {4, 12, 2, 7, 3, 18, 20, 3, 19};
    int bricks = 10;
    int ladders = 2;
    cout << "Furthest Building that can be reached : " << furthestBuilding(heights, bricks, ladders) << endl;
    return 0;
}
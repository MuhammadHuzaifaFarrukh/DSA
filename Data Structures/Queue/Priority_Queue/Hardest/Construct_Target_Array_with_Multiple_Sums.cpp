#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

using namespace std;

/*
You are given an array target of n integers. From a starting array arr consisting of n 1's, you may perform the following procedure :

let x be the sum of all elements currently in your array.
choose index i, such that 0 <= i < n and set the value of arr at index i to x.
You may repeat this procedure as many times as needed.
Return true if it is possible to construct the target array from arr, otherwise, return false.

Input: target = [9,3,5]
Output: true
Explanation: Start with arr = [1, 1, 1]
[1, 1, 1], sum = 3 choose index 1
[1, 3, 1], sum = 5 choose index 2
[1, 3, 5], sum = 9 choose index 0
[9, 3, 5] Done

Input: target = [1,1,1,2]
Output: false
Explanation: Impossible to create target array from [1,1,1,1].
*/

// Heap + Simulation.
// We know that if we try to make from [1,1,1,1] to Target , it will be very difficult.
// Because one small step wrong , and we will never be able to reach target.
// However we can try reverse , that is making target to 1s.
// That simulation is easy for us.
// So we try to see if we can make the 1s from given target , we return 1 otherwise 0.
// Let's say we have [10,25,1,37] So we can see that [1,1,1,1] -> [4,1,1,1] -> [7,1,1,1] -> [10,1,1,1] -> [10,25,1,1] -> [10,25,1,37].
// If we observe it reversed : [10,25,1,37] -> [10,25,1,1] -> [10,13,1,1] -> [10,1,1,1] -> [7,1,1,1] -> [4,1,1,1] -> [1,1,1,1].
// We can see that every time , we are choosing the maximum element , and subtracting the remaining sum from it to make it 1.
// We keep subtracting until we get the maximum element as 1.
// So we can get the maximum element in O(1) using max heap ofcourse.
// We will put all the elements inside the max heap.
// We run our max heap until we get the max element as 1.
// Now we have to make our maximum to 1 , for that we take our maximum as pq.top().
// Then we have to subtract this maximum from the sum of the whole array to get the sum of the remaining elements.
// So we take sum of the array as well before this.
// We get the remaining sum as Total Sum - This Max Element (73 - 37) = 36 (10+25+1)
// We know that this element was made as Max using sum of its own value and the sum of other elements.
// So we get this element by subtracting the Max element - Remaining Elements sum.
// We also update new array sum as the remaining elements sum and this elements value (not maximum now).
// Suppose we have only this array [2] , then we cannot make it to [1] because there are no other elements so when we do 2-2 = 0 , remaining sum becomes 0.
// Also when we have [1,1,1,2] , we cannot make it to [1,1,1,1] because here max is 2 , and remaining sum = 3 , so we cannot do 2-3 because it would never make it 1.
// So we know that in these two cases where remainingSum <= 0 and remainingSum >= Max Element.
// Now suppose we get : [1,1000] , we know that it can get to [1,1] but still we are performing almost 1000 operations to make it reach [1,1] by subtracting 1 each time.
// So for this we can just take modulo of maximum with remaining sum instead of subtracting , this would skip all the subtractions that were needed to do.
// But now , if we do 1000%1 , this would be 0 , but we can clearly see that we can make it [1,1] so we can put a check that if this % answer == 0 then the remaining sum must be 1 only then the answer is possible , in all other cases it won't be possible.
// See [1,2,6]->[1,2,3]->[1,1,0] , see that 6%3 == 0 but its remaining sum is not 1 , so we can never reach [1,1,1] because we cannot stop even while subtracting step by step.
// Also this modulo operator works in all the normal cases as well where we were performing subtractions like 37%36 (37-36) , 25%12 (25-12) , 13%12 (13-12) , 10%3 (10-3-3-3).

// Time Complexity :
// We build heap using step down : O(n)
// Then we perform maximum % RemainingSum which is identical to Euclidean Algorithm , so we can say it as log(m) where m is the maximum of all elements of the array.
// Then we perform this whole heap push/pop operations for logm times = O(logm*logn).
// Total Time : O(n+logm*logn)
// If we had chosen (-) instead of (%) it would have take time : O(n + mlogn) where m is the maximum of the array.

// Space Complexity :
// We store all 'n' elements in our heap.
// Extra = Total Space = O(n)
bool isPossible(vector<int> &target)
{
    priority_queue<int> pq(target.begin(), target.end());
    int sum = 0;
    for (int i = 0; i < target.size(); i++)
    {
        sum += target[i];
    }

    int maximum, remSum, val;
    while (pq.top() != 1)
    {
        maximum = pq.top();
        pq.pop();
        remSum = sum - maximum;

        // Impossible Cases :
        if (remSum <= 0 || remSum >= maximum)
        {
            return 0;
        }

        // val = maximum - remSum;  // Can get TLE.
        val = maximum % remSum;
        if (val == 0) // Need to check must.
        {
            if (remSum == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        sum = remSum + val;
        pq.push(val);
    }
    return 1;
}

// Binary Search or Quickselect won't work here.

int main()
{
    vector<int> v = {10, 25, 1, 37};
    cout << " Is it possible ? " << boolalpha << isPossible(v) << endl;
    return 0;
}
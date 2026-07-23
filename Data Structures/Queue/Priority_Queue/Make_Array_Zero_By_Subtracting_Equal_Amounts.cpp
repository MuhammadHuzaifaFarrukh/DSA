#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
using namespace std;

/*
You are given a non-negative integer array nums. In one operation, you must:

Choose a positive integer x such that x is less than or equal to the smallest non-zero element in nums.
Subtract x from every positive element in nums.
Return the minimum number of operations to make every element in nums equal to 0.

Input: nums = [1,5,0,3,5]
Output: 3
Explanation:
In the first operation, choose x = 1. Now, nums = [0,4,0,2,4].
In the second operation, choose x = 2. Now, nums = [0,2,0,0,2].
In the third operation, choose x = 2. Now, nums = [0,0,0,0,0].
*/

// 1) By using Min-Heap :
// Time :
// Inserting 'n' elements take nlogn time and then processing each 'n' element popping out also takes nlogn time.
// Total Time : O(nlogn)

// Space :
// PQ stores at most n numbers.
// Total Space : O(n)
int minimumOperations(vector<int> &nums)
{
    // Min-heap to store positive integers
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int num : nums)
    {
        if (num > 0)
        {
            pq.push(num);
        }
    }

    int steps = 0;
    int subtracted_sum = 0;

    while (!pq.empty())
    {
        int current_min = pq.top();
        pq.pop();

        // Check if this number is still > 0 after past subtractions
        if (current_min - subtracted_sum > 0)
        {
            // Update total subtracted value to this new minimum
            subtracted_sum = current_min;
            steps++;
        }
    }

    return steps;
}

// 2) Using unordered Set :
// We know that we only need non-zero elements and the non-duplicates (cause duplicates are 0 at the same time)
// Also we keep selecting the minimum elements to subtract.
// So if we have {1,3,5} , then we select 1, {0,2,4} then we select 2 {0,0,2} and again 2.
// So the number of unique values are needed to make each unique number zero at each stage.
// Time : O(n) (or O(n^2) in worst case)
// Space : O(N) where N is the number of distinct positive integers.
int minimumOperations(vector<int> &nums)
{
    unordered_set<int> unique_positives;

    for (int num : nums)
    {
        if (num > 0)
        {
            unique_positives.insert(num);
        }
    }

    return unique_positives.size();
}
int main()
{
    vector<int> v = {1, 5, 0, 5, 1, 3};
    cout << "Minimum Steps to reduce array all elements to zero : " << minimumOperations(v) << endl;
    return 0;
}
#include <iostream>
#include <queue>
using namespace std;

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

        // Add to total score (use long long to avoid overflow!)
        score += maxVal;

        // Replace with ceil(maxVal / 3) and push back
        // Using ceil(maxVal/3) may do Overflow or some errors so we use simplified formula
        // Formula for ceil(a/b) is (a + b - 1) / b
        pq.push((maxVal + 2) / 3);
    }

    return score;
}

int main()
{
    return 0;
}
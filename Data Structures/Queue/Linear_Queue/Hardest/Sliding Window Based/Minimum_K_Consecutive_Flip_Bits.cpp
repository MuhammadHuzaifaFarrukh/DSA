#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <deque>

using namespace std;
// This is almost identical to another problem but with easier constraints and can be solved easily.


// 1) Brute Force :
// Where you find 0 , take that window and flip bits and keep doing it O(n) checks
// Time Complexity : O(n^2)
int minKBitFlips1(vector<int> &nums, int k)
{
    int flips = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] == 0)
        {
            if (i + k > nums.size())
            {
                return -1;
            }
            for (int j = i; j < i + k; j++)
            {
                nums[j] = !nums[j]; // We can also write : nums[j] = 1 - nums[i];
            }
            flips++;
        }
    }
    return flips;
}

// 2) Another Method , that we make another array of same size to store count of how many times we flipped each element of the array.
// Zero flipped Odd times -> 1 and Even Times -> 0
// One  flipped Odd times -> 0 and Even Times -> 1
// We keep checking it until end.
// So we are running a loop till n and for each i , we update count k times in other array.
// So Time Complexity : O(nk).



// 3) Almost same as above , but this time we store the index in queue.
// We use q.size() as our number of flips .
// We have two cases to flip only when q.size() is odd times for 1 and 0
// So we will implement it like that.
// Time Complexity : O(n)
int minKBitFlips(vector<int> &nums, int k)
{
    queue<int> q;
    int flip = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (!q.empty() && q.front() < i)
        {
            q.pop();
        }
        if (q.size() % 2 == nums[i])
        {
            if (i + k - 1 >= nums.size())
            {
                return -1;
            }
            q.push(i + k - 1);
            flip++;
        }
    }
    return flip;
}

int main()
{
    vector<int> v = {0, 0, 1, 0, 0, 1, 1, 0, 1, 0};
    int n = 4;

    cout << "Minimum K Consecuive Flip Bits : " << minKBitFlips(v, n);
    return 0;
}
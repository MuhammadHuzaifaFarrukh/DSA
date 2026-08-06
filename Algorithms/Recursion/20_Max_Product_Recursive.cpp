#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int maxProduct(vector<int> &nums, int i = 0, int m1 = INT_MIN, int m2 = INT_MIN)
{
    // Base Case: We've scanned the entire array
    if (i == nums.size())
    {
        return m1 * m2;
    }

    int current = nums[i];

    // Manual update logic for the two largest elements
    if (current > m1)
    {
        m2 = m1;      // Old top becomes second top
        m1 = current; // Current becomes new top
    }
    else if (current > m2)
    {
        m2 = current; // Current is only bigger than the second top
    }

    // Recursive call: pass the updated top two values to the next index
    return maxProduct(nums, i + 1, m1, m2);
}

int main()
{
    vector<int> v = {3, 8, 8, 2};

    cout << "Maximum Product: " << maxProduct(v, 0) << endl;

    return 0;
}
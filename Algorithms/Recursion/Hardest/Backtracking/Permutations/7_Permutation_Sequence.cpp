#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
/*
The set [1, 2, 3, ..., n] contains a total of n! unique permutations.
By listing and labeling all of the permutations in order, we get the following sequence for n = 3:
"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.
*/

// 1) The "DICTIONARY" Algorithm :
// We generate a vector of size 'n'.
// Then we apply our next permutation function (k-1) times on that vector.
// We do it not k times because the vector itself is counted as 1 permutation.
// We find the next permutation (k-1) times and then we just store our answer in string result.
// Time Complexity:
// Average Time would be just O(n*(k-1)) = O(nk)
// However in the worst , k = n! so it takes time O(n*n!)
// Time : O(n*n!).

// Space Complexity:
// We made another new vector of size 'n' = O(n)
// Space : O(n)
string getPermutation(int n, int k)
{
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        v[i] = i + 1;
    }
    for (int i = 0; i < k - 1; i++)
    {
        nextPermutation(v);
    }
    string result = "";
    for (int i = 0; i < v.size(); i++)
    {
        result += to_string(v[i]);
    }
    return result;
}

void nextPermutation(vector<int> &nums)
{
    int i = nums.size() - 2;
    // We must have atleast two numbers to find the next unique permutation

    // Step 1: Find the rightmost inversion (the pivot)
    while (i >= 0 && nums[i] >= nums[i + 1])
    {
        i--;
    }

    // Step 2 & 3: If a pivot is found, find the successor and swap
    if (i >= 0)
    {
        int j = nums.size() - 1;

        // This also works :
        while (nums[j] <= nums[i])
        {
            j--;
        }

        swap(nums[i], nums[j]);
    }

    // Step 4: Reverse the suffix to reset it to the lowest possible order
    reverse(nums.begin() + i + 1, nums.end());
}

// 2) By Factorial Block Method :
/*
The Core Intuition
If n = 4, our available digits are [1, 2, 3, 4]. The total number of permutations is 4-factorial = 24. If we group these permutations by their very first digit, we get 4 equal-sized blocks:
Permutations starting with 1: 3! = 6 possibilities.
Permutations starting with 2: 3! = 6 possibilities.
Permutations starting with 3: 3! = 6 possibilities.
Permutations starting with 4: 3! = 6 possibilities.

If the problem asks us to find the 14th (k = 14) permutation, we can calculate its group instantly:
Block 1 (starts with 1) covers permutations 1 to 6.
Block 2 (starts with 2) covers permutations 7 to 12.
Block 3 (starts with 3) covers permutations 13 to 18.
Since 14 falls in the 13–18 range, the first digit must be 3. We just skipped 12 steps in a single calculation! We then repeat this exact process for the remaining positions.

Step-by-Step Walkthrough (n = 4, k = 14)
To make the array indexing match our math easily, we switch to 0-based indexing by setting k = k - 1. So, our target is index k = 13.

Step 1: Find the 1st digit
Remaining digits available: [1, 2, 3, 4]
If we lock the first digit, the remaining 3 positions can form 3-factorial = 6 variations.
Block Index = 13 / 6 = 2.
Digit at index 2 of our available list is 3.
Remove 3 from our choices. Our string is now "3".
Update our target index: k = 13 modulo 6 = 1.

Step 2: Find the 2nd digit
Remaining digits available: [1, 2, 4]
If we lock this digit, the remaining 2 positions can form 2-factorial = 2 variations.
Block Index = 1 / 2 = 0.
Digit at index 0 of our available list is 1.
Remove 1 from our choices. Our string is now "31".
Update our target index: k = 1 modulo 2 = 1.

Step 3: Find the 3rd digit
Remaining digits available: [2, 4]
The remaining 1 position can form 1-factorial = 1 variation.
Block Index = 1 / 1 = 1.
Digit at index 1 of our available list is 4.
Remove 4 from our choices. Our string is now "314".
Update our target index: k = 1 modulo 1 = 0.

Step 4: Find the last digit
Only digit left is 2.

Final string: "3142".
*/

// Time Complexity :
// Each time we find a number we erase it which takes time O(n)
// So our time comp is O(n^2) or O(n) if we neglect the erasing time.

// Space Complexity :
// We used extra vector 'digits' so that makes it O(n).
// Space : O(n)
string getPermutation(int n, int k)
{
    vector<int> digits;
    int factorial = 1;

    // 1. Precompute factorials up to (n-1)! and fill our available digits list
    for (int i = 1; i < n; i++)
    {
        factorial *= i;
        digits.push_back(i);
    }
    digits.push_back(n); // digits is now [1, 2, ..., n]

    // 2. Convert k to 0-based indexing
    k = k - 1;
    string result = "";

    // 3. Extract digits one by one
    for (int i = 0; i < n; i++)
    {
        // Find which block index our k lands in
        int block_idx = k / factorial;
        result += to_string(digits[block_idx]);

        // Remove the used digit from our available options pool
        digits.erase(digits.begin() + block_idx);

        // If there are digits left, update k and calculate the next factorial block size
        if (digits.empty())
            break;
        k = k % factorial;
        factorial = factorial / digits.size();
    }

    return result;
}

int main()
{
    int n = 4;
    int k = 2;
    string result = getPermutation(n, k);
    cout << "The " << k << "th Permutation of " << n << " : " << result << endl;
    return 0;
}
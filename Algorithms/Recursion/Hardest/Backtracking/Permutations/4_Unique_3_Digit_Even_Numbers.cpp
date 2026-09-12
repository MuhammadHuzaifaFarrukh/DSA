#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

/*
You are given an array of digits called digits.
Your task is to determine the number of distinct three-digit even numbers that can be formed using these digits.
Note: Each copy of a digit can only be used once per number, and there may not be leading zeros.

Input: digits = [1,2,3,4]
Output: 12
Explanation: The 12 distinct 3-digit even numbers that can be formed are 124, 132, 134, 142, 214, 234, 312, 314, 324, 342, 412, and 432. Note that 222 cannot be formed because there is only 1 copy of the digit 2.

Input: digits = [0,2,2]
Output: 2
Explanation: The only 3-digit even numbers that can be formed are 202 and 220. Note that the digit 2 can be used twice because it appears twice in the array.

Input: digits = [6,6,6]
Output: 1
Explanation: Only 666 can be formed.

Input: digits = [1,3,5]
Output: 0
Explanation: No even 3-digit numbers can be formed.
*/

// 1) Brute Force
// We generate all the possible pairs of length 3 permutations nP3.
// Then we check if its first letter is 0 or not and if its odd or not.
// If either true then we don't save it , otherwise we save it in our unordered set.
// Because duplicates can yield same permutations , so we use set here.
// Time Complexity :
// At level 0 , we loop N times.
// At level 1 , we loop (N-1) times.
// At level 2 , we loop (N-2) times.
// Maximum call stack goes only to level 0-2 (3 levels since we stop at k=3).
// Total recursive brances : N(N-1)*(N-2) = N^3 = O(n^3)
// Copying the elements is also fixed at 3 elements only so its also O(1).
// Time : O(n^3)

// Space Complexity :
// The Call Space only goes to level 0-2 (3 levels since we stop at k=3).
// The unordered set also stores answers from 100-998 numbers (fixed).
// Space : O(1)

// Its not n! or nn! time or space :
// A standard backtracking algorithm that generates full permutations goes up to index == N, exploring N! leaves. Here, by hardcoding the stopping condition at index == 3, you pruned the decision tree at depth 3. The algorithm computes P(N, K) where K = 3, giving:
// Work = N! / (N - 3)! = N * (N - 1) * (N - 2) = O(N^3)
int totalNumbers(vector<int> &digits)
{
    unordered_set<int> ans;
    PermutationsNPK(digits, ans, 0);
    return ans.size();
}
void PermutationsNPK(vector<int> &nums, unordered_set<int> &ans, int index)
{
    if (index == 3)
    {
        vector<int> current_permutation(nums.begin(), nums.begin() + 3);
        if (current_permutation[0] == 0)
        {
            return;
        }
        int x = current_permutation[0] * 100 + current_permutation[1] * 10 + current_permutation[2];
        if (x % 2 == 0)
        {
            ans.insert(x);
        }
        return;
    }

    for (int i = index; i < nums.size(); i++)
    {
        swap(nums[i], nums[index]);
        PermutationsNPK(nums, ans, index + 1);
        swap(nums[i], nums[index]);
    }
}

// 2) Using Maths :
// We know that total answers we are gonna get are from 100-998
// So we count the number of digits in a freq map.
// Then we loop from 100-998 and check if we can make which numbers in this range using our map.
// If we can make , we increase the count++.
// While checking this , we make sure to copy our frequency map because
// When we are making a number , we have to do -- in our freq map , and that can decrease for other numbers.
// Similarly we cannot do like using if(freq[unit]-1) because it is possible that same numbers may be involved so we don't know how many times to subtract.
// So we make a copy and use that.
// Time : O(n)
// Space : O(1)
int totalNumbers2(vector<int> &digits)
{
    vector<int> freq(10, 0);
    // All even 3 digit numbers are between 100-998
    for (int i = 0; i < digits.size(); i++)
    {
        freq[digits[i]]++;
    }

    int count = 0;
    for (int num = 100; num <= 998; num += 2)
    {
        int unit = num % 10;
        int tens = (num / 10) % 10;
        int huns = (num / 100);

        vector<int> copy = freq;
        copy[unit]--;
        copy[tens]--;
        copy[huns]--;
        if (copy[unit] >= 0 && copy[tens] >= 0 && copy[huns] >= 0)
        {
            count++;
        }
    }
    return count;
}
int main()
{
    vector<int> v = {1, 2, 3, 4};
    cout << "Unique 3 Digit-Even Numbers are : " << totalNumbers(v) << endl;
    return 0;
}
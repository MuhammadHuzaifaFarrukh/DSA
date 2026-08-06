#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

/*
Given an array of strings nums containing n unique binary strings each of length n, return a binary string of length n that does not appear in nums.
If there are multiple answers, you may return any of them.

Input: nums = ["01","10"]
Output: "11"
Explanation: "11" does not appear in nums. "00" would also be correct.
*/

// We generate all the possible N-Bit Binary Strings.
// Then we create a hash map and compare the given strings and our newly string that has all the combinations.
// Time : O(2^n) or O(n*2^n).
// Space : O(n*2^n) (This includes all the bit strings for 'n' and the unordered map as well)

string findDifferentBinaryString(vector<string> &nums)
{
    int n = nums[0].size();
    vector<string> ans;
    string temp = "";
    helper(n, temp, ans);
    unordered_map<string, bool> m;
    for (int i = 0; i < nums.size(); i++)
    {
        m[nums[i]] = 1;
    }
    for (int i = 0; i < ans.size(); i++)
    {
        if (m[ans[i]] == 0)
        {
            return ans[i];
        }
    }
    return "";
}

void helper(int n, string &temp, vector<string> &ans)
{
    if (temp.size() == n)
    {
        ans.push_back(temp);
        return;
    }

    temp.push_back('0');
    helper(n, temp, ans);
    temp.pop_back();

    temp.push_back('1');
    helper(n, temp, ans);
    temp.pop_back();
}

// 2) Cantor's Diagonal :
/*
Cantor proved that we can never list all real numbers because no matter how long our list is, we can always generate a new number that isn't on it.
How the Trick Works in Practice

Imagine you are given N = 3 binary strings:
Row 0:   [0] 1  1
Row 1:    1 [1] 0
Row 2:    0  0 [0]
We want to construct a new string ans of length 3 that is guaranteed to be different from every single row above.

Instead of generating all possibilities or searching through sets, we focus exclusively on the main diagonal (the elements at [i][i]):
Look at nums[0][0]: It's '0'. Flip it to '1'.
Why? Because ans[0] is now '1', ans can never match nums[0] (they differ at position 0).
Look at nums[1][1]: It's '1'. Flip it to '0'.
Why? Because ans[1] is now '0', ans can never match nums[1] (they differ at position 1).
Look at nums[2][2]: It's '0'. Flip it to '1'.
Why? Because ans[2] is now '1', ans can never match nums[2] (they differ at position 2).
Our resulting string is "101".

Why Is It 100% Guaranteed to Work?
Ask yourself: Could "101" be equal to nums[0]?
No, because we explicitly made the 0th character different ('1' vs '0').
Could it be equal to nums[1]?
No, because we explicitly made the 1st character different ('0' vs '1').
Could it be equal to nums[2]?
No, because we explicitly made the 2nd character different ('1' vs '0').
By walking down the diagonal and inverting the i-th bit for the i-th string, your generated string disagrees with every row in the input at least at index i.

This works for m==n (Square Matrix) otherwise we would have to change its variation.

// Time : O(n)
// Space : O(1) (or O(n) including the answer string)
string findDifferentBinaryString(vector<string> &nums)
{
    string temp = "";
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i][i] == '1')
        {
            temp += "0";
        }
        else
        {
            temp += "1";
        }
    }
    return temp;
}
*/

int main()
{
    vector<string> ans = {"01", "10"};

    return 0;
}
#include <iostream>
#include <string>
#include <vector>

using namespace std;
/*
Generate all the N Bitstrings without adjacent zeros.
Input: n = 3
Output: ["010","011","101","110","111"]
Explanation:
The valid strings of length 3 are: "010", "011", "101", "110", and "111".
*/

// 1) Generate all the N Bitstrings and at the time of base case , iterate through the temp to see adjacent zeroes present or not.
// Time : O(n*2^n)
// Space : O(n*2^n)  ( or O(n*1.618^n) to be precise)

// 2) Use an index value as a reference.
// Zero choice is available only when index is 0 or if the previous index is not zero.
// So each time when we do a function call we do index+1 and after coming back we do index-1.
// Time Complexity :
// Total nodes at approx : 2^n (or 1.618^n to be precise as they follow a Fibonnacci series pattern)
// If we neglect the Push_Back() time then :
// Time : O(2^n)  (or O(1.618^n) to be precise).

// Space Complexity :
// Maximum depth of stack is 'n' = O(n)
// Total valid strings in answer are of 2^n (or 1.618^n to be precise).
// Each string is of length 'n'.
// Space : O(n*2^n)  (or O(n*1.618^n)  to be precise).

// No need to take index as reference variable and then no need to do index--.
void helper(int n, string &temp, vector<string> &ans, int &index)
{
    if (temp.size() == n)
    {
        ans.push_back(temp);
        return;
    }

    if ((index > 0 && temp[index - 1] != '0') || (index == 0))
    {
        temp.push_back('0');
        index++;
        helper(n, temp, ans, index);
        index--;
        temp.pop_back();
    }

    temp.push_back('1');
    index++;
    helper(n, temp, ans, index);
    index--;
    temp.pop_back();
}

int main()
{
    int n;
    cout << "Enter n : ";
    cin >> n;

    vector<string> ans;
    string temp = "";

    int index = 0;
    helper(n, temp, ans, index);

    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    return 0;
}
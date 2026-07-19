#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
You are given a string s consisting of lowercase English letters.
A duplicate removal consists of choosing two adjacent and equal letters and removing them.
We repeatedly make duplicate removals on s until we no longer can.
Return the final string after all such duplicate removals have been made. It can be proven that the answer is unique.

Input: s = "abbaca"
Output: "ca"
Explanation:
For example, in "abbaca" we could remove "bb" since the letters are adjacent and equal, and this is the only possible move.
The result of this move is that the string is "aaca", of which only "aa" is possible, so the final string is "ca".
*/

// We make use  of the string as our stack.
// We can just pop if our result contains something and last character in it matches the current one.
// Otherwise we push characters in it.
// Time : O(n)
// Space : O(1) or O(n) if we count our string result also.

// This question is the same as removing adjacent same strings using stack.
string removeDuplicates(string s)
{
    // stack<char> st;
    string result = "";
    result.push_back(s[0]);
    for (int i = 1; i < s.length(); i++)
    {
        if (!result.empty() && (result.back() == s[i]))
        {
            result.pop_back();
        }
        else
        {
            result.push_back(s[i]);
        }
    }
    return result;
}
int main()
{
    string s = "azxxzy";
    cout << "String after removal of adjacent duplicates : " << removeDuplicates(s) << endl;
    return 0;
}
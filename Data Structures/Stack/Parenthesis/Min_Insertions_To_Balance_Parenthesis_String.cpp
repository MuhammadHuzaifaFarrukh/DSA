#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
Given a parentheses string s containing only the characters '(' and ')'.
A parentheses string is balanced if:
Any left parenthesis '(' must have a corresponding two consecutive right parenthesis '))'.
Left parenthesis '(' must go before the corresponding two consecutive right parenthesis '))'.
In other words, we treat '(' as an opening parenthesis and '))' as a closing parenthesis.
For example, "())", "())(())))" and "(())())))" are balanced, ")()", "()))" and "(()))" are not balanced.
You can insert the characters '(' and ')' at any position of the string to balance it if needed.
Return the minimum number of insertions needed to make s balanced.


Input: s = "(()))"
Output: 1
Explanation: The second '(' has two matching '))', but the first '(' has only ')' matching. We need to add one more ')' at the end of the string to be "(())))" which is balanced.

Input: s = "())"
Output: 0
Explanation: The string is already balanced.

Input: s = "))())("
Output: 3
Explanation: Add '(' to match the first '))', Add '))' to match the last '('.
*/

// We cannot use stack here because now we have to keep count of two closing strings parenthesis for 1 open.
// We will track this now using variables.
// Openneeded counts number of right parenthesis required to balance out left.
// Insertions counts the total number of brackets (( or )) we are forced to manually insert into the string to fix imbalances as we scan from left to right.
// Now when we reach opening brace , we increase the need for the right parenthesis by 2.
// When we reach closing braces , we decrease the need for the right parenthesis by 1.
// Now if we have a string like ))( , then our openneeded becomes negative , so for that we keep a check and increase insertions by 1 for 1 left parenthesis , and increase openneeded by 2 out of which 1 we have already encountered.
// Then if our openneeded becomes odd e.g (()()) then at the 4th index when we have '(' our open becomes 5 but we have to only insert even number so we give 1 to insertions and subtract 1 from open.
// We return our final answer as (insertions + openneeded).
// Time Complexity : O(n)
// Space Complexity : O(n)
int minInsertions(string s)
{
    int insertions = 0;
    int openNeeded = 0; // Counts missing ')' needed for active '('

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(')
        {
            // Each '(' requires 2 closing brackets
            openNeeded += 2;

            // If openNeeded was odd, we had an unmatched single ')' before this '('
            if (openNeeded % 2 != 0)
            {
                insertions++; // Insert 1 missing ')'
                openNeeded--; // Balance it out
            }
        }
        else
        { // s[i] == ')'
            openNeeded--;

            // Too many closing brackets encountered!
            if (openNeeded < 0)
            {
                insertions++;    // Insert 1 missing '(' on the left
                openNeeded += 2; // That new '(' needs 2 ')', one of which is s[i]
            }
        }
    }

    // Any remaining needed ')' must be inserted at the end
    return insertions + openNeeded;
}

int main()
{
    string s = "))())(";
    cout << "Minimum Insertions required : " << minInsertions(s) << endl;
    return 0;
}
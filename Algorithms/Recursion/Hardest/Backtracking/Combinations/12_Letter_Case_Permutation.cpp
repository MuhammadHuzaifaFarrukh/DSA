#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
Given a string s, you can transform every letter individually to be lowercase or uppercase to create another string.
Return a list of all possible strings we could create.
Return the output in any order.

Input: s = "a1b2"
Output: ["a1b2","a1B2","A1b2","A1B2"]
*/

// We solve this using the inclusion-exclusion principle of choices.
// We can either take a character lowercase or uppercase.
// If we encounter digit , then take it as it is.
// Now if we see digit we can use like if-else so that digit is always appended and in characters we have choices.
// We take our choice for lowercase and then uppercase.
// This is like a combination problem for the characters only not numbers.

// Time Complexity :
// Every new character creates a new branch of choices (Uppercase or Lowercase)
// O(2^k) where k is the number of characters.

// Space Complexity :
// Max depth of stack is O(n) and no extra space used.
// Now if we see the answer array , it is unique for each new letter.
// So answer array contains 2^k combinations where each combination is of size 'n'.
// So total Space becomes : O(n*2^k).
void letterCasePermutation(string &s, vector<string> &ans, string &temp, int index)
{
    if (index == s.size())
    {
        ans.push_back(temp);
        return;
    }

    char ch = s[index];

    if (isdigit(ch))
    {
        // It's a digit, just take it as is
        temp.push_back(ch);
        letterCasePermutation(s, ans, temp, index + 1);
        temp.pop_back(); // Backtrack
    }
    else
    {
        // Choice 1: Keep/convert to lowercase
        temp.push_back(tolower(ch));
        letterCasePermutation(s, ans, temp, index + 1);
        temp.pop_back(); // Backtrack

        // Choice 2: Keep/convert to uppercase
        temp.push_back(toupper(ch));
        letterCasePermutation(s, ans, temp, index + 1);
        temp.pop_back(); // Backtrack
    }
}

int main()
{
    string s = "a1b2";
    vector<string> ans;
    int index = 0;
    string temp = "";
    letterCasePermutation(s, ans, temp, index);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    return 0;
}
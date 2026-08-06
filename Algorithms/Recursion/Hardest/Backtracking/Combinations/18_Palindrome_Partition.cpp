#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.

Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]

Input: s = "a"
Output: [["a"]]
*/
// This is a combination question without repetition and with fixed order in which the string appears and whole coverage meaning no string part is left-over.

// We make a palindrome function as well that will check palindrome of our string before calling function recursively.
// We check whether to make a cut on a string's first part that is if we have a string "abc" , then we check if we need to make a cut at 'a' , 'bc' or do we need to make a cut little further or more.
// So that leaves us with two choices.
// Make a cut right at this part or skip the cut at this part and check for next expanding this portion rightwards.
// If we decide to make a cut at this part , then for that , it must be a palindrome and if it is then we make a cut and keep both i and index same as index+1.
// If not , then we proceed and just increase the index by 1 keeping 'i' same.
// At each step , we are just separating our string if it is a palindrome or if not then we are increasing string length to look for another palindromic position.

// Recursive Tree for "aab"
/*
                                            (i=0, index=0)
                                            /               \
                                  (TRY CUT "a")           (SKIP CUT)
                                       /                        \
                    (i=1, index=1)                          (i=0, index=1)
                       /        \                          /          \
              (TRY CUT "a")   (SKIP CUT)              (TRY CUT "aa")   (SKIP CUT)
                   /                \                      /                \
        (i=2, index=2)           (i=1, index=2)        (i=2, index=2)       (i=0, index=2)
              |                        |                  |                    |
       (TRY CUT "b")             (TRY CUT "ab")       (TRY CUT "b")       (TRY CUT "aab")
              |                        |                  |                    |
        [SUCCESS!]                [FAIL: "ab"        [SUCCESS!]           [FAIL: "aab"
     temp: ["a","a","b"]           not palin]        temp: ["aa","b"]      not palin]
*/

// Time Complexity :
// At each branch we have two choices approx so for 'n' characters in string , it makes 2^n choices.
// Time : O(2^n) , or O(n*2^n) if we also include time for 1D copying to 2D vector.

// Space Complexity :
// The max recursive depth of the stack is 'n' -> O(n)
// No other extra space is being used.
// Space : O(n)
// Any string of length 'n' can have valid partitions of upto 2^(n-1).
// So if all the substrings that are cut are palindromes , then answer array will have 2^(n-1) rows and any row at max can go at length 'n'.
// So total space : O(n*2^n).

vector<vector<string>> partition(string s)
{
    vector<vector<string>> ans;
    vector<string> temp;
    palindromicPartitions(ans, temp, s, 0, 0);
    return ans;
}

void palindromicPartitions(vector<vector<string>> &ans, vector<string> &temp, const string &s, int i, int index)
{

    if (index == s.size())
    {
        // If segmentStart also reached the end, we've successfully partitioned the full string!
        if (i == s.size())
        {
            ans.push_back(temp);
        }
        return;
    }

    // --- BRANCH 1: OPTION TO MAKE A CUT HERE ---
    // Substring from segmentStart to currentIndex (inclusive)
    string x = s.substr(i, index - i + 1);

    if (isPalindrome(x))
    {
        temp.push_back(x);
        // CUT MADE: Next segment starts at currentIndex + 1
        palindromicPartitions(ans, temp, s, index + 1, index + 1);
        temp.pop_back(); // Backtrack
    }

    // --- BRANCH 2: OPTION TO SKIP THE CUT ---
    // Keep the same segmentStart, just expand the current substring rightward
    palindromicPartitions(ans, temp, s, i, index + 1);
}

bool isPalindrome(const string &s)
{
    int start = 0, end = s.size() - 1;
    while (start < end)
    {
        if (s[start] != s[end])
        {
            return 0;
        }
        start++;
        end--;
    }
    return 1;
}

// 2) Using for-loop but same logic :
/*
void palindromicPartitions(vector<vector<string>> &ans ,vector<string> temp , string &s, int index )
    {
        if(index == s.size())
        {
            ans.push_back(temp);
            return;
        }
        for(int i =index ; i<s.size() ; i++)
        {
            string x = s.substr(index, i - index + 1);
            if(isPalindrome(x))
            {
                temp.push_back(x);
                palindromicPartitions(ans,temp,s,i+1);
                temp.pop_back();
            }
        }
    }
*/
int main()
{
    string word = "abcaa";
    vector<vector<string>> ans = partition(word);

    for (int i = 0; i < ans.size(); i++)
    {
        for (int j = 0; j < ans[i].size(); j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
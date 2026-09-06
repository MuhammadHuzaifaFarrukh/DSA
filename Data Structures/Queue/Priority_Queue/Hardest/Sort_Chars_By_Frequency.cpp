#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

/*
Given a string s, sort it in decreasing order based on the frequency of the characters. The frequency of a character is the number of times it appears in the string.
Return the sorted string. If there are multiple answers, return any of them.

Input: s = "tree"
Output: "eert"
Explanation: 'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.

Input: s = "cccaaa"
Output: "aaaccc"
Explanation: Both 'c' and 'a' appear three times, so both "cccaaa" and "aaaccc" are valid answers.
Note that "cacaca" is incorrect, as the same characters must be together.

Input: s = "Aabb"
Output: "bbAa"
Explanation: "bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.
*/

// 1) Brute Forcing and sorting characters may take up to O(n^2) time or even n^3 as there are characters , numbers and even captials also.

// 2) Optimized Approach : Use Priority Queue + Hash Map
// We make a separate map for all lower case , upper case and digits.
// Then we add characters in the maps.
// Then from map , we add them into a max heap along with character and its counts.
// This Max heap keeps the highest frequency character at top and in case of same frequency , it will see which letter has greater ASCII val.
// Since the question says in case of same frequency , we can do any order , this will not matter to us then.
// We just use heap to add elements to our answer.
// Time : O(n) , Space : O(n)
string frequencySort(string s)
{
    priority_queue<pair<int, char>> q;
    int digits_count[10] = {0};
    int upper[26] = {0}, lower[26] = {0};
    for (int i = 0; i < s.length(); i++)
    {
        char c = s[i];
        if (c >= 'A' && c <= 'Z')
        {
            upper[c - 'A']++;
        }
        else if (c >= 'a' && c <= 'z')
        {
            lower[c - 'a']++;
        }
        else
        {
            digits_count[c - '0']++;
        }
    }

    for (int i = 0; i < 26; i++)
    {
        if (lower[i] > 0)
        {
            q.push({lower[i], 'a' + i});
        }
    }

    for (int i = 0; i < 26; i++)
    {
        if (upper[i] > 0)
        {
            q.push({upper[i], 'A' + i});
        }
    }

    for (int i = 0; i < 10; i++)
    {
        if (digits_count[i] > 0)
        {
            q.push({digits_count[i], '0' + i});
        }
    }

    string ans = "";
    while (!q.empty())
    {
        ans = ans + string(q.top().first, q.top().second); // We used string init string(Counts, Character).
        q.pop();
    }
    return ans;
}

int main()
{
    return 0;
}
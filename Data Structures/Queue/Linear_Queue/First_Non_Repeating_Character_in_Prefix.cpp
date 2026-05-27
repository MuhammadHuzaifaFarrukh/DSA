#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;


// Add Non_Repeating Characters in a New String Answer and if there is no non-repeating character left then append a '#' symbol.
// If we find more than one non-repeating , then we still continue with the first non-repeating untill it repeats or untill string is ended. And if it repeats then we choose the next non-repeating one.
// If all non-repeating have ended , then we compensate by adding '#' until we find another non-repeating character.
// You have to give answer for each character in the string.

// E.g : Given String : leetcode , Answer is llllllll because 'l' is the first non repeating character that doesn't repeat so it appears for all the indices.
// E.g : Given String : aaabcbdge , Answer is a##bbcccc , 'a' repeated so we placed '#' since there was no other non-repeated char , then when 'b' got repeated , we place 'c' because 'c' was still non-repeated.
// E.g : Given String : aanana , Answer is a#nn##
// 1) Brute force approach : Time : O(n^2) , Space : O(1)


// 2) Optimized , using Queue : Time : O(n) , Space : O(n)
int main()
{
    string s;
    cout << "Enter string: ";
    getline(cin, s);

    int freq[26] = {0};
    queue<char> q;
    string ans = "";

    for (int i = 0; i < s.length(); i++)
    {
        char ch = s[i];

        // 1. Update frequency and add to queue
        freq[ch - 'a']++;
        q.push(ch);

        // 2. Clean the queue: Remove characters from the front that are now repeats
        while (!q.empty() && freq[q.front() - 'a'] > 1)
        {
            q.pop();
        }

        // 3. Determine the result for this prefix
        if (q.empty())
        {
            ans += '#';
        }
        else
        {
            ans += q.front();
        }
    }

    cout << "Result: " << ans << endl;
    return 0;
}

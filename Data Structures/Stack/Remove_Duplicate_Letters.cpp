#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/*
Given a string s, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.
Input: s = "bcabc"
Output: "abc"

Input: s = "bcaac"
Output: "bac"

Input: s = "cbacdcbc"
Output: "acdb"
*/

// Map + String (Stack)
// We make use of the string as our stack.
// We take an unordered map that keeps a count of all elements in the string.
// Now we make a boolean array to keep a track of elements that have been processed or not.
// If result is empty we simply store the character and we also mark this character as seen.
// Now if it appears again , we simply have a track of it in our seen vector.
// Now if a character appears that is smaller than the last character added and the last character added also appears later (by checking its freq > 0) , then we simply pop the last character added and add this smaller one.
// However if the character that appear is smaller than the last character but the last character doesn't appear later ("ca") or its duplicates appeared before ("cca") , then we don't pop out the last character added and add this current one after the larger character.

// Time : O(n)
// Space : O(26)+O(26) = O(1)
// If we count the answer as well , that makes it O(n)
string removeDuplicateLetters(string s)
{
    // 1. Frequency Map: Count occurrences of each character
    vector<int> count(26, 0);
    for (int i = 0; i < s.length(); i++)
    {
        count[s[i] - 'a']++;
    }

    // 2. Seen Set: Tracks if a character is already in our answer
    vector<bool> seen(26, false);

    // 3. Stack: We use std::string as a stack because it lets us
    // look at the back, push, and pop easily while building the final result.
    // By using stack , we increase our memory more.
    string result = "";

    for (int i = 0; i < s.length(); i++)
    {
        // Step A: We passed this character, decrement its remaining count
        count[s[i] - 'a']--;

        // Step B: If it's already in our result, skip it
        if (seen[s[i] - 'a'])
        {
            continue;
        }

        // Step C: Maintain the "monotonic" small-to-large order.
        // While the result isn't empty, the last character is bigger than current,
        // AND that last character appears again later:
        while (!result.empty() && result.back() > s[i] && count[result.back() - 'a'] > 0)
        {
            seen[result.back() - 'a'] = false; // Mark it as not seen
            result.pop_back();                 // Remove it from our stack
        }

        // Step D: Add the current character to our result
        result.push_back(s[i]);
        seen[s[i] - 'a'] = true;
    }

    return result;
}
int main()
{
    string s = "cbacdcbc";
    cout << "Removed Duplicates and in the smallest possible lexicographical order : " << removeDuplicateLetters(s) << endl;
    return 0;
}
#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;


// Add Non_Repeating Characters in a New String Answer and if there is no non-repeating character left then append a '#' symbol.
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

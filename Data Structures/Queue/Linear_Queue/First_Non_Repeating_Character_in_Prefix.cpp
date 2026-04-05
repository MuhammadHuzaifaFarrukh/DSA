#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

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
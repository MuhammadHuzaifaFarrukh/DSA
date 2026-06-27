#include <iostream>
#include <queue>
using namespace std;

// Return the index of first unique character in the string
// 1) Brute force approach : Time : O(n^2) , Space : O(1)

// 2) Optimized , using Queue : Time : O(n) , Space : O(n)
int firstUniqChar(string s)
{
    int count[26] = {0};
    queue<int> q;

    for (int i = 0; i < s.length(); i++)
    {
        char c = s[i];
        count[c - 'a']++; // Increment frequency
        q.push(i);        // Add current index to queue

        // "The Cleanup": Remove from front if it's no longer unique
        while (!q.empty() && count[s[q.front()] - 'a'] > 1)
        {
            q.pop();
        }
    }
    if (q.empty())
    {
        return -1;
    }
    else
    {
        return q.front();
    }
}

// 3) Using only Hash Map (or Vector for it)
// We keep all elements count inside our map.
// We then see the first character whose occurrence is 1 we return that index.
// Time : O(n) , Space : O(26) = O(1)
int firstUniqChar2(string s)
{
    vector<int> v(26, 0);
    for (int i = 0; i < s.size(); i++)
    {
        v[s[i] - 'a']++;
    }

    for (int i = 0; i < s.size(); i++)
    {
        if (v[s[i] - 'a'] == 1)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    string s = "loveleetcode";
    int i = firstUniqChar(s);
    cout << "First Unique Character Index : " << i << " which is Character : " << s[i] << endl;

    return 0;
}

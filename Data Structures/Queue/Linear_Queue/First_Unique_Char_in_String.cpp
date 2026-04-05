#include <iostream>
#include <queue>
#include <String.hpp>
using namespace std;

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

int main()
{
    string s = "loveleetcode";
    int i = firstUniqChar(s);
    cout<<"First Unique Character Index : " <<i<<" which is Character : "<<s[i]<<endl;

    return 0;
}
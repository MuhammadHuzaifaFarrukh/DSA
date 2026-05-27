#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

// 1) Brute Forcing and sorting characters may take up to O(n^2) time or even n^3 as there are characters , numbers and even captials also.

// 2) Optimized Approach : Use Priority Queue 
// Time : O(n) , Space : O(n)
string frequencySort(string s)
{
    priority_queue<pair<int, char>, vector<pair<int, char>>, less<pair<int, char>>> q;
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
        ans = ans + string(q.top().first, q.top().second);
        q.pop();
    }
    return ans;
}

int main()
{
    return 0;
}
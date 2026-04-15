#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <climits>
#include <unordered_map>
using namespace std;

// 1) Using Priority Queue and frequency count : O(N + Klogk) ~ O(N)
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

// We could have done this using unordered map  :
/*
string frequencySort(string s)
{
    // 1. Use a larger map or array to handle all ASCII characters safely
    unordered_map<char, int> freq;
    for (char c : s)
        freq[c]++;

    // 2. Max-heap (less is default, so we can simplify the declaration)
    priority_queue<pair<int, char>> q;

    // 3. ONLY push unique characters into the heap
    for (auto const &[ch, count] : freq)
    {
        q.push({count, ch});
    }

    string ans = "";
    // 4. Extract from heap and build the string
    while (!q.empty())
    {
        auto [count, ch] = q.top();
        q.pop();

        // Add the character 'count' times
        ans.append(count, ch);
    }

    return ans;
}
*/

int main()
{
    string s = "tree";
    cout << "Frequency Sort : " << frequencySort(s) << endl;
    return 0;
}

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
void printBinary(int n)
{
    if (n <= 0)
    {
        return ;
    }

    queue<string> q;
    q.push("1");

    for (int i = 0; i < n; i++)
    {
        string cur = q.front();

        q.pop();
        cout << cur << " ";

        string s1 = cur + "0";
        string s2 = cur + "1";

        q.push(s1);
        q.push(s2);
    }
}
int main()
{
    int n;
    cout << "Enter n : ";
    cin >> n;

    /*
    // Slower Approach , Works in O(n log n)
    // Taking each number and converting it into binary number
    for (int i = 1; i <= n; i++)
    {
        string t = "";
        int num = i;
        while (num != 0)
        {
            t = to_string(num % 2) + t;
            num = num / 2;
        }
        cout<<t<<" ";
    }
    */

    printBinary(n);
    cout << endl;
    return 0;
}

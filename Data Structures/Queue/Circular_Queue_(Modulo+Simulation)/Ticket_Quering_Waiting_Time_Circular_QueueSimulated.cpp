#include <queue>
#include <string>
#include <stack>
#include <iostream>

using namespace std;

int timetobuytickets(int tickets[], int k, int n)
{
    int time = 0;
    queue<int> q, temp;
    for (int i = 0; i < n; i++)
    {
        q.push(i);
    }

    while (!q.empty())
    {
        int x = q.front();
        q.pop();

        tickets[x]--;
        time++;

        if (x == k && tickets[x] == 0)
        {
            return time;
        }

        if (tickets[x] > 0)
        {
            q.push(x);
        }
    }

    return time;
}

int main()
{
    int n;
    cout << "Number of People buying Tickets : ";
    cin >> n;

    int *t = new int[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter tickets for person : " << i << " : ";
        cin >> t[i];
    }
    int k;
    cout << "Enter k : ";
    cin >> k;
    cout << "Time required for Person : " << k << " to buy tickets : " << timetobuytickets(t, k, n) << endl;

    delete[] t;
    return 0;
}
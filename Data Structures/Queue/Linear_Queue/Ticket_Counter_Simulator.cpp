#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of commands : ";
    cin >> n;
    cin.ignore();

    queue<string> q;
    string s, t;
    while (n--)
    {
        cin >> s;
        if (s == "ARRIVE")
        {
            getline(cin >> ws, t);
            q.push(t);
        }
        else if (s == "SERVE")
        {
            if (q.empty())
            {
                cout << "Queue is Empty " << endl;
            }
            else
            {
                cout << "Serving : " << q.front() << endl;
                q.pop();
            }
        }
        else if (s == "SKIP")
        {
            if (q.size() >= 2)
            {
                t = q.front();
                q.push(t);
                q.pop();
            }
        }
        else if (s == "COUNT")
        {
            cout << "Count : " << q.size() << endl;
        }
        else if (s == "DISPLAY")
        {
            if (q.empty())
            {
                cout << "Queue is Empty " << endl;
            }
            else
            {
                queue<string> temp = q;
                cout << "Queue : ";
                while (!temp.empty())
                {
                    cout << temp.front() << " ";
                    temp.pop();
                    if (!temp.empty())
                    {
                        cout << " -> ";
                    }
                }
                cout << endl;
            }
        }
    }
    return 0;
}
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Task
{
    string name;
    int burstTime;
};
int main()
{
    string n;
    int tim;

    cout << "Enter non-positive time and enter to exit input" << endl;
    queue<Task> q;
    vector<string> fin;
    while (1)
    {
        cin >> n >> tim;
        Task T;
        if (tim <= 0)
        {
            break;
        }
        T.name = n;
        T.burstTime = tim;
        q.push(T);
    }

    int unit = 1;
    while (!q.empty())
    {
        Task T = q.front();
        q.pop();
        T.burstTime--;
        cout << "Turn " << unit << " : " << T.name << " ran | Remaining : " << T.burstTime;
        if (T.burstTime == 0)
        {
            cout << " -> " << T.name << " Completed" << endl;
            fin.push_back(T.name);
        }
        else
        {
            cout << endl;
            q.push(T);
        }
        unit++;
    }

    cout << endl
         << "Completion Order : ";
    for (int i = 0; i < fin.size(); i++)
    {
        cout << fin[i];
        if (i < fin.size() - 1)
        {
            cout << " , ";
        }
    }
    cout << endl;

    return 0;
}
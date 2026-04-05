#include <iostream>
#include <queue>
using namespace std;
struct Process
{
    int id;
    int burst;
};
int main()
{
    queue<Process> q;
    int n, tq;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter time quantum: ";
    cin >> tq;
    for (int i = 1; i <= n; i++)
    {
        Process p;
        p.id = i;
        cout << "Enter burst time for process " << i << ": ";
        cin >> p.burst;
        q.push(p);
    }
    cout << "\nExecution Order:\n";
    while (!q.empty())
    {
        Process p = q.front();
        q.pop();
        if (p.burst > tq)
        {
            cout << "P" << p.id << " executes for " << tq << " units\n";
            p.burst -= tq;
            q.push(p);
        }
        else
        {
            cout << "P" << p.id << " executes for " << p.burst << " units and finishes\n";
        }
    }
    return 0;
}
#include <iostream>
#include <queue>
#include <string>
using namespace std;

// See how some systems follow priority queue.
// Even though , the systems may be more complexed , still we can see the basic working underneath.
// In Hospital Emergency system , the person who is critically ill gets higher priority than the ones who are normal patients.
// Here we overloaded the '<' operator , we could also use a functor as well which is even a better design.

struct Patient
{
    string name;
    int priority;
    bool operator<(const Patient &other) const
    {
        return priority < other.priority; // max heap by priority
    }
};
int main()
{
    priority_queue<Patient> pq;
    int choice;
    do
    {
        cout << "\n--- Hospital Emergency System ---\n";
        cout << "1. Add patient\n";
        cout << "2. Treat highest priority patient\n";
        cout << "3. Show next patient\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
        {
            Patient p;
            cout << "Enter patient name: ";
            getline(cin, p.name);
            cout << "Enter priority (higher = more urgent): ";
            cin >> p.priority;
            cin.ignore();
            pq.push(p);
            break;
        }
        case 2:
            if (pq.empty())
                cout << "No patients waiting.\n";
            else
            {
                cout << "Treating: " << pq.top().name << " (Priority " << pq.top().priority << ")\n";
                pq.pop();
            }
            break;
        case 3:
            if (pq.empty())
            {
                cout << "No patients waiting.\n";
            }
            else
            {
                cout << "Next patient: " << pq.top().name << " (Priority " << pq.top().priority << ")\n";
            }
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 4);
    return 0;
}
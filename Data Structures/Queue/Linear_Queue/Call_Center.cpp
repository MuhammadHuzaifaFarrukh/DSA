#include <iostream>
#include <queue>
#include <string>
using namespace std;
int main()
{
    queue<string> callers;
    int choice;
    string name;
    do
    {
        cout << "\n--- Call Center System ---\n";
        cout << "1. Add caller\n";
        cout << "2. Serve caller\n";
        cout << "3. Show waiting callers\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            cout << "Enter caller name: ";
            getline(cin, name);
            callers.push(name);
            cout << "Caller added.\n";
            break;
        case 2:
            if (callers.empty())
                cout << "No callers waiting.\n";
            else
            {
                cout << "Serving: " << callers.front() << "\n";
                callers.pop();
            }
            break;
        case 3:
        {
            if (callers.empty())
                cout << "No callers waiting.\n";
            else
            {
                queue<string> temp = callers;
                cout << "Waiting callers:\n";
                while (!temp.empty())
                {
                    cout << temp.front() << "\n";
                    temp.pop();
                }
            }
            break;
        }
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 4);
    return 0;
}
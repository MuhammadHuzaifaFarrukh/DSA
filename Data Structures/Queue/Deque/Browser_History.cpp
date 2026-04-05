#include <iostream>
#include <deque>
#include <string>
using namespace std;
int main()
{
    deque<string> backHistory, forwardHistory;
    string current = "home";
    int choice;
    do
    {
        cout << "\nCurrent page: " << current << "\n";
        cout << "--- Browser History System ---\n";
        cout << "1. Visit new page\n";
        cout << "2. Back\n";
        cout << "3. Forward\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
        {
            string page;
            cout << "Enter page name: ";
            getline(cin, page);
            backHistory.push_back(current);
            current = page;
            forwardHistory.clear();
            break;
        }
        case 2:
            if (backHistory.empty())
            {
                cout << "No page in back history.\n";
            }
            else
            {
                forwardHistory.push_back(current);
                current = backHistory.back();
                backHistory.pop_back();
            }
            break;
        case 3:
            if (forwardHistory.empty())
            {
                cout << "No page in forward history.\n";
            }
            else
            {
                backHistory.push_back(current);
                current = forwardHistory.back();
                forwardHistory.pop_back();
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
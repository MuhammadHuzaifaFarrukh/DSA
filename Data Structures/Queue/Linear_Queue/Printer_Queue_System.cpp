#include <iostream>
#include <queue>
#include <string>
using namespace std;
struct Job
{
    int id;
    int pages;
};
int main()
{
    queue<Job> q;
    int choice;
    int nextId = 1;
    do
    {
        cout << "\n--- Printer Queue System ---\n";
        cout << "1. Add print job\n";
        cout << "2. Process next job\n";
        cout << "3. Display pending jobs\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            Job j;
            j.id = nextId++;
            cout << "Enter number of pages: ";
            cin >> j.pages;
            q.push(j);
            cout << "Job added. ID = " << j.id << "\n";
            break;
        }
        case 2:
        {
            if (q.empty())
            {
                cout << "No jobs to process.\n";
            }
            else
            {
                Job j = q.front();
                q.pop();
                cout << "Processing Job ID " << j.id << " with " << j.pages << " pages\n";
            }
            break;
        }
        case 3:
        {
            if (q.empty())
            {
                cout << "No pending jobs.\n";
            }
            else
            {
                queue<Job> temp = q;
                cout << "Pending jobs:\n";
                while (!temp.empty())
                {
                    Job j = temp.front();
                    temp.pop();
                    cout << "Job ID: " << j.id << ", Pages: " << j.pages
                         << "\n";
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
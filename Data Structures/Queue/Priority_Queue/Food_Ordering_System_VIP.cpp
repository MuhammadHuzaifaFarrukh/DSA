#include <iostream>
#include <queue>
#include <string>
using namespace std;

// See how some systems follow priority queue.
// Even though , the systems may be more complexed , still we can see the basic working underneath.
// In food delivery system , the person who is VIP gets higher priority than the ones who are just regular customers.
// Here we overloaded the '<' operator , we could also use a functor as well which is even a better design.

struct Order
{
    string customer;
    int priority; // higher means more urgent/VIP
    bool operator<(const Order &other) const
    {
        return priority < other.priority;
    }
};
int main()
{
    priority_queue<Order> pq;
    int choice;
    do
    {
        "\n";
        cout << "\n--- Food Delivery System ---\n";
        cout << "1. Add order\n";
        cout << "2. Dispatch next order\n";
        cout << "3. Show next order\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
        {
            Order o;
            cout << "Enter customer name: ";
            getline(cin, o.customer);
            cout << "Enter priority (VIP/high value first): ";
            cin >> o.priority;
            cin.ignore();
            pq.push(o);
            break;
        }
        case 2:
            if (pq.empty())
                cout << "No orders pending.\n";
            else
            {
                cout << "Dispatching order for " << pq.top().customer << endl;
                pq.pop();
            }
            break;
        case 3:
            if (pq.empty())
            {
                cout << "No orders pending.\n";
            }
            else
            {
                cout << "Next order: " << pq.top().customer << "\n";
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
#include <iostream>
using namespace std;
class CircularQueue
{
    int *arr, front, rear, size, count;

public:
    CircularQueue(int n)
    {
        size = n;
        arr = new int[size];
        front = 0;
        rear = -1;
        count = 0;
        for (int i = 0; i < size; i++)
            arr[i] = i + 1; // seat numbers
    }
    bool isFull() { return count == size; }
    bool isEmpty() { return count == 0; }
    int bookSeat()
    {
        if (isEmpty())
            return -1;
        int seat = arr[front];
        front = (front + 1) % size;
        count--;
        return seat;
    }
    void initialize()
    {
        front = 0;
        rear = size - 1;
        count = size;
    }
    void cancelSeat(int seatNo)
    {
        if (count == size)
        {
            cout << "All seats already available.\n";
            return;
        }
        rear = (rear + 1) % size;
        arr[rear] = seatNo;
        count++;
        cout << "Seat " << seatNo << " added back to availability queue.\n";
    }
    void displayAvailable()
    {
        if (isEmpty())
        {
            cout << "No seats available.\n";
            return;
        }
        cout << "Available seats: ";
        for (int i = 0; i < count; i++)
        {
            cout << arr[(front + i) % size] << " ";
        }
        cout << "\n";
    }
    ~CircularQueue() { delete[] arr; }
};

int main()
{
    int n;
    cout << "Enter total number of seats: ";
    cin >> n;
    CircularQueue cq(n);
    cq.initialize();
    int choice;
    do
    {
        cout << "\n--- Ticket Booking System ---\n";
        cout << "1. Book ticket\n";
        cout << "2. Cancel ticket\n";
        cout << "3. Show available seats\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            int seat = cq.bookSeat();
            if (seat == -1)
                cout << "No seats available.\n";
            else
                cout << "Booked seat: " << seat << "\n";
            break;
        }
        case 2:
        {
            int seatNo;
            cout << "Enter seat number to cancel: ";
            cin >> seatNo;
            cq.cancelSeat(seatNo);
            break;
        }
        case 3:
            cq.displayAvailable();
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
#include <iostream>
#include <queue>
using namespace std;
class MyCircularQueue
{
    int *arr;
    int FRONT;
    int REAR;
    int count;
    int CAP;

    int *allocate(int capacity)
    {
        try
        {
            return new int[capacity];
        }
        catch (const std::bad_alloc &)
        {
            throw std::runtime_error("Queue: Memory allocation failed.");
        }
    }

    void reserve(int new_cap)
    {
        int *temp = allocate(new_cap);
        // When resizing a circular queue, we must "unwrap" it into the new array
        for (int i = 0; i < count; i++)
        {
            temp[i] = std::move(arr[(FRONT + i) % CAP]);
        }

        delete[] arr;
        arr = temp;
        FRONT = 0;
        REAR = count - 1;
        CAP = new_cap;
    }

public:
    MyCircularQueue(int k)
    {
        CAP = (k > 0) ? k : 4;
        arr = allocate(CAP);
        FRONT = 0;
        REAR = -1;
        count = 0;
    }

    bool enQueue(int value)
    {
        if (isFull())
        {
            return 0;
            // reserve(CAP * 2);
        }
        // Use modulo to wrap the REAR index to the "behind space"
        REAR = (REAR + 1) % CAP;
        arr[REAR] = value;
        count++;
        return 1;
    }

    bool deQueue()
    {
        if (isEmpty())
            return 0;
        // Simply move FRONT forward using modulo
        FRONT = (FRONT + 1) % CAP;
        count--;
        return 1;
    }

    int Front()
    {
        if (isEmpty())
            return -1;
        return arr[FRONT];
    }

    int Rear()
    {
        if (isEmpty())
            return -1;
        return arr[REAR];
    }

    bool isEmpty()
    {
        return count == 0;
    }

    bool isFull()
    {
        return count == CAP;
    }

    int size() const
    {
        return count;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */

int main()
{
    return 0;
}
#pragma once
#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>
using namespace std;

// To understand a Queue, it is best to think of it as a FIFO (First-In, First-Out) behavior.
// While a Stack is like a stack of plates, a Queue is like a line of people waiting for coffee.
// The first person to join the line is the first one served.

// In C++ , the header queue contains std::queue and std::priority_queue both.
// In C++, the built-in std::queue is an adaptor that usually sits on top of a std::deque.
// It restricts access so you can only add to the back and remove from the front.
// Using a Queue ADT instead of a Vector ensures Safety and Intent, preventing accidental
// middle-insertions that would break the logic of your process.
// std::queue works on deque that allocates chunks of memory each time an element is added.
// So std::queue can be made to work on deque by default and even std::list also


// Elements are added at REAR and removed from FRONT. Once REAR hits CAP, it resizes.
// However this wastes a lot of space in this way if the space was allocated for many elements.

template <typename T>
class Queue
{
private:
    T *arr;
    int FRONT; 
    int REAR;  
    int count; 
    int CAP;

    T *allocate(int capacity)
    {
        try
        {
            return new T[capacity];
        }
        catch (const std::bad_alloc &)
        {
            throw std::runtime_error("Queue: Memory allocation failed.");
        }
    }

    void reserve(int new_cap)
    {
        if (new_cap <= CAP)
            return;

        T *temp = allocate(new_cap);

        // Linear Copy: We only copy the active elements from FRONT to REAR
        for (int i = 0; i < count; i++)
        {
            temp[i] = std::move(arr[FRONT + i]);
        }

        delete[] arr;
        arr = temp;
        FRONT = 0;
        REAR = count - 1; 
        CAP = new_cap;
    }

public:
    Queue(int initial_cap = 1)
    {
        CAP = (initial_cap > 0) ? initial_cap : 1;
        arr = allocate(CAP);
        FRONT = 0;
        REAR = -1;
        count = 0;
    }

    Queue(std::initializer_list<T> list)
    {
        CAP = (list.size() > 0) ? (int)list.size() : 1;
        arr = allocate(CAP);
        FRONT = 0;
        REAR = -1;
        count = 0;
        for (const T &item : list)
            push(item);
    }

    ~Queue()
    {
        delete[] arr;
    }

    // Rule of 5 - Deep Copy
    Queue(const Queue &other)
    {
        CAP = other.CAP;
        count = other.count;
        FRONT = 0;
        REAR = count - 1;
        arr = allocate(CAP);
        for (int i = 0; i < count; i++)
        {
            arr[i] = other.arr[other.FRONT + i];
        }
    }

    Queue &operator=(const Queue &other)
    {
        if (this != &other)
        {
            T *temp = allocate(other.CAP);
            for (int i = 0; i < other.count; i++)
            {
                temp[i] = other.arr[other.FRONT + i];
            }
            delete[] arr;
            arr = temp;
            CAP = other.CAP;
            count = other.count;
            FRONT = 0;
            REAR = count - 1;
        }
        return *this;
    }

    // Rule of 5 - Move Semantics
    Queue(Queue &&other) noexcept
    {
        arr = other.arr;
        CAP = other.CAP;
        count = other.count;
        FRONT = other.FRONT;
        REAR = other.REAR;

        other.arr = nullptr;
        other.count = 0;
        other.CAP = 0;
    }

    Queue &operator=(Queue &&other) noexcept
    {
        if (this != &other)
        {
            delete[] arr;
            arr = other.arr;
            CAP = other.CAP;
            count = other.count;
            FRONT = other.FRONT;
            REAR = other.REAR;

            other.arr = nullptr;
            other.count = 0;
            other.CAP = 0;
        }
        return *this;
    }

    bool empty() const { return count == 0; }

    bool full() const { return REAR == CAP - 1; }

    int size() const { return count; }

    void pop()
    {
        if (empty())
        {
            throw std::out_of_range("Queue Underflow");
        }
        FRONT++; // Simply move the front pointer
        count--; // Decrement active count
        // Shrinking logic removed
    }

    void push(T val)
    {
        if (full())
            reserve(CAP * 2); // Dynamic expansion continues
        REAR++;
        arr[REAR] = val;
        count++;
    }

    T &front()
    {
        if (empty())
            throw std::out_of_range("Queue is empty");
        return arr[FRONT];
    }

    T &back()
    {
        if (empty())
            throw std::out_of_range("Queue is empty");
        return arr[REAR];
    }

    void swap(Queue &other) noexcept
    {
        std::swap(arr, other.arr);
        std::swap(FRONT, other.FRONT);
        std::swap(REAR, other.REAR);
        std::swap(count, other.count);
        std::swap(CAP, other.CAP);
    }

    bool operator==(const Queue &other) const
    {
        if (count != other.count)
            return false;
        for (int i = 0; i < count; i++)
        {
            if (arr[FRONT + i] != other.arr[other.FRONT + i])
                return false;
        }
        return true;
    }

    bool operator!=(const Queue &other) const { return !(*this == other); }

    void display() const
    {
        if (empty())
        {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "Front -> ";
        for (int i = 0; i < count; i++)
        {
            cout << "[" << arr[FRONT + i] << "] ";
        }
        cout << "<- Rear" << endl;
    }

    friend std::ostream &operator<<(std::ostream &out, const Queue<T> &q)
    {
        for (int i = 0; i < q.count; i++)
        {
            out << q.arr[q.FRONT + i] << " ";
        }
        return out;
    }
};
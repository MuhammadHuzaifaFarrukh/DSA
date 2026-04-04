#pragma once
#include <iostream>
#include <stdexcept>
#include <initializer_list>

/*
Circular Queue is one that saves space by adding the elements on the elements that were present there before.

// Meaning that if the elements can be pushed to the places of those elements that were popped.
// This saves us huge space and even the time to allocate the new space for more elements.
// There is no circular queue in cpp by default but we have made it here and making it to work like deque or list.
*/
template <typename T>
class Circular_Queue
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
        T *temp = allocate(new_cap);
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
    CircularQueue(int initial_cap = 4)
    {
        CAP = (initial_cap > 0) ? initial_cap : 4;
        arr = allocate(CAP);
        FRONT = 0;
        REAR = -1;
        count = 0;
    }

    CircularQueue(std::initializer_list<T> list) : CircularQueue((int)list.size())
    {
        for (const auto &item : list)
            push(item);
    }

    ~CircularQueue() { delete[] arr; }

    // Rule of 5: Copy Constructor
    CircularQueue(const CircularQueue &other)
    {
        CAP = other.CAP;
        count = other.count;
        FRONT = 0;
        REAR = count - 1;
        arr = allocate(CAP);
        for (int i = 0; i < count; i++)
        {
            arr[i] = other.arr[(other.FRONT + i) % other.CAP];
        }
    }

    // Rule of 5: Move Constructor
    CircularQueue(CircularQueue &&other) noexcept
        : arr(other.arr), FRONT(other.FRONT), REAR(other.REAR), count(other.count), CAP(other.CAP)
    {
        other.arr = nullptr;
        other.count = 0;
    }

    bool empty() const { return count == 0; }   // Can also do Rear = -1 , if we have resetted Front = 0 and Rear = - 1 in pop() function
    bool full() const { return count == CAP; }  // If we didn't have count , then we would use : (Rear + 1) % n == Front
    int size() const { return count; }          // For size , the count variable is convenient.

    void push(const T &val)
    {
        if (full())
        {
            reserve(CAP * 2);
        }
        // Use modulo to wrap the REAR index to the "behind space"
        REAR = (REAR + 1) % CAP;
        arr[REAR] = val;
        count++;
    }

    void pop()
    {
        if (empty())
            throw std::out_of_range("Queue Underflow");
        // You can also put Front = 0 and Rear = -1 when they both meet and we pop and then we can easily check our isEmpty() function by Rear = -1 instead of checking count 
        

        // Simply move FRONT forward using modulo
        FRONT = (FRONT + 1) % CAP;
        count--;
    }

    T &front()
    {
        if (empty())
            throw std::out_of_range("Queue is empty");
        return arr[FRONT];
    }

    void display() const
    {
        if (empty())
        {
            std::cout << "Queue is empty." << std::endl;
            return;
        }
        std::cout << "Front -> ";
        for (int i = 0; i < count; i++)
        {
            std::cout << "[" << arr[(FRONT + i) % CAP] << "] ";
        }
        std::cout << "<- Rear" << std::endl;
    }
};

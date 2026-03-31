#pragma once
#include <iostream>
#include <stdexcept>
#include <initializer_list>

// This version of queue is implemented using linked list.
// We could also have used the independent classes instead of nested class here.
// This also solves the array wastage problem as the nodes are inserted and deleted at the time of insertion and deletion instantly.
template <typename T>
class Queue
{
private:
    // Internal node structure
    struct Node
    {
        T data;
        Node *next;
        Node(const T &val) : data(val), next(nullptr) {}
        Node(T &&val) : data(std::move(val)), next(nullptr) {}
    };

    Node *FRONT; // Points to the head of the list (removal point)
    Node *REAR;  // Points to the tail of the list (insertion point)
    int count;   // Number of active elements

public:
    // 1. Standard Constructor
    Queue() : FRONT(nullptr), REAR(nullptr), count(0) {}

    // 2. Initializer List Constructor
    Queue(std::initializer_list<T> list) : FRONT(nullptr), REAR(nullptr), count(0)
    {
        for (const T &item : list)
        {
            push(item);
        }
    }

    // 3. Destructor
    ~Queue()
    {
        while (!empty())
        {
            pop();
        }
    }

    // 4. Copy Constructor (Deep Copy)
    Queue(const Queue &other) : FRONT(nullptr), REAR(nullptr), count(0)
    {
        Node *temp = other.FRONT;
        while (temp)
        {
            push(temp->data);
            temp = temp->next;
        }
    }

    // 5. Copy Assignment Operator
    Queue &operator=(const Queue &other)
    {
        if (this != &other)
        {
            // Clear current content
            while (!empty())
                pop();

            Node *temp = other.FRONT;
            while (temp)
            {
                push(temp->data);
                temp = temp->next;
            }
        }
        return *this;
    }

    // 6. Move Constructor
    Queue(Queue &&other) noexcept : FRONT(other.FRONT), REAR(other.REAR), count(other.count)
    {
        other.FRONT = nullptr;
        other.REAR = nullptr;
        other.count = 0;
    }

    // 7. Move Assignment Operator
    Queue &operator=(Queue &&other) noexcept
    {
        if (this != &other)
        {
            while (!empty())
                pop();

            FRONT = other.FRONT;
            REAR = other.REAR;
            count = other.count;

            other.FRONT = nullptr;
            other.REAR = nullptr;
            other.count = 0;
        }
        return *this;
    }

    // --- Core Functionality ---

    bool empty() const { return count == 0; }

    int size() const { return count; }

    void push(const T &val)
    {
        Node *newNode = new Node(val);
        if (empty())
        {
            FRONT = REAR = newNode;
        }
        else
        {
            REAR->next = newNode;
            REAR = newNode;
        }
        count++;
    }

    void pop()
    {
        if (empty())
        {
            throw std::out_of_range("Queue Underflow");
        }
        Node *temp = FRONT;
        FRONT = FRONT->next;
        delete temp;
        count--;

        if (FRONT == nullptr)
        {
            REAR = nullptr;
        }
    }

    T &front()
    {
        if (empty())
            throw std::out_of_range("Queue is empty");
        return FRONT->data;
    }

    T &back()
    {
        if (empty())
            throw std::out_of_range("Queue is empty");
        return REAR->data;
    }

    void display() const
    {
        if (empty())
        {
            std::cout << "Queue is empty." << std::endl;
            return;
        }
        std::cout << "Front -> ";
        Node *temp = FRONT;
        while (temp)
        {
            std::cout << "[" << temp->data << "] ";
            temp = temp->next;
        }
        std::cout << "<- Rear" << std::endl;
    }

    // --- Relational Operators ---

    bool operator==(const Queue &other) const
    {
        if (count != other.count)
            return false;
        Node *t1 = FRONT;
        Node *t2 = other.FRONT;
        while (t1)
        {
            if (t1->data != t2->data)
                return false;
            t1 = t1->next;
            t2 = t2->next;
        }
        return true;
    }

    bool operator!=(const Queue &other) const { return !(*this == other); }

    friend std::ostream &operator<<(std::ostream &out, const Queue<T> &q)
    {
        Node *temp = q.FRONT;
        while (temp)
        {
            out << temp->data << " ";
            temp = temp->next;
        }
        return out;
    }
};
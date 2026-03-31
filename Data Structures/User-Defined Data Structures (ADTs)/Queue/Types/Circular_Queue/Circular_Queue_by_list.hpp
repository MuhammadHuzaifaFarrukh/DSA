#pragma once
#include <iostream>
#include <stdexcept>

/*
// In a Linked List, "Circular" means the REAR->next pointer points back to FRONT instead of nullptr. 
// This structure is often used for buffering data streams where you want to cycle through a fixed set of nodes.
*/
template <typename T>
class Circular_Queue
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(const T &val) : data(val), next(nullptr) {}
    };

    Node *REAR; // In a circular list, we only need REAR because REAR->next is FRONT
    int count;

public:
    CircularListQueue() : REAR(nullptr), count(0) {}

    ~CircularListQueue()
    {
        while (count > 0)
            pop();
    }

    bool empty() const { return count == 0; }

    void push(const T &val)
    {
        Node *newNode = new Node(val);
        if (empty())
        {
            newNode->next = newNode; // Points to itself
            REAR = newNode;
        }
        else
        {
            newNode->next = REAR->next; // New node points to FRONT
            REAR->next = newNode;       // Old REAR points to new node
            REAR = newNode;             // Update REAR to the new node
        }
        count++;
    }

    void pop()
    {
        if (empty())
            throw std::out_of_range("Queue Underflow");

        Node *frontNode = REAR->next;
        if (count == 1)
        {
            REAR = nullptr;
        }
        else
        {
            REAR->next = frontNode->next; // REAR points to the new FRONT
        }
        delete frontNode;
        count--;
    }

    T &front()
    {
        if (empty())
            throw std::out_of_range("Queue is empty");
        return REAR->next->data;
    }

    void display() const
    {
        if (empty())
            return;
        Node *temp = REAR->next;
        std::cout << "Front -> ";
        for (int i = 0; i < count; i++)
        {
            std::cout << "[" << temp->data << "] ";
            temp = temp->next;
        }
        std::cout << "<- Rear" << std::endl;
    }
};
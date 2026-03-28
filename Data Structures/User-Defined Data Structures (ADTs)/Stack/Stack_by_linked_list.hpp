#pragma once
#include <iostream>
#include <stdexcept>
#include <initializer_list>

// In this version, the Stack is a chain of Nodes.
// Previously , we implemented Stack using array pointer 
// Here we will do it in Linked List way.
// Each Node contains the data and a pointer to the Node below it.
// In this version , we don't need to use the resizing function anymore cause we can add any node and assign it value.
// Here we did using nested Nodes class.
// It could also have been done by making 2 separate independent classes.

template <typename T>
class Stack
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(const T &val, Node *ptr = nullptr) : data(val), next(ptr) {}
    };

    Node *topNode; // Points to the LIFO "Top"
    int count;     // Tracks the number of elements

public:
    // Standard Constructor
    Stack() : topNode(nullptr), count(0) {}

    // Initializer List Constructor
    // Allows: Stack<int> s = {1, 2, 3};
    Stack(std::initializer_list<T> list) : topNode(nullptr), count(0)
    {
        for (const T &item : list)
        {
            push(item);
        }
    }

    // 1. Copy Constructor (Deep Copy)
    Stack(const Stack &other) : topNode(nullptr), count(0)
    {
        if (other.topNode == nullptr)
            return;

        // To keep the order the same, we have to copy recursively
        // or use a temporary buffer. A simple way is to copy
        // while traversing the 'other' stack.
        try
        {
            // Reversing the logic to maintain order
            Node *otherCurrent = other.topNode;
            T *tempArr = new T[other.count];
            for (int i = other.count - 1; i >= 0; i--)
            {
                tempArr[i] = otherCurrent->data;
                otherCurrent = otherCurrent->next;
            }
            for (int i = 0; i < other.count; i++)
            {
                push(tempArr[i]);
            }
            delete[] tempArr;
        }
        catch (...)
        {
            throw std::runtime_error("Stack: Copy failed.");
        }
    }

    // 2. Destructor (Clean up all heap-allocated nodes)
    ~Stack()
    {
        while (!empty())
        {
            pop();
        }
    }

    // --- Core Operations ---

    void push(T val)
    {
        // Create a new node where 'next' points to the old top
        Node *newNode = new Node(val, topNode);
        topNode = newNode;
        count++;
    }

    void pop()
    {
        if (empty())
        {
            throw std::out_of_range("Stack Underflow");
        }
        Node *temp = topNode;
        topNode = topNode->next; // Move top to the next element down
        delete temp;
        count--;
    }

    T &top()
    {
        if (empty())
            throw std::out_of_range("Stack is empty");
        return topNode->data;
    }

    const T &top() const
    {
        if (empty())
            throw std::out_of_range("Stack is empty");
        return topNode->data;
    }

    // --- Utilities ---

    bool empty() const { return topNode == nullptr; }

    int size() const { return count; }

    void display() const
    {
        Node *current = topNode;
        while (current != nullptr)
        {
            std::cout << "| " << current->data << " |" << std::endl;
            current = current->next;
        }
        std::cout << " -----" << std::endl;
    }

    // Global friend operator for output (Bottom to Top)
    friend std::ostream &operator<<(std::ostream &out, const Stack<T> &s)
    {
        // Helper to print in reverse (bottom to top)
        auto printRecursive = [&](auto self, Node *n) -> void
        {
            if (n == nullptr)
                return;
            self(self, n->next);
            out << n->data << " ";
        };
        printRecursive(printRecursive, s.topNode);
        return out;
    }
};
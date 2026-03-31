#pragma once
#include <iostream>
#include <stdexcept>
#include <initializer_list>

// This version uses pointers (next and prev) for every node (Doubly Linked List). 
// It is naturally dynamic and never requires a reserve() or shrink_to_fit() operation in the traditional sense,
template <typename T>
class Deque
{
private:
    struct Node
    {
        T data;
        Node *next, *prev;
        Node(const T &val) : data(val), next(nullptr), prev(nullptr) {}
    };

    Node *FRONT, *REAR;
    int count;

public:
    class Iterator
    {
    private:
        Node *curr;

    public:
        Iterator(Node *n) : curr(n) {}
        T &operator*() { return curr->data; }
        Iterator &operator++()
        {
            if (curr)
                curr = curr->next;
            return *this;
        }
        bool operator==(const Iterator &other) const { return curr == other.curr; }
        bool operator!=(const Iterator &other) const { return curr != other.curr; }
    };

    Iterator begin() { return Iterator(FRONT); }
    Iterator end() { return Iterator(nullptr); }

    // --- Constructors & Rule of 5 ---
    Deque() : FRONT(nullptr), REAR(nullptr), count(0) {}

    Deque(std::initializer_list<T> list) : Deque()
    {
        for (const auto &item : list)
            push_back(item);
    }

    ~Deque() { clear(); }

    Deque(const Deque &other) : Deque()
    {
        Node *temp = other.FRONT;
        while (temp)
        {
            push_back(temp->data);
            temp = temp->next;
        }
    }

    Deque(Deque &&other) noexcept : FRONT(other.FRONT), REAR(other.REAR), count(other.count)
    {
        other.FRONT = nullptr;
        other.REAR = nullptr;
        other.count = 0;
    }

    Deque &operator=(const Deque &other)
    {
        if (this != &other)
        {
            clear();
            Node *temp = other.FRONT;
            while (temp)
            {
                push_back(temp->data);
                temp = temp->next;
            }
        }
        return *this;
    }

    // --- Modifiers ---
    void push_front(const T &val)
    {
        Node *newNode = new Node(val);
        if (empty())
        {
            FRONT = REAR = newNode;
        }
        else
        {
            newNode->next = FRONT;
            FRONT->prev = newNode;
            FRONT = newNode;
        }
        count++;
    }

    void push_back(const T &val)
    {
        Node *newNode = new Node(val);
        if (empty())
        {
            FRONT = REAR = newNode;
        }
        else
        {
            REAR->next = newNode;
            newNode->prev = REAR;
            REAR = newNode;
        }
        count++;
    }

    void pop_front()
    {
        if (empty())
            return;
        Node *temp = FRONT;
        FRONT = FRONT->next;
        if (FRONT)
            FRONT->prev = nullptr;
        else
            REAR = nullptr;
        delete temp;
        count--;
    }

    void pop_back()
    {
        if (empty())
            return;
        Node *temp = REAR;
        REAR = REAR->prev;
        if (REAR)
            REAR->next = nullptr;
        else
            FRONT = nullptr;
        delete temp;
        count--;
    }

    // --- Insert Variants ---
    void insert(int pos, const T &val)
    {
        if (pos == 0)
        {
            push_front(val);
            return;
        }
        if (pos == count)
        {
            push_back(val);
            return;
        }
        Node *curr = FRONT;
        for (int i = 0; i < pos; i++)
            curr = curr->next;
        Node *newNode = new Node(val);
        newNode->next = curr;
        newNode->prev = curr->prev;
        curr->prev->next = newNode;
        curr->prev = newNode;
        count++;
    }

    void insert(int pos, int n, const T &val)
    {
        for (int i = 0; i < n; i++)
            insert(pos + i, val);
    }

    void insert(int pos, Iterator first, Iterator last)
    {
        int offset = 0;
        while (first != last)
        {
            insert(pos + offset, *first);
            ++first;
            ++offset;
        }
    }

    // --- Erase Variants ---
    void erase(int pos)
    {
        if (pos == 0)
        {
            pop_front();
            return;
        }
        if (pos == count - 1)
        {
            pop_back();
            return;
        }
        Node *curr = FRONT;
        for (int i = 0; i < pos; i++)
            curr = curr->next;
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        count--;
    }

    void erase(int first_pos, int last_pos)
    {
        int num = last_pos - first_pos;
        for (int i = 0; i < num; i++)
            erase(first_pos);
    }

    // --- Capacity & Utilities ---
    void clear()
    {
        while (!empty())
            pop_front();
    }
    bool empty() const { return count == 0; }
    bool full() const { return false; }
    int size() const { return count; }
    void display() const
    {
        Node *temp = FRONT;
        while (temp)
        {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    bool operator==(const Deque &other) const
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
};
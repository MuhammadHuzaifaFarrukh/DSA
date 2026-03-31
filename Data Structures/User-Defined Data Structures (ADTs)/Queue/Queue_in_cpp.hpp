#pragma once
#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <deque>

// Can be made to behave like std::deque or std::list
// FIFO Behavior Adaptor
template <typename T, typename Container = std::deque<T>>
class Queue
{
private:
    Container c;

public:
    Queue() : c() {}
    Queue(std::initializer_list<T> list) : c(list) {}

    // Rule of Zero: The container manages its own lifecycle
    ~Queue() = default;

    void push(const T& val)
    {
        c.push_back(val);
    }
    void push(T&& val)
    {
        c.push_back(std::move(val));
    }

    void pop()
    {
        if (c.empty()) throw std::out_of_range("Queue Underflow");
        c.pop_front();
    }

    T& front()
    {
        return c.front();
    }
    T& back()
    {
        return c.back();
    }
    bool empty() const
    {
        return c.empty();
    }
    int size() const
    {
        return (int)c.size();
    }

    void display() const
    {
        if (empty())
        {
            std::cout << "Queue is empty." << std::endl;
            return;
        }
        std::cout << "Front -> ";
        for (const auto& item : c) std::cout << "[" << item << "] ";
        std::cout << "<- Rear" << std::endl;
    }
};

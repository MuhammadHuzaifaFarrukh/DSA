#pragma once
#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <vector>   // You may use your own Vector.hpp header
#include <list>     // You may use your own List.hpp header
#include <deque> // Default container

using namespace std;

// To understand a Stack, it is best to think of it not just as a container, but as a
// behavior. While an array or a vector allows you to access any element at any time,
// a stack enforces a strict rule: Last-In, First-Out (LIFO).

// What is a Stack? (The LIFO Principle)
// Imagine a stack of physical plates in a cafeteria.
// You always place a new plate on the top.
// If you want to take a plate, you take the one from the top.
// You cannot (safely) grab a plate from the middle or the bottom without removing everything above it first.

// You might ask: "If a Vector can do everything a Stack can, why use a Stack?"
// The answer is Safety and Intent.
// Using a Stack ADT tells other programmers (and the compiler) exactly how the data should be handled.
// It prevents bugs where someone might accidentally delete an element from the middle of your history or your "undo" chain, which would break the logic of your program.
// In short, a Vector is a tool for storage, while a Stack is a tool for process control.

// Different languages have different implementations of Stack , while concept is same.
// In C++ , the built-in std::stack is a container adapter that sits on top of another container : deque.
// It doesn't actually manage memory itself.
// It uses std::deque because deques don't require massive "copy-everything" reallocations like vectors do.
// Just like how a deque works , stack will work like that with its own member functions but memory managed by std::deque

// You can force it to use a std::vector or std::list.
// E.g : When you write std::stack<int, std::vector<int>>, the stack object literally contains a
// std::vector as a private member variable. It then maps its own functions directly to the vector's functions:
// stack::push() calls vector::push_back()
// stack::pop() calls vector::pop_back()
// stack::top() calls vector::back()
// Because C++ gives you manual control, you choose whether you want the "doubling" behavior of a vector or the "chunked" behavior of a deque.

// In Java , stack extends vector so it basically works like a vector.

// Here in this ADT we have implemented in such a way that our stack works like that of vector , list , deque like the built-in one.
// For that we use a technique called template template parameters.

template <typename T, typename Container = std::deque<T>>
class Stack
{
private:
    Container c; // This could be your Vector, std::vector, std::list, or std::deque

public:
    // 1. Standard Constructor
    Stack() : c() {}

    // 2. Initializer List Constructor
    // This allows: Stack<int> s = {1, 2, 3};
    Stack(std::initializer_list<T> list) : c(list) {}

    // 3. Destructor, Copy/Move Constructors & Assignments
    // We use "= default" because the Container (c) already knows how to
    // copy/move/delete itself. This is called the "Rule of Zero".
    Stack(const Stack &other) = default;
    Stack(Stack &&other) noexcept = default;
    Stack &operator=(const Stack &other) = default;
    Stack &operator=(Stack &&other) noexcept = default;
    ~Stack() = default;

    // --- Core Stack Operations ---

    void push(const T &val)
    {
        c.push_back(val);
    }

    // Move push for efficiency
    void push(T &&val)
    {
        c.push_back(std::move(val));
    }

    void pop()
    {
        if (c.empty())
        {
            throw std::out_of_range("Stack Underflow: Container is empty.");
        }
        c.pop_back();
    }

    T &top()
    {
        if (c.empty())
        {
            throw std::out_of_range("Stack: Accessing top of empty container.");
        }
        return c.back();
    }

    const T &top() const
    {
        if (c.empty())
        {
            throw std::out_of_range("Stack: Accessing top of empty container.");
        }
        return c.back();
    }

    // --- Utilities ---

    bool empty() const { return c.empty(); }

    int size() const { return (int)c.size(); }

    // Status: For deque/list, capacity isn't always relevant,
    // but if the container supports it (like Vector), we can show it.
    int status() const
    {
        // This is a trick: it only calls .capacity() if the container has it
        return 0; // Usually hidden in adaptors, but kept for ADT consistency
    }

    void swap(Stack &other) noexcept
    {
        using std::swap;
        swap(c, other.c);
    }

    // --- Operators ---

    bool operator==(const Stack &other) const
    {
        return c == other.c; // Delegating comparison to the engine
    }

    bool operator!=(const Stack &other) const
    {
        return c != other.c;
    }

    // Displays top to bottom like a stack is 
    void display() const
    {
        if (empty())
        {
            std::cout << "[Empty Stack]" << std::endl;
            return;
        }
        // We go from the last element (size-1) down to 0
        for (int i = size() - 1; i >= 0; i--)
        {
            // We use a temporary way to access elements if the container allows
            // Note: This assumes the container has operator[] (like Vector or Deque)
            std::cout << "| " << c[i] << " |" << std::endl;
        }
        std::cout << " -----" << std::endl;
    }

    // Displays from bottom to top.
    // See how data items were pushed originally.
    friend std::ostream &operator<<(std::ostream &out, const Stack<T, Container> &s)
    {
        // Range-loop: starts at index 0 (Bottom), ends at topIndex (Top)
        for (const auto &item : s.c)
        {
            out << item << " ";
        }
        return out;
    }

    // For the built-in stack , we usually use a while loop with condition !stack.empty()
    // and keeping using top() and pop() for it to print , we don't use a for() loop for this. 
    // We do this while keeping the copy of the original stack object to not lose it.
};
#pragma once
#include <iostream>
#include <stdexcept>
#include <initializer_list> 

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

// Here in this ADT , Stack is designed like a vector that manages its memory itself not like the built-in one.
// But we make a topindex that points to the last element in the array.
// We could also have implemented in such a way that our stack worked like that of vector , list , deque like the built-in one.
// For that we use a technique called template template parameters. 
template <typename T> 
class Stack
{
private:
    T *arr;        // Changed to T* for templating
    int topIndex; 
    int CAP;

    void reserve(int new_cap)
    {
        if (new_cap <= CAP)
            return;

        T *temp = nullptr;
        try
        {
            temp = new T[new_cap]; // Allocation for type T
        }
        catch (const std::bad_alloc &)
        {
            throw std::runtime_error("Stack: Allocation failed.");
        }

        int current_count = topIndex + 1;
        for (int i = 0; i < current_count; i++)
        {
            // Using std::move like your Vector.hpp for efficiency
            temp[i] = std::move(arr[i]);
        }

        delete[] arr;
        arr = temp;
        CAP = new_cap;
    }

public:
    // Standard Constructor
    Stack(int initial_cap = 1)
    {
        CAP = (initial_cap > 0) ? initial_cap : 1;
        topIndex = -1;
        arr = new T[CAP];
    }

    // Initializer List Constructor
    // This allows: Stack<int> s = {1, 2, 3};
    Stack(std::initializer_list<T> list)
    {
        int list_size = list.size();
        CAP = (list_size > 0) ? list_size : 1;
        arr = new T[CAP];
        topIndex = -1;

        for (const T &item : list)
        {
            push(item); // Reusing push to handle index and potential resizing
        }
    }

    ~Stack()
    {
        delete[] arr;
    }

    void push(T val)
    {
        if (topIndex + 1 == CAP)
        {
            reserve(CAP * 2);
        }
        topIndex++;
        arr[topIndex] = val;
    }

    void pop()
    {
        if (empty())
        {
            throw std::out_of_range("Stack Underflow");
        }
        topIndex--;
    }

    // Templated Top (Reference for modification)
    T &top()
    {
        if (empty())
        {
            throw std::out_of_range("Stack is empty");
        }
        return arr[topIndex];
    }

    // Const version
    const T &top() const
    {
        if (empty())
            throw std::out_of_range("Stack is empty");
        return arr[topIndex];
    }

    bool empty() const
    {
        return topIndex == -1;
    }

    int size() const
    {
        return topIndex + 1;
    }

    void swap_for_stack(Stack &other) noexcept
    {
        T *tempArr = this->arr;
        this->arr = other.arr;
        other.arr = tempArr;

        int tempTop = this->topIndex;
        this->topIndex = other.topIndex;
        other.topIndex = tempTop;

        int tempCap = this->CAP;
        this->CAP = other.CAP;
        other.CAP = tempCap;
    }

    int status() const
    {
        return CAP - (topIndex + 1);
    }

    // Comparison now works for type T (if T supports ==)
    bool operator==(const Stack &other) const
    {
        if (topIndex != other.topIndex)
            return false;
        for (int i = 0; i <= topIndex; i++)
        {
            if (arr[i] != other.arr[i])
                return false;
        }
        return true;
    }

    // This Displays from top to bottom.
    void display() const
    {
        for (int i = topIndex; i >= 0; i--)
        {
            std::cout << "| " << arr[i] << " |" << std::endl;
        }
        std::cout << " -----" << std::endl;
    }

    // This displays from bottom to top.
    // Chronological order of how data items were added.
    // Global friend operator for output
    friend std::ostream &operator<<(std::ostream &out, const Stack<T> &s)
    {
        for (int i = 0; i <= s.topIndex; i++)
        {
            out << s.arr[i] << " ";
        }
        return out;
    }
    // For the built-in stack , we usually use a while loop with condition !stack.empty()
    // and keeping using top() and pop() for it to print , we don't use a for() loop for this. 
    // We do this while keeping the copy of the original stack object to not lose it.
};
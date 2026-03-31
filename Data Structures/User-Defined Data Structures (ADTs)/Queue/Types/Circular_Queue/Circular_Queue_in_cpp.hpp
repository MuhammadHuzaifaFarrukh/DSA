#pragma once
#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <vector>
#include <deque>

using namespace std;

/**
 * Circular_Queue ADT (Container Adaptor)
 * * Unlike a standard Queue, a Circular Queue reuses "behind space"
 * created by pop() operations before triggering a full memory reallocation.
 * * This implementation follows the "Rule of Zero" where possible,
 * but manually manages indices to enforce circular behavior on the container.
 */

// This will allow only vector and deque , not list because list doesn't perform the ciruclar behaviour that we want with this circular queue.
// It will give compilation error if we use std::List here .
template <typename T, typename Container = std::vector<T>>
class Circular_Queue
{
private:
    Container c;
    int FRONT;
    int REAR;
    int count;
    int CAP;

public:
    // 1. Standard Constructor
    Circular_Queue(int initial_cap = 4)
    {
        if (initial_cap > 0)
        {
            CAP = initial_cap;
        }
        else
        {
            CAP = 4;
        }
        
        c.resize(CAP);
        FRONT = 0;
        REAR = -1;
        count = 0;
    }

    // 2. Initializer List Constructor
    Circular_Queue(std::initializer_list<T> list)
    {
        if (list.size() > 0)
        {
            CAP = (int)list.size();
        }
        else
        {
            CAP = 4;
        }
        
        c.resize(CAP);
        FRONT = 0;
        REAR = -1;
        count = 0;

        for (const auto& item : list)
        {
            push(item);
        }
    }

    // 3. Rule of Zero / Default operations
    Circular_Queue(const Circular_Queue& other) = default;
    Circular_Queue(Circular_Queue&& other) noexcept = default;
    Circular_Queue& operator=(const Circular_Queue& other) = default;
    Circular_Queue& operator=(Circular_Queue&& other) noexcept = default;
    ~Circular_Queue() = default;

    // --- Core Operations ---

    void push(const T& val)
    {
        if (count == CAP)
        {
            // Expansion: Double the capacity
            int new_cap = CAP * 2;
            Container temp(new_cap);

            // Unroll circular elements into new linear space
            for (int i = 0; i < count; i++)
            {
                temp[i] = std::move(c[(FRONT + i) % CAP]);
            }

            c = std::move(temp);
            FRONT = 0;
            REAR = count - 1;
            CAP = new_cap;
        }

        // Reuse space behind FRONT using modulo
        REAR = (REAR + 1) % CAP;
        c[REAR] = val;
        count++;
    }

    void pop()
    {
        if (empty())
        {
            throw std::out_of_range("Queue Underflow");
        }

        FRONT = (FRONT + 1) % CAP;
        count--;

        // Optional Shrinking Logic (25% rule)
        if (CAP > 4)
        {
            if (count <= CAP / 4)
            {
                int new_cap = CAP / 2;
                Container temp(new_cap);
                
                for (int i = 0; i < count; i++)
                {
                    temp[i] = std::move(c[(FRONT + i) % CAP]);
                }
                
                c = std::move(temp);
                FRONT = 0;
                REAR = count - 1;
                CAP = new_cap;
            }
        }
    }

    T& front()
    {
        if (empty())
        {
            throw std::out_of_range("Queue is empty");
        }
        return c[FRONT];
    }

    // --- Utilities ---

    bool empty() const 
    { 
        return count == 0; 
    }
    
    int size() const 
    { 
        return count; 
    }

    void display() const
    {
        if (empty())
        {
            std::cout << "[Empty Circular Queue]" << std::endl;
            return;
        }
        std::cout << "Front -> ";
        for (int i = 0; i < count; i++)
        {
            std::cout << "[" << c[(FRONT + i) % CAP] << "] ";
        }
        std::cout << "<- Rear" << std::endl;
    }

    // --- Relational Operators ---

    bool operator==(const Circular_Queue& other) const
    {
        if (count != other.count)
        {
            return false;
        }
        
        for (int i = 0; i < count; i++)
        {
            if (c[(FRONT + i) % CAP] != other.c[(other.FRONT + i) % other.CAP])
            {
                return false;
            }
        }
        return true;
    }

    friend std::ostream& operator<<(std::ostream& out, const Circular_Queue& q)
    {
        for (int i = 0; i < q.count; i++)
        {
            out << q.c[(q.FRONT + i) % q.CAP] << " ";
        }
        return out;
    }
};
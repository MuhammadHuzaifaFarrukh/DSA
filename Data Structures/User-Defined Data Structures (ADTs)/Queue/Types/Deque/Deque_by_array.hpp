#pragma once
#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>

// The array-based version uses a circular buffer logic. push_front and pop_back use modulo arithmetic to "wrap around" the physical ends of the memory block.

template <typename T>
class Deque
{
private:
    T *arr;
    int FRONT;
    int REAR;
    int count;
    int CAP;

    void reserve(int new_cap)
    {
        T *temp = new T[new_cap];
        for (int i = 0; i < count; i++)
        {
            temp[i] = std::move(arr[(FRONT + i) % CAP]);
        }
        delete[] arr;
        arr = temp;
        FRONT = 0;
        if (count == 0)
        {
            REAR = -1;
        }
        else
        {
            REAR = count - 1;
        }
        CAP = new_cap;
    }

public:
    // --- Nested Iterator ---
    class Iterator
    {
    private:
        T *ptr;
        int logical_idx;
        int f_ptr;
        int capacity;

    public:
        Iterator(T *p, int l, int f, int c) : ptr(p), logical_idx(l), f_ptr(f), capacity(c) {}
        T &operator*() { return ptr[(f_ptr + logical_idx) % capacity]; }
        Iterator &operator++()
        {
            logical_idx++;
            return *this;
        }
        Iterator &operator--()
        {
            logical_idx--;
            return *this;
        }
        bool operator==(const Iterator &other) const { return logical_idx == other.logical_idx; }
        bool operator!=(const Iterator &other) const { return logical_idx != other.logical_idx; }
        int get_idx() const { return logical_idx; }
    };

    Iterator begin() { return Iterator(arr, 0, FRONT, CAP); }
    Iterator end() { return Iterator(arr, count, FRONT, CAP); }

    // --- Constructors & Rule of 5 ---
    Deque(int c = 4)
    {
        if (c > 0)
        {
            CAP = c;
        }
        else
        {
            CAP = 4;
        }
        arr = new T[CAP];
        FRONT = 0;
        REAR = -1;
        count = 0;
    }

    Deque(std::initializer_list<T> list) : Deque((int)list.size())
    {
        for (const auto &item : list)
            push_back(item);
    }

    ~Deque() { delete[] arr; }

    Deque(const Deque &other)
    {
        CAP = other.CAP;
        count = other.count;
        arr = new T[CAP];
        FRONT = 0;
        REAR = (count == 0) ? -1 : count - 1;
        for (int i = 0; i < count; i++)
        {
            arr[i] = other.arr[(other.FRONT + i) % other.CAP];
        }
    }

    Deque(Deque &&other) noexcept : arr(other.arr), FRONT(other.FRONT), REAR(other.REAR), count(other.count), CAP(other.CAP)
    {
        other.arr = nullptr;
        other.count = 0;
    }

    Deque &operator=(const Deque &other)
    {
        if (this != &other)
        {
            delete[] arr;
            CAP = other.CAP;
            count = other.count;
            arr = new T[CAP];
            FRONT = 0;
            REAR = (count == 0) ? -1 : count - 1;
            for (int i = 0; i < count; i++)
            {
                arr[i] = other.arr[(other.FRONT + i) % other.CAP];
            }
        }
        return *this;
    }

    // --- Modifiers ---
    void push_back(const T &val)
    {
        if (full())
            reserve(CAP * 2);
        REAR = (REAR + 1) % CAP;
        arr[REAR] = val;
        count++;
    }

    void push_front(const T &val)
    {
        if (full())
            reserve(CAP * 2);
        FRONT = (FRONT - 1 + CAP) % CAP;
        arr[FRONT] = val;
        count++;
    }

    void pop_back()
    {
        if (empty())
            throw std::out_of_range("Underflow");
        REAR = (REAR - 1 + CAP) % CAP;
        count--;
    }

    void pop_front()
    {
        if (empty())
            throw std::out_of_range("Underflow");
        FRONT = (FRONT + 1) % CAP;
        count--;
    }

    // --- Insert Variants ---
    // 1. Single element
    void insert(int pos, const T &val) // In std deque , this is Iterator pos instead of int pos
    {
        if (pos < 0 || pos > count)
            throw std::out_of_range("Invalid Position");
        if (full())
            reserve(CAP * 2);
        for (int i = count; i > pos; i--)
        {
            (*this)[i] = std::move((*this)[i - 1]);
        }
        (*this)[pos] = val;
        REAR = (REAR + 1) % CAP;
        count++;
    }

    // 2. Fill version
    void insert(int pos, int n, const T &val) // In std deque , this is Iterator pos instead of int pos
    {
        for (int i = 0; i < n; i++)
        {
            insert(pos + i, val);
        }
    }

    // 3. Range version (using Iterators)
    void insert(int pos, Iterator first, Iterator last) // In std deque , this is Iterator pos instead of int pos
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
    // 1. Single element
    void erase(int pos)
    {
        if (pos < 0 || pos >= count)
            throw std::out_of_range("Invalid Position");
        for (int i = pos; i < count - 1; i++)
        {
            (*this)[i] = std::move((*this)[i + 1]);
        }
        REAR = (REAR - 1 + CAP) % CAP;
        count--;
    }

    // 2. Range version
    void erase(int first_pos, int last_pos)
    {
        int num_to_erase = last_pos - first_pos;
        for (int i = 0; i < num_to_erase; i++)
        {
            erase(first_pos);
        }
    }

    // --- Assignments ---
    void assign(int n, const T &val)
    {
        clear();
        for (int i = 0; i < n; i++)
            push_back(val);
    }

    void assign(std::initializer_list<T> list)
    {
        clear();
        for (const auto &item : list)
            push_back(item);
    }

    // --- Accessors & Utilities ---
    T &operator[](int idx) { return arr[(FRONT + idx) % CAP]; }
    T &at(int idx)
    {
        if (idx < 0 || idx >= count)
            throw std::out_of_range("Out of bounds");
        return (*this)[idx];
    }
    T &front() { return arr[FRONT]; }
    T &back() { return arr[REAR]; }
    bool empty() const { return count == 0; }
    bool full() const { return count == CAP; }
    int size() const { return count; }
    void clear()
    {
        count = 0;
        FRONT = 0;
        REAR = -1;
    }
    void shrink_to_fit()
    {
        if (count < CAP)
            reserve(count > 0 ? count : 1);
    }

    void display() const
    {
        for (int i = 0; i < count; i++)
            std::cout << arr[(FRONT + i) % CAP] << " ";
        std::cout << std::endl;
    }

    bool operator==(const Deque &other) const
    {
        if (count != other.count)
            return false;
        for (int i = 0; i < count; i++)
        {
            if ((*this)[i] != other.arr[(other.FRONT + i) % other.CAP])
                return false;
        }
        return true;
    }
    bool operator!=(const Deque &other) const { return !(*this == other); }
};
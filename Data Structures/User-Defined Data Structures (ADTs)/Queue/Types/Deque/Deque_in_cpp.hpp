#pragma once
#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>

// In C++, the standard std::deque (Double-Ended Queue) is a hybrid data structure. 
// It is designed to combine the strengths of a std::vector (fast random access) and a std::list (fast insertions at both ends) without the "massive reallocation" cost of a vector.

/*
Unlike a vector, which is one single contiguous block of memory, a deque is a sequence of fixed-size chunks (or pages).

The Map: There is a central "Map" (an array of pointers).
The Chunks: Each pointer in the map points to a separate, fixed-size array of data.
Growth: When you push to the front or back and the current chunk is full, the deque simply allocates a new chunk and adds its pointer to the map. 
It doesn't have to copy all existing elements to a new location.
*/

// The std::deque is the base container for the stack and queue in C++ and made by chunks that are hardcoded so it cannot be made to use the other containers.
template <typename T>
class Deque
{
private:
    static const int CHUNK_SIZE = 8; // Fixed size for each data block
    T **map;                         // The central "Map" (Array of Pointers)
    int map_size;                    // Total slots available in the map
    int first_chunk;                 // Index of the first allocated chunk in the map
    int last_chunk;                  // Index of the last allocated chunk in the map

    int front_idx; // Index of the first element within map[first_chunk]
    int back_idx;  // Index of the last element within map[last_chunk]
    int count;

    // Helper to get element by logical index
    T &get_at(int index) const
    {
        int total_front_offset = front_idx + index;
        int chunk_offset = total_front_offset / CHUNK_SIZE;
        int element_inner_idx = total_front_offset % CHUNK_SIZE;
        return map[first_chunk + chunk_offset][element_inner_idx];
    }

    void reserve_map()
    {
        int new_map_size = map_size * 3; // Triple the map to allow growth both ways
        T **new_map = new T *[new_map_size];
        for (int i = 0; i < new_map_size; i++)
            new_map[i] = nullptr;

        int start_offset = map_size; // Place old map in the middle
        for (int i = first_chunk; i <= last_chunk; i++)
        {
            new_map[i + start_offset] = map[i];
        }

        delete[] map;
        map = new_map;
        first_chunk += start_offset;
        last_chunk += start_offset;
        map_size = new_map_size;
    }

public:
    // --- Nested Iterator ---
    class Iterator
    {
    private:
        const Deque *parent;
        int logical_pos;

    public:
        Iterator(const Deque *p, int pos) : parent(p), logical_pos(pos) {}
        T &operator*() { return parent->get_at(logical_pos); }
        Iterator &operator++()
        {
            logical_pos++;
            return *this;
        }
        bool operator==(const Iterator &other) const { return logical_pos == other.logical_pos; }
        bool operator!=(const Iterator &other) const { return logical_pos != other.logical_pos; }
    };

    Iterator begin() const { return Iterator(this, 0); }
    Iterator end() const { return Iterator(this, count); }

    // --- Constructors & Rule of 5 ---
    Deque()
    {
        map_size = 8;
        map = new T *[map_size];
        for (int i = 0; i < map_size; i++)
            map[i] = nullptr;

        first_chunk = last_chunk = map_size / 2;
        map[first_chunk] = new T[CHUNK_SIZE];
        front_idx = back_idx = CHUNK_SIZE / 2;
        count = 0;
    }

    Deque(std::initializer_list<T> list) : Deque()
    {
        for (const auto &item : list)
            push_back(item);
    }

    ~Deque()
    {
        for (int i = 0; i < map_size; i++)
        {
            if (map[i] != nullptr)
                delete[] map[i];
        }
        delete[] map;
    }

    // Copy Constructor
    DequeMapped(const Deque &other) : Deque()
    {
        for (int i = 0; i < other.count; i++)
            push_back(other.get_at(i));
    }

    // Assignment Operator
    Deque &operator=(const Deque &other)
    {
        if (this != &other)
        {
            clear();
            for (int i = 0; i < other.count; i++)
                push_back(other.get_at(i));
        }
        return *this;
    }

    // --- Core Modifiers ---
    void push_back(const T &val)
    {
        if (count > 0)
        {
            back_idx++;
            if (back_idx == CHUNK_SIZE)
            {
                if (last_chunk == map_size - 1)
                    reserve_map();
                last_chunk++;
                map[last_chunk] = new T[CHUNK_SIZE];
                back_idx = 0;
            }
        }
        map[last_chunk][back_idx] = val;
        count++;
    }

    void push_front(const T &val)
    {
        if (count > 0)
        {
            front_idx--;
            if (front_idx < 0)
            {
                if (first_chunk == 0)
                    reserve_map();
                first_chunk--;
                map[first_chunk] = new T[CHUNK_SIZE];
                front_idx = CHUNK_SIZE - 1;
            }
        }
        map[first_chunk][front_idx] = val;
        count++;
    }

    void pop_back()
    {
        if (count == 0)
            return;
        if (back_idx == 0)
        {
            delete[] map[last_chunk];
            map[last_chunk] = nullptr;
            last_chunk--;
            back_idx = CHUNK_SIZE - 1;
        }
        else
        {
            back_idx--;
        }
        count--;
    }

    void pop_front()
    {
        if (count == 0)
            return;
        if (front_idx == CHUNK_SIZE - 1)
        {
            delete[] map[first_chunk];
            map[first_chunk] = nullptr;
            first_chunk++;
            front_idx = 0;
        }
        else
        {
            front_idx++;
        }
        count--;
    }

    // --- Complex Modifiers (Insert/Erase Variants) ---
    void insert(int pos, const T &val)
    {
        if (pos < 0 || pos > count)
            throw std::out_of_range("Invalid Position");
        if (pos == 0)
        {
            push_front(val);
        }
        else if (pos == count)
        {
            push_back(val);
        }
        else
        {
            push_back(get_at(count - 1)); // Temporary growth
            for (int i = count - 2; i > pos; i--)
            {
                get_at(i) = std::move(get_at(i - 1));
            }
            get_at(pos) = val;
        }
    }

    void insert(int pos, int n, const T &val)
    {
        for (int i = 0; i < n; i++)
            insert(pos + i, val);
    }

    void erase(int pos)
    {
        if (pos < 0 || pos >= count)
            throw std::out_of_range("Invalid Position");
        for (int i = pos; i < count - 1; i++)
        {
            get_at(i) = std::move(get_at(i + 1));
        }
        pop_back();
    }

    void erase(int first, int last)
    {
        int num = last - first;
        for (int i = 0; i < num; i++)
            erase(first);
    }

    // --- Access & Utils ---
    T &operator[](int idx) { return get_at(idx); }
    T &at(int idx)
    {
        if (idx < 0 || idx >= count)
            throw std::out_of_range("Out of bounds");
        return get_at(idx);
    }

    void clear()
    {
        while (count > 0)
            pop_front();
    }
    bool empty() const { return count == 0; }
    int size() const { return count; }

    void display() const
    {
        for (int i = 0; i < count; i++)
            std::cout << get_at(i) << " ";
        std::cout << std::endl;
    }

    // --- Operator Overloads ---
    bool operator==(const Deque &other) const
    {
        if (count != other.count)
            return false;
        for (int i = 0; i < count; i++)
        {
            if (get_at(i) != other.get_at(i))
                return false;
        }
        return true;
    }

    friend std::ostream &operator<<(std::ostream &out, const Deque &d)
    {
        for (int i = 0; i < d.count; i++)
            out << d.get_at(i) << " ";
        return out;
    }
};
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <functional> // For std::less and std::greater

using namespace std;

/**
 * Unified Heap Class
 * @tparam T The data type to store
 * @tparam Compare The comparison policy:
 * - use std::less<T> for a MAX HEAP (default)
 * - use std::greater<T> for a MIN HEAP
 */

// Heap<int> maxH; // Uses std::less, so parent < child triggers a swap (Max-Heap).
// Heap<int, greater<int>> minH; // Uses std::greater, triggers swap if parent > child.

template <typename T, typename Compare = less<T>> // We can also write : <typename Tp , typename Container = vector<Tp> , typename Compare = less<Tp> >  so it can use deque or vector both , and for that we need to make Container c , an object inside this class instead of T *arr and other data members.
class Heap                                        // Think of this class just like a Priority queue but managed by C-Styled Arrays
{
    T *arr;
    int Size;
    int Cap;
    Compare comp; // Policy object to handle > or < logic
    // less<T> and greater<T> are functors so they use < and > for typename T.
    // For having Heap that checks user defined classes , 
    // 1) Overload both < , > signs in that class. and use it as : Heap <myObject , less<myCompare> or Heap <myObject , greater<myCompare>.
    // less<T> and greater<T> check the type of objects they are comparing and they begin to find the overloaded versions of those objects in that class.

    // 2) But if you don't want to use less<T> and greater<T> , you can implement your own for your own class (The Advanced Way)
    /**
    // For a MAX-HEAP (High priority at top)
        struct MaxCompare
        {
            bool operator()(const myobject& a, const myobject& b) const
            {
                return a.priority < b.priority;
            }
        };
        // Here we use the functor in another struct , not in the myobject because we won't be able to do function overloading as we will have same parameters and same types
        Max-Heap: Heap<myobject, MaxCompare> maxHeap;

        // For a MIN-HEAP (Low priority at top)
        struct MinCompare
        {
            bool operator()(const myobject& a, const myobject& b) const
            {
                return a.priority > b.priority;
            }
        };
        // Here we use the functor in another struct , not in the myobject because we won't be able to do function overloading as we will have same parameters and same types
        Min-Heap: Heap<myobject, MinCompare> minHeap;
        // Now we have two separate structs for functors.Put these structs outside the Heap Class for use.
        // In this method less<T> and greater <T> are completely ignored.


        // Usage
        Heap<myobject, MyCompare> heap;

    */
public:
    Heap(int initialCap = 10)
    {
        if (initialCap <= 0)
            throw invalid_argument("Capacity must be positive");

        try
        {
            arr = new T[initialCap];
            Cap = initialCap;
            Size = 0;
        }
        catch (const bad_alloc &e)
        {
            cerr << "Memory Allocation Failed: " << e.what() << endl;
            throw;
        }
    }

    Heap(initializer_list<T> list)
    {
        Size = 0;
        Cap = list.size() > 0 ? (int)list.size() : 10;
        arr = new T[Cap];

        // We use push() because it automatically calls StepUp
        // to maintain the heap property for every element.
        for (const auto &item : list)
        {
            push(item);
        }
    }

    // StepUp: O(log N)
    void StepUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            // comp(parent, index) checks if parent has LOWER priority than child
            if (comp(arr[parent], arr[index]))
            {
                swap(arr[index], arr[parent]);
                index = parent;
            }
            else
                break;
        }
    }

    // Heapify / StepDown: O(log N)
    void Heapify(int index)
    {
        while (true)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int priorityNode = index;

            // Check left child
            if (left < Size && comp(arr[priorityNode], arr[left]))
            {
                priorityNode = left;
            }

            // Check right child with safety nesting
            if (right < Size)
            {
                if (comp(arr[priorityNode], arr[right]))
                {
                    priorityNode = right;
                }
            }

            if (priorityNode != index)
            {
                swap(arr[index], arr[priorityNode]);
                index = priorityNode;
            }
            else
                break;
        }
    }

    // O(N) Building Approach
    void make_heap()
    {
        if (Size <= 1)
            return;
        for (int i = (Size / 2) - 1; i >= 0; i--)
        {
            Heapify(i);
        }
    }

    // O(N log N) Building Approach
    void make_heap_step_up()
    {
        if (Size <= 1)
            return;
        for (int i = 1; i < Size; i++)
        {
            StepUp(i);
        }
    }

    void push(T val)
    {
        if (Size == Cap)
            reserve(Cap * 2);
        arr[Size] = val;
        StepUp(Size);
        Size++;
    }

    void pop()
    {
        if (Size == 0)
            throw underflow_error("Heap underflow");
        swap(arr[0], arr[Size - 1]);
        Size--;
        if (Size > 0)
            Heapify(0);
    }

    void sort()
    {
        make_heap();
        int originalSize = Size;
        for (int i = Size - 1; i > 0; i--)
        {
            swap(arr[0], arr[i]);
            Size--;
            Heapify(0);
        }
        Size = originalSize;
    }

    // Standard Accessors
    T &top()
    {
        if (Size == 0)
            throw out_of_range("Heap is empty");
        return arr[0];
    }

    T &operator[](int i) { return at(i); }

    T &at(int i)
    {
        if (i < 0 || i >= Size)
            throw out_of_range("Index out of bounds");
        return arr[i];
    }

    int size() const { return Size; }

    void reserve(int newCap)
    {
        if (newCap <= Cap)
            return;
        T *newArr = new T[newCap];
        for (int i = 0; i < Size; i++)
            newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
        Cap = newCap;
    }

    bool operator==(const Heap<T, Compare> &other) const
    {
        if (Size != other.Size)
            return false;
        for (int i = 0; i < Size; i++)
        {
            if (arr[i] != other.arr[i])
                return false;
        }
        return true;
    }

    bool operator!=(const Heap<T, Compare> &other) const
    {
        return !(*this == other);
    }

    void display() const
    {
        for (int i = 0; i < Size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

    template <typename U, typename C>
    friend ostream &operator<<(ostream &os, const Heap<U, C> &h)
    {
        os << "[ ";
        for (int i = 0; i < h.Size; i++)
            os << h.arr[i] << (i == h.Size - 1 ? "" : ", ");
        os << " ]";
        return os;
    }

    ~Heap() { delete[] arr; }
};

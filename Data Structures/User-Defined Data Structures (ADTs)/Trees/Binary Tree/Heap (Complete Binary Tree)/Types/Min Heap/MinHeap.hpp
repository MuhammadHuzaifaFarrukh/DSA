#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

// Min Heap is a type of Heap (Complete Binary Tree).
// Heap is present in C++ in std::make_heap().
// Here we implement our own version of heap using array (or vector).
// Although it can be done through linked list , as we implement any tree.
// However for Heap , it becomes slow , so we don't actually use linked list , we will use array (or vector).
// Min Heap contains the lowest element at front

// We can also do minheap on objects if we have overloaded them with < sign
template <typename T>
class MinHeap
{
    T *arr;
    int Size;
    int Cap;

public:
    MinHeap(int initialCap = 10)
    {
        if (initialCap <= 0)
        {
            throw invalid_argument("Capacity must be positive");
        }

        try
        {
            arr = new T[initialCap];
            Cap = initialCap; // Total Size
            Size = 0;
        }
        catch (const bad_alloc &e)
        {
            cout << "Memory Allocation Failed: " << e.what() << endl;
            throw;
        }
    }

    /**
     * Initializer List Constructor
     * Allows: Heap<int> h = {10, 20, 5, 30};
     */
    Heap(initializer_list<T> list)
    {
        Size = 0;
        Cap = (list.size() > 0) ? (int)list.size() : 10;
        arr = new T[Cap];

        // We use push() because it calls StepUp() for every element,
        // ensuring the heap property is maintained according to 'comp'.
        for (const auto &item : list)
        {
            push(item);
        }
    }

    // Helper: Moves an element up to restore heap property (O(log N))
    // Total Complexity is O(n log n) when in making heap
    // Uses O(logn) in insertion
    // Its Complexity Itself is  : O(logn)
    // You can find Time Complexity of each operation by visualizing them in the form of tree better than as linear.

    void StepUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            // For Min Heap, if child is SMALLER than parent, we swap
            if (arr[index] < arr[parent])
            {
                swap(arr[index], arr[parent]);
                index = parent;
            }
            else
            {
                break;
            }
        }
    }

    // Helper: Moves an element down to restore heap property (O(log N))
    // Total Complexity is O(n) in making heap
    // Uses O(logn) in deletion
    // Its Complexity Itself is  : O(logn)
    // Heapify also called Step Down

    void Heapify(int index)
    {
        while (true)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            // Check if Parent < its both Child or not ?
            if (left < Size && arr[left] < arr[smallest])
            {
                smallest = left;
            }
            if (right < Size)
            {
                // Nested if for memory safety and old compiler compatibility
                if (arr[right] < arr[smallest])
                {
                    smallest = right;
                }
            }
            if (smallest != index)
            {
                swap(arr[index], arr[smallest]);
                index = smallest;
            }
            else
            {
                break;
            }
        }
    }

    // Builds the heap using the Step-Up approach
    // Complexity: O(N log N)
    // As all elements at last level (n/2) go up (logn) so n/2*logn and for levels above last , it keeps getting
    // n/2*logn + n/4*(logn-1) + n/8*(logn-2) + ... ~ O(n logn)

    // Why select i = 1?
    // At i = 0, a single node is already a valid heap by itself.
    // At i = 1, we are adding the second element and stepping it up to its correct position relative to the root.
    // We then move linearly through the array (i++), stepping each new element up into the "finished" part of the heap to its left.

    // Builds the heap using the Step-Up approach O(N log N)

    void make_heap_step_up() // Makes an array or a vector into heap order
    {
        if (Size <= 1)
            return;

        // We start from the first child and "insert" every element
        // into the existing heap structure to its left.
        for (int i = 1; i < Size; i++)
        {
            StepUp(i);
        }
    }

    // Builds the heap using the Step-Down approach (The Standard one)
    // Complexity: O(N)
    // As all elements at 2nd last level can go one step down and same for other above levels :
    // n/4(1) + n/8(2) + n/16(3) + ... + logn ~ O(n).

    // For Step-Down , we start at i = (Size/2)-1
    // We have to start from the last Parent node having atleast one child (Leaf Nodes)
    // All Leaf Nodes are from N/2 to N-1 so (total -> N/2 almost)
    // So we take i = (N/2) - 1

    void make_heap()
    {
        if (Size <= 1)
            return;

        for (int i = (Size / 2) - 1; i >= 0; i--)
        {
            Heapify(i);
        }
    }

    // Also both make_heaps only ensure the 1st highest element being at top.
    // Even 2nd may be determined but others cannot be determined.
    // Then the answers for 2nd-Last Highest can be different for both make_heaps.

    // This inserts an element at the last place and then uses
    // Step-Up Approach to bring it upwards if it is greater.
    // Uses O(logn)

    void push_heap(T val) // Inserts an element and restores Min-Heap property
    {
        if (Size == Cap)
        {
            reserve(Cap * 2);
        }
        arr[Size] = val;
        StepUp(Size);
        Size++;
    }

    // This swaps Root node and last node.
    // Then uses Step-Down Approach to bring the element down if it is small.
    // Uses O(logn)
    void pop_heap() // Removes the root (minimum element)
    {
        if (Size == 0)
        {
            throw underflow_error("Cannot pop from an empty heap");
        }
        swap(arr[0], arr[Size - 1]);
        Size--;

        if (Size > 0)
        {
            Heapify(0);
        }
    }

    // Uses O(n log n) because :
    // make_heap() uses O(n) and
    // Then if all the elements at last level are too big then after swapping all the last level elements (n/2) will have to go down by Heapify
    // So for this : n/2*logn and then for the 2nd last levels and so on so : n/2*logn + n/4*(logn-1) + ...
    // Total : O(n) + n/n/2*logn + n/4*(logn-1) + ... ~ O(n log n).

    // Note: For MinHeap, sort_heap will sort the array in DESCENDING order
    void sort_heap()
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

    // Our Data Structure is already is_heap
    // So we use is_heap for other vector that is not a maxheap object.

    // bool is_heap(){}

    // Vector Related Operations only

    T &front()
    {
        if (Size == 0)
        {
            throw out_of_range("Heap is empty");
        }
        return arr[0];
    }

    T &back()
    {
        if (Size == 0)
        {
            throw out_of_range("Heap is empty");
        }
        return arr[Size - 1];
    }

    T &operator[](int i) // Usually [] doesn't check the ifs but here our [] uses at() so now it behaves same.
    {
        return at(i);
    }

    T &at(int i)
    {
        if (i < 0 || i >= Size)
        {
            throw out_of_range("Index " + to_string(i) + " is out of bounds");
        }
        return arr[i];
    }

    int size()
    {
        return Size;
    }
    int capacity()
    {
        return Cap;
    }

    void reserve(int newCap)
    {
        if (newCap <= Cap)
            return;

        try
        {
            T *newArr = new T[newCap];
            for (int i = 0; i < Size; i++)
            {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
            Cap = newCap;
        }
        catch (const bad_alloc &e)
        {
            throw runtime_error("Failed to expand heap memory");
        }
    }

    bool operator==(const MinHeap<T> &other) const
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

    bool operator!=(const MinHeap<T> &other) const
    {
        return !(*this == other);
    }

    void display() const
    {
        if (Size == 0)
        {
            cout << "Heap is empty." << endl;
            return;
        }
        for (int i = 0; i < Size; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    // Friend template declaration
    template <typename U>
    friend ostream &operator<<(ostream &os, const MinHeap<U> &h)
    {
        if (h.Size == 0)
        {
            os << "[Empty Heap]";
            return os;
        }
        os << "[ ";
        for (int i = 0; i < h.Size; i++)
        {
            os << h.arr[i] << (i == h.Size - 1 ? "" : ", ");
        }
        os << " ]";
        return os;
    }

    ~MinHeap()
    {
        delete[] arr;
    }
};

// Checks for any array if it is heap :
template <typename T>
bool is_heap(vector<T> &nums, int n) // Is it heap or not ?
{
    for (int i = 0; i <= (n / 2) - 1; i++)
    {

        int left = 2 * i + 1;

        int right = 2 * i + 2;

        if (left < n && nums[i] > nums[left])
        {
            return false;
        }

        if (right < n && nums[i] > nums[right])
        {
            return false;
        }
    }
    return true;
}
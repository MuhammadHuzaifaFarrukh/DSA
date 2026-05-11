#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <functional>
#include <initializer_list>
#include <algorithm> // For std::swap

using namespace std;

/**
 * PriorityQueue: A Container Adapter for Heaps.
 * @tparam T The data type
 * @tparam Container Underlying storage (default: vector)
 * @tparam Compare Comparison logic (default: less for Max-Heap)
 */
template <typename T, typename Container = vector<T>, typename Compare = less<T>>
class PriorityQueue
{
private:
    Container c;  // The underlying sequence container
    Compare comp; // The comparison functor

    // StepUp: O(log N)
    void StepUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (comp(c[parent], c[index]))
            {
                swap(c[index], c[parent]);
                index = parent;
            }
            else
                break;
        }
    }

    // StepDown / Heapify : O(log N)
    // We update Heapify to accept a 'limit'.
    // It defaults to c.size() so your push/pop still work without changes!
    // This is done because our container is a vector or deque and we cannot access its size freely as its private.
    // So we used limit for this as we cannot do c.size()--.
    void Heapify(int index, int limit = -1)
    {
        // Use the limit if provided, otherwise use the full container size
        size_t current_limit = (limit == -1) ? c.size() : static_cast<size_t>(limit);

        while (true)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int priorityNode = index;

            // Use 'current_limit' instead of 'c.size()'
            if (left < current_limit && comp(c[priorityNode], c[left]))
                priorityNode = left;

            if (right < current_limit && comp(c[priorityNode], c[right]))
                priorityNode = right;

            if (priorityNode != index)
            {
                swap(c[index], c[priorityNode]);
                index = priorityNode;
            }
            else
                break;
        }
    }

    // O(N) Construction
    // make_heap() uses Heapify to make heap for O(N)
    // If it used Step Up then it would have got O(N Log N).
    void make_heap()
    {
        if (c.size() <= 1)
            return;
        for (int i = (static_cast<int>(c.size()) / 2) - 1; i >= 0; i--)
        {
            Heapify(i);
        }
    }

public:
    // --- Constructors ---

    // Default
    PriorityQueue() : c() {}

    // Initializer List: PriorityQueue<int> pq = {1, 5, 2};
    PriorityQueue(initializer_list<T> list) : c(list)
    {
        make_heap();
    }

    // Iterator Range: PriorityQueue<int> pq(v.begin(), v.end());
    template <typename InputIterator>
    PriorityQueue(InputIterator first, InputIterator last) : c(first, last)
    {
        make_heap();
    }

    // --- The Swap Function ---

    /**
     * Member swap: Swaps the contents of this priority queue with another.
     * Complexity: O(1) if the container (like vector) supports O(1) swap.
     */
    void swap(PriorityQueue &other) noexcept
    {
        using std::swap;
        swap(c, other.c);       // Swaps the underlying containers
        swap(comp, other.comp); // Swaps the comparison logic
    }

    // --- Standard Interface ---

    void push(const T &val)
    {
        c.push_back(val);
        StepUp(c.size() - 1);
    }

    void pop()
    {
        if (c.empty())
            throw underflow_error("PriorityQueue empty");
        std::swap(c[0], c[c.size() - 1]);
        c.pop_back();
        if (!c.empty())
            Heapify(0);
    }

    const T &top() const
    {
        if (c.empty())
            throw out_of_range("PriorityQueue empty");
        return c[0];
    }

    bool empty() const
    {
        return c.empty();
    }
    size_t size() const
    {
        return c.size();
    }

    /**
     * sort: Performs Heapsort on the underlying container.
     * Complexity: O(N log N)
     * Note: After calling this, the underlying container is sorted,
     * but the PriorityQueue property is lost until make_heap() is called again.
     */
    void sort()
    {
        // 1. Ensure the container is a valid heap
        make_heap();

        // We use a local copy of the size to avoid permanently
        // shrinking the actual container c during the sort process.
        int n = static_cast<int>(c.size());

        for (int i = n - 1; i > 0; i--)
        {
            // 2. Move current root to the end
            std::swap(c[0], c[i]);

            // 3. Call Heapify on the reduced heap
            // We need a version of Heapify that accepts a custom size
            // so it doesn't look at the elements already "sorted" at the end.
            Heapify(0, i);
        }
    }

    void display() const
    {
        if (c.empty())
        {
            cout << "PriorityQueue is empty." << endl;
            return;
        }
        for (const auto &item : c)
        {
            cout << item << " ";
        }
        cout << endl;
    }

    bool operator==(const PriorityQueue &other) const
    {
        // Comparing the underlying containers and the comparators
        return (c == other.c);
    }

    bool operator!=(const PriorityQueue &other) const
    {
        return !(*this == other);
    }

    // Friend function for << operator
    template <typename U, typename Cont, typename Comp>
    friend ostream &operator<<(ostream &os, const PriorityQueue<U, Cont, Comp> &pq)
    {
        os << "[ ";
        for (size_t i = 0; i < pq.c.size(); i++)
        {
            os << pq.c[i] << (i == pq.c.size() - 1 ? "" : ", ");
        }
        os << " ]";
        return os;
    }
};

/**
 * Non-member swap overload (Customization Point)
 * This allows std::swap(pq1, pq2) to call our O(1) swap instead of O(N) copy.
 */
template <typename T, typename Container, typename Compare>
void swap(PriorityQueue<T, Container, Compare> &lhs, PriorityQueue<T, Container, Compare> &rhs) noexcept
{
    lhs.swap(rhs);
}
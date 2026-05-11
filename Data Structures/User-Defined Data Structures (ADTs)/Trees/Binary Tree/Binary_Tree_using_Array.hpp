#pragma once
#include <iostream>
#include <queue>
#include <cmath>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <limits>

using namespace std;

template <typename T>
class BinaryTreeArray
{
private:
    T *arr;
    int capacity;
    int current_max_idx; // Tracks the highest occupied index
    T nullValue;         // Value representing "NULL"

    void resize(int minCapacity)
    {
        int newCapacity = capacity;
        while (newCapacity <= minCapacity)
        {
            newCapacity *= 2;
        }

        try
        {
            T *newArr = new T[newCapacity];
            // Initialize new memory first
            for (int i = 0; i < newCapacity; i++)
            {
                newArr[i] = nullValue;
            }

            // Copy old data
            for (int i = 0; i < capacity; i++)
            {
                newArr[i] = arr[i];
            }

            delete[] arr;
            arr = newArr;
            capacity = newCapacity;
        }
        catch (const bad_alloc &)
        {
            throw runtime_error("Critical Error: Array resizing failed due to memory exhaustion.");
        }
    }

    void ensure_capacity(int index)
    {
        if (index < 0)
        {
            throw out_of_range("Negative index access attempted.");
        }
        if (index >= capacity)
        {
            resize(index);
        }
    }

    void create_dfs_helper(int index)
    {
        try
        {
            T val;
            cout << "Enter data for index " << index << " (or " << nullValue << " for NULL): ";
            if (!(cin >> val))
            {
                throw runtime_error("Invalid input type encountered.");
            }

            if (val == nullValue)
            {
                return;
            }

            ensure_capacity(index);
            arr[index] = val;
            if (index > current_max_idx)
            {
                current_max_idx = index;
            }

            cout << "Going Left of " << val << " -> ";
            create_dfs_helper(2 * index + 1);
            cout << "Going Right of " << val << " -> ";
            create_dfs_helper(2 * index + 2);
        }
        catch (const exception &e)
        {
            cerr << "DFS Creation Error: " << e.what() << endl;
            throw; // Re-throw to be handled by caller
        }
    }

    int height_helper(int index) const
    {
        if (index >= capacity || arr[index] == nullValue)
        {
            return -1; // Std Height
        }
        return 1 + max(height_helper(2 * index + 1), height_helper(2 * index + 2));
    }

    // Recursive Balance Helper with early exit optimization
    int height_balanced(int index, bool &valid) const
    {
        if (index >= capacity || arr[index] == nullValue || !valid)
        {
            return -1;
        }

        int lh = height_balanced(2 * index + 1, valid);
        int rh = height_balanced(2 * index + 2, valid);
        if (abs(lh - rh) > 1)
        {
            valid = false;
        }

        return 1 + max(lh, rh);
    }

public:
    // ── 1. Constructors & Rule of Five ───────

    BinaryTreeArray(int cap = 15, T nullVal = T{-1}) : capacity(cap), current_max_idx(-1), nullValue(nullVal)
    {
        if (cap <= 0)
            capacity = 1;
        try
        {
            arr = new T[capacity];
            for (int i = 0; i < capacity; i++)
            {
                arr[i] = nullValue;
            }
        }
        catch (const bad_alloc &)
        {
            throw runtime_error("Failed to allocate initial tree memory.");
        }
    }

    BinaryTreeArray(initializer_list<T> list, T nullVal = T{-1}) : BinaryTreeArray(static_cast<int>(list.size()), nullVal)
    {
        try
        {
            int i = 0;
            for (auto val : list)
            {
                if (val != nullValue)
                {
                    ensure_capacity(i);
                    arr[i] = val;
                    current_max_idx = i;
                }
                i++;
            }
        }
        catch (...)
        {
            delete[] arr; // Cleanup on constructor failure
            throw;
        }
    }

    BinaryTreeArray(const BinaryTreeArray &other) : capacity(other.capacity), current_max_idx(other.current_max_idx), nullValue(other.nullValue)
    {
        try
        {
            arr = new T[capacity];
            for (int i = 0; i < capacity; i++)
            {
                arr[i] = other.arr[i];
            }
        }
        catch (const bad_alloc &)
        {
            throw runtime_error("Copy failed: Out of memory.");
        }
    }

    BinaryTreeArray(BinaryTreeArray &&other) noexcept : arr(other.arr), capacity(other.capacity), current_max_idx(other.current_max_idx), nullValue(other.nullValue)
    {
        other.arr = nullptr;
        other.capacity = 0;
        other.current_max_idx = -1;
    }

    BinaryTreeArray &operator=(const BinaryTreeArray &other)
    {
        if (this != &other)
        {
            try
            {
                T *newArr = new T[other.capacity];
                for (int i = 0; i < other.capacity; i++)
                {
                    newArr[i] = other.arr[i];
                }

                delete[] arr;
                arr = newArr;
                capacity = other.capacity;
                current_max_idx = other.current_max_idx;
                nullValue = other.nullValue;
            }
            catch (const bad_alloc &)
            {
                throw runtime_error("Assignment failed: Out of memory.");
            }
        }
        return *this;
    }

    BinaryTreeArray &operator=(BinaryTreeArray &&other) noexcept
    {
        if (this != &other)
        {
            delete[] arr;
            arr = other.arr;
            capacity = other.capacity;
            current_max_idx = other.current_max_idx;
            nullValue = other.nullValue;

            other.arr = nullptr;
            other.capacity = 0;
            other.current_max_idx = -1;
        }
        return *this;
    }

    ~BinaryTreeArray()
    {
        if (arr != nullptr)
        {
            delete[] arr;
            arr = nullptr;
        }
    }

    // ── 2. Construction Methods ──────────────

    void make_tree_dfs()
    {
        clear_tree();
        create_dfs_helper(0);
    }

    void make_tree_bfs()
    {
        try
        {
            clear_tree();
            T val;
            cout << "Enter root node: ";
            if (!(cin >> val))
            {
                throw runtime_error("Invalid root input.");
            }

            if (val == nullValue)
            {
                return;
            }

            ensure_capacity(0);
            arr[0] = val;
            current_max_idx = 0;
            queue<int> q;
            q.push(0);

            while (!q.empty())
            {
                int currIdx = q.front();
                q.pop();
                T l, r;

                cout << "Left of " << arr[currIdx] << ": ";
                if (!(cin >> l))
                {
                    throw runtime_error("Invalid left-child input.");
                }
                if (l != nullValue)
                {
                    int lIdx = 2 * currIdx + 1;
                    ensure_capacity(lIdx);
                    arr[lIdx] = l;
                    if (lIdx > current_max_idx)
                    {
                        current_max_idx = lIdx;
                    }
                    q.push(lIdx);
                }

                cout << "Right of " << arr[currIdx] << ": ";
                if (!(cin >> r))
                {
                    throw runtime_error("Invalid right-child input.");
                }
                if (r != nullValue)
                {
                    int rIdx = 2 * currIdx + 2;
                    ensure_capacity(rIdx);
                    arr[rIdx] = r;
                    if (rIdx > current_max_idx)
                    {
                        current_max_idx = rIdx;
                    }
                    q.push(rIdx);
                }
            }
        }
        catch (const exception &e)
        {
            cerr << "BFS Tree Creation failed: " << e.what() << endl;
        }
    }

    // ── 3. Traversals ────────────────────────

    void preorder(int idx = 0) const
    {
        if (idx < 0 || idx >= capacity || arr[idx] == nullValue)
        {
            return;
        }
        cout << arr[idx] << " ";
        preorder(2 * idx + 1);
        preorder(2 * idx + 2);
    }

    void inorder(int idx = 0) const
    {
        if (idx < 0 || idx >= capacity || arr[idx] == nullValue)
        {
            return;
        }
        inorder(2 * idx + 1);
        cout << arr[idx] << " ";
        inorder(2 * idx + 2);
    }

    void postorder(int idx = 0) const
    {
        if (idx < 0 || idx >= capacity || arr[idx] == nullValue)
        {
            return;
        }
        postorder(2 * idx + 1);
        postorder(2 * idx + 2);
        cout << arr[idx] << " ";
    }

    void levelorder() const
    {
        if (current_max_idx == -1)
        {
            cout << "Tree is empty.";
            return;
        }
        for (int i = 0; i <= current_max_idx; i++)
        {
            if (arr[i] != nullValue)
            {
                cout << arr[i] << " ";
            }
        }
    }

    // ── 4. Properties & Search ───────────────

    int get_height() const 
    { 
        return height_helper(0); 
    }

    int count_nodes() const
    {
        int count = 0;
        for (int i = 0; i <= current_max_idx; i++)
        {
            if (arr[i] != nullValue)
            {
                count++;
            }
        }
        return count;
    }

    int count_leaves() const
    {
        int leaves = 0;
        for (int i = 0; i <= current_max_idx; i++)
        {
            if (arr[i] != nullValue)
            {
                int l = 2 * i + 1, r = 2 * i + 2;
                bool noLeft = (l >= capacity || arr[l] == nullValue);
                bool noRight = (r >= capacity || arr[r] == nullValue);
                if (noLeft && noRight)
                    leaves++;
            }
        }
        return leaves;
    }

    bool search(T val) const
    {
        for (int i = 0; i <= current_max_idx; i++)
        {
            if (arr[i] == val)
            {
                return true;
            }
        }
        return false;
    }

    bool is_balanced() const
    {
        bool h = 0;
        return height_balanced(0, h);
    }

    T find_parent(T val) const
    {
        if (current_max_idx == -1 || arr[0] == val)
        {
            return nullValue;
        }
        for (int i = 1; i <= current_max_idx; i++)
        {
            if (arr[i] == val)
            {
                return arr[(i - 1) / 2];
            }
        }
        return nullValue;
    }

    bool is_bst(int idx = 0, T minVal = numeric_limits<T>::min(), T maxVal = numeric_limits<T>::max()) const
    {
        if (idx >= capacity || arr[idx] == nullValue)
        {
            return true;
        }
        if (arr[idx] <= minVal || arr[idx] >= maxVal)
        {
            return false;
        }
        return is_bst(2 * idx + 1, minVal, arr[idx]) && is_bst(2 * idx + 2, arr[idx], maxVal);
    }

    // ── 5. Insertion & Deletion ──────────────

    void insert_node(T val)
    {
        try
        {
            int i = 0;
            while (true)
            {
                ensure_capacity(i);
                if (arr[i] == nullValue)
                {
                    arr[i] = val;
                    if (i > current_max_idx)
                    {
                        current_max_idx = i;
                    }
                    return;
                }
                i++;
            }
        }
        catch (const exception &e)
        {
            cerr << "Insertion failed: " << e.what() << endl;
        }
    }

    void insert_at_end(T val)
    {
        try
        {
            int nextIdx = current_max_idx + 1;
            ensure_capacity(nextIdx);
            arr[nextIdx] = val;
            current_max_idx = nextIdx;
        }
        catch (const exception &e)
        {
            cerr << "Append failed: " << e.what() << endl;
        }
    }

    void delete_node(T val)
    {
        int targetIdx = -1;
        for (int i = 0; i <= current_max_idx; i++)
        {
            if (arr[i] == val)
            {
                targetIdx = i;
                break;
            }
        }
        if (targetIdx != -1)
        {
            arr[targetIdx] = arr[current_max_idx];
            arr[current_max_idx] = nullValue;
            // Find the previous actual node after deleting
            while (current_max_idx >= 0 && arr[current_max_idx] == nullValue)
            {
                current_max_idx--;
            }
        }
    }

    void delete_last_node()
    {
        if (current_max_idx >= 0)
        {
            arr[current_max_idx] = nullValue;
            current_max_idx--;
            // Find the previous actual node after deleting
            while (current_max_idx >= 0 && arr[current_max_idx] == nullValue)
            {
                current_max_idx--;
            }
        }
    }

    void clear_tree()
    {
        for (int i = 0; i < capacity; i++)
        {
            arr[i] = nullValue;
        }
        current_max_idx = -1;
    }
};
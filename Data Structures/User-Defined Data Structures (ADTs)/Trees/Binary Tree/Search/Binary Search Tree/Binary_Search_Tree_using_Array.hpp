#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <new>

using namespace std;
// Binary Search Tree (BST) is a Binary Tree that keeps elements in specific order.
// Left Child Node < Parent Node < Right Child Node.
// It can be implemented via list or array depending on our use case.
// It has core operations like insertion , deletion or searching.

// Usually nodes in BST have unique values (mostly).
// However if there are duplicates (for any specific reason) , then here's how we handle :
// 1) Use an unordered map for it , or use an int count in the Node class to keep count of every node there and only delete when its count becomes zero however it becomes costly if all nodes are unique.
// 2) Create another node and decide if you want either this Left Child Node <= Parent or Parent <= Right Child Node and stick with any one of it for your tree however this may cost more memory than above one.
// The 2nd method is not used because it is quite bad in a sense that if implemented , it won't let BST property hold for the nodes.
// The 1st method is actually quite good for these kind of tasks.

// Here we implement it using arrays.
// If there is a parent then its child are at 2i+1 and 2i+2
// If we have a child , then its parent is at (i-1)/2.

template <typename T>
class BinarySearchTree
{
private:
    T *arr;
    int capacity;
    int size;

    bool isEmpty(int i) const
    {
        return i >= capacity || arr[i] == T(-1);
    }

    void grow()
    {
        int newCap = capacity * 2;
        T *newArr = new T[newCap];
        for (int i = 0; i < capacity; ++i)
        {
            newArr[i] = arr[i];
        }
        for (int i = capacity; i < newCap; ++i)
        {
            newArr[i] = T(-1);
        }
        delete[] arr;
        arr = newArr;
        capacity = newCap;
    }

    void ensureIndex(int i)
    {
        while (i >= capacity)
        {
            grow();
        }
    }

    void promoteSubtree(int src, int dst)
    {
        ensureIndex(dst);
        if (isEmpty(src))
        {
            if (dst < capacity)
            {
                arr[dst] = T(-1);
            }
            return;
        }
        arr[dst] = arr[src];
        arr[src] = T(-1);
        promoteSubtree(2 * src + 1, 2 * dst + 1);
        promoteSubtree(2 * src + 2, 2 * dst + 2);
    }

public:
    BinarySearchTree(int initialCapacity = 16) : arr(nullptr), capacity(0), size(0)
    {
        try
        {
            if (initialCapacity < 1)
            {
                initialCapacity = 1;
            }
            arr = new T[initialCapacity];
            capacity = initialCapacity;
            for (int i = 0; i < capacity; ++i)
            {
                arr[i] = T(-1);
            }
        }
        catch (const bad_alloc &e)
        {
            cerr << "Constructor Failed: Insufficient memory. " << e.what() << endl;
            delete[] arr;
            arr = nullptr;
            throw;
        }
    }

    BinarySearchTree(const BinarySearchTree<T> &other) : arr(nullptr), capacity(0), size(0)
    {
        try
        {
            arr = new T[other.capacity];
            capacity = other.capacity;
            size = other.size;
            for (int i = 0; i < capacity; ++i)
            {
                arr[i] = other.arr[i];
            }
        }
        catch (const bad_alloc &e)
        {
            cerr << "Copy Constructor Failed: Insufficient memory. " << e.what() << endl;
            delete[] arr;
            arr = nullptr;
            throw;
        }
    }

    BinarySearchTree<T> &operator=(const BinarySearchTree<T> &other)
    {
        if (this != &other)
        {
            try
            {
                BinarySearchTree<T> temp(other);
                swap(arr, temp.arr);
                swap(capacity, temp.capacity);
                swap(size, temp.size);
            }
            catch (const bad_alloc &e)
            {
                cerr << "Assignment Failed: State preserved. " << e.what() << endl;
                throw;
            }
        }
        return *this;
    }

    BinarySearchTree(BinarySearchTree<T> &&other) noexcept : arr(other.arr), capacity(other.capacity), size(other.size)
    {
        other.arr = nullptr;
        other.capacity = 0;
        other.size = 0;
    }

    BinarySearchTree<T> &operator=(BinarySearchTree<T> &&other) noexcept
    {
        if (this != &other)
        {
            delete[] arr;
            arr = other.arr;
            capacity = other.capacity;
            size = other.size;
            other.arr = nullptr;
            other.capacity = 0;
            other.size = 0;
        }
        return *this;
    }

    ~BinarySearchTree()
    {
        delete[] arr;
        arr = nullptr;
    }

    void insert(int i, T val)
    {
        try
        {
            ensureIndex(i);
            if (isEmpty(i))
            {
                arr[i] = val;
                ++size;
                return;
            }
            if (val < arr[i])
            {
                insert(2 * i + 1, val);
            }
            else if (val > arr[i])
            {
                insert(2 * i + 2, val);
            }
        }
        catch (const bad_alloc &e)
        {
            cerr << "Insertion failed: Out of memory. " << e.what() << endl;
            throw runtime_error("Tree insertion blocked: Out of Memory.");
        }
    }

    void insert(T val)
    {
        insert(0, val);
    }

    T findMin(int i) const
    {
        try
        {
            if (isEmpty(0))
            {
                throw out_of_range("Requested minimum, but BST is empty.");
            }
            while (!isEmpty(2 * i + 1))
            {
                i = 2 * i + 1;
            }
            return arr[i];
        }
        catch (const out_of_range &e)
        {
            cerr << "Range Exception: " << e.what() << endl;
            throw;
        }
    }

    T findMin() const
    {
        return findMin(0);
    }

    T findMax(int i) const
    {
        try
        {
            if (isEmpty(0))
            {
                throw out_of_range("Requested maximum, but BST is empty.");
            }
            while (!isEmpty(2 * i + 2))
            {
                i = 2 * i + 2;
            }
            return arr[i];
        }
        catch (const out_of_range &e)
        {
            cerr << "Range Exception: " << e.what() << endl;
            throw;
        }
    }

    T findMax() const { return findMax(0); }

    bool search(int i, T val) const
    {
        if (isEmpty(i))
        {
            return false;
        }
        if (val == arr[i])
        {
            return true;
        }
        if (val < arr[i])
        {
            return search(2 * i + 1, val);
        }
        return search(2 * i + 2, val);
    }

    bool search(T val) const { return search(0, val); }

    void deleteNode(int i, T val)
    {
        try
        {
            if (isEmpty(0))
            {
                throw out_of_range("Cannot delete from an empty BST.");
            }
            if (!search(val))
            {
                throw out_of_range("Value not found in BST.");
            }

            if (isEmpty(i))
            {
                return;
            }

            if (val < arr[i])
            {
                deleteNode(2 * i + 1, val);
            }
            else if (val > arr[i])
            {
                deleteNode(2 * i + 2, val);
            }
            else
            {
                bool hasLeft = !isEmpty(2 * i + 1);
                bool hasRight = !isEmpty(2 * i + 2);

                if (!hasLeft && !hasRight)
                {
                    arr[i] = T(-1);
                    --size;
                }
                else if (hasLeft && !hasRight)
                {
                    promoteSubtree(2 * i + 1, i);
                }
                else if (!hasLeft && hasRight)
                {
                    promoteSubtree(2 * i + 2, i);
                }
                else
                {
                    // two children: replace with in-order predecessor
                    int pred = 2 * i + 1;
                    while (!isEmpty(2 * pred + 2))
                    {
                        pred = 2 * pred + 2;
                    }
                    arr[i] = arr[pred];
                    deleteNode(2 * i + 1, arr[i]);
                }
            }
        }
        catch (const out_of_range &e)
        {
            cerr << "Range Exception: " << e.what() << endl;
            throw;
        }
    }

    void deleteNode(T val)
    {
        deleteNode(0, val);
    }

    int height(int i) const
    {
        if (isEmpty(i))
        {
            return -1;
        }
        return 1 + max(height(2 * i + 1), height(2 * i + 2));
    }

    int height() const
    {
        return height(0);
    }

    void inorder(int i) const
    {
        if (isEmpty(i))
        {
            return;
        }
        inorder(2 * i + 1);
        cout << arr[i] << " ";
        inorder(2 * i + 2);
    }

    void inorder() const
    {
        inorder(0);
        cout << "\n";
    }

    void preorder(int i) const
    {
        if (isEmpty(i))
        {
            return;
        }
        cout << arr[i] << " ";
        preorder(2 * i + 1);
        preorder(2 * i + 2);
    }

    void preorder() const
    {
        preorder(0);
        cout << "\n";
    }

    void postorder(int i) const
    {
        if (isEmpty(i))
        {
            return;
        }
        postorder(2 * i + 1);
        postorder(2 * i + 2);
        cout << arr[i] << " ";
    }

    void postorder() const
    {
        postorder(0);
        cout << "\n";
    }

    bool empty() const
    {
        return size == 0;
    }
    int getSize() const
    {
        return size;
    }
    int getCap() const
    {
        return capacity;
    }
    T *get_arr() const
    {
        return arr;
    }
};
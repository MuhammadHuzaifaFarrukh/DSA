#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <new>

using namespace std;

// Binary Search Tree (BST) is a Binary Tree that keeps elements in specific order.
// Left Child Node < Parent Node < Right Child Node.
// It can be implemented via list or array depending on our use case.
// It has core operations like insertion , deletion or searching.

// Now we implement a binary search tree with duplicates allowed.
// We have an unordered map inside our BST Class which will keep the count of our all the repeated elements inside tree.
// Now even our move assignment and move constructors are optimized due to maps.
// Also this method is the optimized one to store a BST of duplicates.

template <typename T>
class Node
{
public:
    T val;
    Node<T> *left;
    Node<T> *right;

    Node(T v = T(), Node<T> *l = nullptr, Node<T> *r = nullptr) : val(v), left(l), right(r) {}
};

template <typename T>
class BinarySearchTree
{
private:
    Node<T> *root;
    std::unordered_map<T, int> frequencyMap; // Maps elements to their respective duplicate counts

    Node<T> *copyTree(const Node<T> *otherRoot)
    {
        if (!otherRoot)
            return nullptr;

        try
        {
            Node<T> *newNode = new Node<T>(otherRoot->val);
            newNode->left = copyTree(otherRoot->left);
            newNode->right = copyTree(otherRoot->right);
            return newNode;
        }
        catch (const std::bad_alloc &)
        {
            throw;
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    // Copy Constructor (Deep copies node topology + frequency map)
    BinarySearchTree(const BinarySearchTree<T> &other)
    {
        try
        {
            root = copyTree(other.root);
            frequencyMap = other.frequencyMap; // Duplicates the map data natively
        }
        catch (const std::bad_alloc &e)
        {
            cerr << "Copy Constructor Failed: Insufficient memory. " << e.what() << endl;
            root = nullptr;
            frequencyMap.clear();
            throw;
        }
    }

    // Copy Assignment Operator (Copy-and-Swap safety)
    BinarySearchTree<T> &operator=(const BinarySearchTree<T> &other)
    {
        if (this != &other)
        {
            try
            {
                BinarySearchTree<T> temp(other);
                swap(this->root, temp.root);
                swap(this->frequencyMap, temp.frequencyMap);
            }
            catch (const std::bad_alloc &e)
            {
                cerr << "Assignment Failed: Memory allocation crashed. State preserved. " << e.what() << endl;
                throw;
            }
        }
        return *this;
    }

    // Move Constructor
    BinarySearchTree(BinarySearchTree<T> &&other) noexcept : root(other.root), frequencyMap(std::move(other.frequencyMap))
    {
        other.root = nullptr;
    }

    // Move Assignment Operator
    BinarySearchTree<T> &operator=(BinarySearchTree<T> &&other) noexcept
    {
        if (this != &other)
        {
            destroy_tree(root);
            root = other.root;
            frequencyMap = std::move(other.frequencyMap);
            other.root = nullptr;
        }
        return *this;
    }

    // Destructor
    ~BinarySearchTree()
    {
        destroy_tree(root);
        root = nullptr;
        frequencyMap.clear();
    }

    void destroy_tree(Node<T> *p)
    {
        if (p != nullptr)
        {
            destroy_tree(p->left);
            destroy_tree(p->right);
            delete p;
        }
    }

    void insert(T val)
    {

        if (val == -1)
            return currRoot;

        if (!currRoot)
        {
            Node *temp;
            try
            {
                temp = new Node<T>(val);
                frequencyMap[val] = 1; // Mark frequency as 1 for a completely new unique node
                return temp;
            }
            catch (const std::bad_alloc &e)
            {
                cerr << "Critical Error: Insertion failed due to memory exhaustion! " << e.what() << endl;
                throw std::runtime_error("Tree insertion blocked: Out of Memory.");
            }
        }

        if (val < currRoot->val)
        {
            currRoot->left = insertHelper(currRoot->left, val);
        }
        else if (val > currRoot->val)
        {
            currRoot->right = insertHelper(currRoot->right, val);
        }
        else
        {
            // Value already exists as a physical node -> Simply increment the map counter
            frequencyMap[val]++;
        }
        return currRoot;
    }

    Node<T> *deleteNode(Node<T> *currRoot, T val)
    {
        if (!currRoot)
        {
            return nullptr;
        }

        if (val < currRoot->val)
        {
            currRoot->left = deleteNode(currRoot->left, val);
            return currRoot;
        }
        else if (val > currRoot->val)
        {
            currRoot->right = deleteNode(currRoot->right, val);
            return currRoot;
        }
        else
        {
            // Target Node Found! Lower the counter configuration inside the map tracking layer
            frequencyMap[val]--;

            // If instances remain alive inside the lookup registry, hold onto physical node linkages
            if (frequencyMap[val] > 0)
            {
                return currRoot;
            }

            // Clean up the map entry entirely since count has hit zero
            frequencyMap.erase(val);

            // True Structural physical unlinking begins here
            if (!currRoot->left && !currRoot->right)
            {
                delete currRoot;
                return nullptr;
            }
            else if (!currRoot->left)
            {
                Node<T> *temp = currRoot->right;
                delete currRoot;
                return temp;
            }
            else if (!currRoot->right)
            {
                Node<T> *temp = currRoot->left;
                delete currRoot;
                return temp;
            }
            else
            {
                // Find inorder predecessor
                Node<T> *parent = currRoot;
                Node<T> *child = currRoot->left;
                while (child->right)
                {
                    parent = child;
                    child = child->right;
                }

                if (currRoot != parent)
                {
                    parent->right = child->left;
                    child->left = currRoot->left;
                    child->right = currRoot->right;
                }
                else
                {
                    child->right = currRoot->right;
                }

                delete currRoot;
                return child;
            }
        }
    }

    // Inorder prints the values sequentially based on map frequency counts
    void inorder(Node<T> *currRoot)
    {
        if (!currRoot)
        {
            return;
        }
        inorder(currRoot->left);

        // Fetch current duplicate frequency from the unordered map
        int count = frequencyMap[currRoot->val];
        for (int i = 0; i < count; ++i)
        {
            cout << currRoot->val << " ";
        }

        inorder(currRoot->right);
    }

    // To query exactly how many times an element currently exists
    int getCount(T val)
    {
        auto it = frequencyMap.find(val);
        if (it != frequencyMap.end())
        {
            return it->second;
        }
        return 0; // Not present
    }

    T findMin()
    {
        try
        {
            if (!root)
            {
                throw std::out_of_range("Requested minimum element, but the BST is completely empty.");
            }
            Node<T> *temp = root;
            while (temp->left)
            {
                temp = temp->left;
            }
            return temp->val;
        }
        catch (const std::out_of_range &e)
        {
            cerr << "Range Exception: " << e.what() << endl;
            throw;
        }
    }

    T findMax()
    {
        try
        {
            if (!root)
            {
                throw std::out_of_range("Requested maximum element, but the BST is completely empty.");
            }
            Node<T> *temp = root;
            while (temp->right)
            {
                temp = temp->right;
            }
            return temp->val;
        }
        catch (const std::out_of_range &e)
        {
            cerr << "Range Exception: " << e.what() << endl;
            throw;
        }
    }

    Node<T> *get_root() const
    {
        return root;
    }
    Node<T> *&get_root()
    {
        return root;
    }
};
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

// Now we implement a binary search tree with duplicates allowed.
// Our Node class has an int count to keep count of duplicates each time a value is entered.
// This will be checked for all nodes and in almost all the functions while processing , traversing , etc.
// This way is better than making the duplicate nodes but it also takes toll to keep int pointer even if the tree is unique.
// Moreover this implementation is way better than making duplicate nodes once more as inorder traversal may become disturbed in that way as well.
// If we tried making each duplicate node that would stop in most of the cases even if we decided to keep it at either left or right , it would still not work for most cases. It would not let BST property hold for the nodes.

// There's still 1 way to optimize it and that is to keep the count of duplicates only inside an unordered map , in this way the unique valued nodes won't have an int count taking space.

template <typename T>
class Node
{
public:
    T val;
    int count;
    Node<T> *left;
    Node<T> *right;

    Node(T v = T(), Node<T> *l = nullptr, Node<T> *r = nullptr)
        : val(v), count(1), left(l), right(r) {}
};

template <typename T>
class BinarySearchTree
{
private:
    Node<T> *root;

    Node<T> *copyTree(const Node<T> *otherRoot)
    {
        if (!otherRoot)
            return nullptr;

        try
        {
            Node<T> *newNode = new Node<T>(otherRoot->val);
            newNode->count = otherRoot->count;
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

    BinarySearchTree(const BinarySearchTree<T> &other)
    {
        try
        {
            root = copyTree(other.root);
        }
        catch (const std::bad_alloc &e)
        {
            cerr << "Copy Constructor Failed: Insufficient memory. " << e.what() << endl;
            root = nullptr;
            throw;
        }
    }

    // Copy Assignment (Copy-and-Swap idiom)
    BinarySearchTree<T> &operator=(const BinarySearchTree<T> &other)
    {
        if (this != &other)
        {
            try
            {
                BinarySearchTree<T> temp(other);
                swap(this->root, temp.root);
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
    BinarySearchTree(BinarySearchTree<T> &&other) noexcept : root(other.root)
    {
        other.root = nullptr;
    }

    // Move Assignment
    BinarySearchTree<T> &operator=(BinarySearchTree<T> &&other) noexcept
    {
        if (this != &other)
        {
            destroy_tree(root);
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }

    // Destructor
    ~BinarySearchTree()
    {
        destroy_tree(root);
        root = nullptr;
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

    Node<T> *insert(Node<T> *currRoot, T val)
    {
        if (val == -1)
        {
            return currRoot;
        }

        if (!currRoot)
        {
            Node<T> *temp;
            try
            {
                temp = new Node<T>(val);
            }
            catch (const std::bad_alloc &e)
            {
                cerr << "Critical Error: Insertion failed due to memory exhaustion! " << e.what() << endl;
                throw std::runtime_error("Tree insertion blocked: Out of Memory.");
            }

            return temp;
        }

        if (val < currRoot->val)
        {
            currRoot->left = insert(currRoot->left, val);
        }
        else if (val > currRoot->val)
        {
            currRoot->right = insert(currRoot->right, val);
        }
        else
        {
            currRoot->count++;
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
            currRoot->count--;
            if (currRoot->count > 0)
            {
                return currRoot;
            }

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

    void inorder(Node<T> *currRoot)
    {
        if (!currRoot)
        {
            return;
        }
        inorder(currRoot->left);

        for (int i = 0; i < currRoot->count; ++i)
        {
            cout << currRoot->val << " ";
        }

        inorder(currRoot->right);
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

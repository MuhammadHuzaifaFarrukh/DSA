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

    Node<T> *insertHelper(Node<T> *currRoot, T val)
    {
        if (val == -1)
            return currRoot;

        if (!currRoot)
        {
            return new Node<T>(val);
        }
        if (val < currRoot->val)
        {
            currRoot->left = insertHelper(currRoot->left, val);
        }
        else if (val > currRoot->val)
        {
            currRoot->right = insertHelper(currRoot->right, val);
        }
        return currRoot;
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

    BinarySearchTree(BinarySearchTree<T> &&other) noexcept : root(other.root)
    {
        other.root = nullptr;
    }

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
    void insert(T val)
    {
        try
        {
            root = insertHelper(root, val);
        }
        catch (const std::bad_alloc &e)
        {
            cerr << "Critical Error: Insertion failed due to memory exhaustion! " << e.what() << endl;
            throw std::runtime_error("Tree insertion blocked: Out of Memory.");
        }
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
        cout << currRoot->val << " ";
        inorder(currRoot->right);
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
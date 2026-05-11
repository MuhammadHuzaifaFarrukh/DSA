#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <initializer_list>
#include <limits>

using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node *left, *right;
    Node(T val = T{}) : data(val), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinaryTree
{
private:
    Node<T> *root;

    // ── Private Helpers ──────────────────────

    void destroy(Node<T> *p)
    {
        if (p)
        {
            destroy(p->left);
            destroy(p->right);
            delete p;
        }
    }

    Node<T> *copyTree(Node<T> *p)
    {
        if (!p)
        {
            return nullptr;
        }
        Node<T> *newNode = new Node<T>(p->data);
        newNode->left = copyTree(p->left);
        newNode->right = copyTree(p->right);
        return newNode;
    }

    // Uses numeric_limits so it works for any ordered type
    bool isBSTHelper(Node<T> *p, T minVal, T maxVal) const
    {
        if (!p)
        {
            return true;
        }
        if (p->data <= minVal || p->data >= maxVal)
        {
            return false;
        }
        return isBSTHelper(p->left, minVal, p->data) && isBSTHelper(p->right, p->data, maxVal);
    }

    // ── Private recursive traversals (used internally) ──

    Node<T> *create_dfs()
    {
        T x;
        cout << "Enter data (-1 for null): ";
        cin >> x;
        if (x == T{-1})
        {
            return nullptr;
        }
        Node<T> *p = new Node<T>(x);
        cout << "Left of " << x << " -> ";
        p->left = create_dfs();
        cout << "Right of " << x << " -> ";
        p->right = create_dfs();
        return p;
    }

public:
    // ── 1. Constructors & Rule of Five ───────

    BinaryTree() : root(nullptr) {}

    // Initializer-list constructor (BFS / Level-Order)
    BinaryTree(initializer_list<T> list) : root(nullptr)
    {
        if (list.size() == 0 || *list.begin() == T{-1})
        {
            return;
        }

        auto it = list.begin();
        root = new Node<T>(*it++);
        queue<Node<T> *> q;
        q.push(root);

        while (!q.empty() && it != list.end())
        {
            Node<T> *curr = q.front();
            q.pop();

            if (it != list.end())
            {
                T val = *it++;
                if (val != T{-1})
                {
                    curr->left = new Node<T>(val);
                    q.push(curr->left);
                }
            }
            if (it != list.end())
            {
                T val = *it++;
                if (val != T{-1})
                {
                    curr->right = new Node<T>(val);
                    q.push(curr->right);
                }
            }
        }
    }

    // Copy constructor
    BinaryTree(const BinaryTree &other) { root = copyTree(other.root); }

    // Copy assignment
    BinaryTree &operator=(const BinaryTree &other)
    {
        if (this != &other)
        {
            clear_tree();
            root = copyTree(other.root);
        }
        return *this;
    }

    // Move constructor
    BinaryTree(BinaryTree &&other) noexcept : root(other.root) { other.root = nullptr; }

    // Move assignment
    BinaryTree &operator=(BinaryTree &&other) noexcept
    {
        if (this != &other)
        {
            clear_tree();
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }

    ~BinaryTree() { clear_tree(); }

    int _get_height(Node<T> *p) const
    {
        if (!p)
        {
            return -1;
        }
        return 1 + max(_get_height(p->left), _get_height(p->right));
    }

    int _countNodes(Node<T> *p) const
    {
        if (!p)
        {
            return 0;
        }
        return 1 + _countNodes(p->left) + _countNodes(p->right);
    }

    void _count_leaves(Node<T> *p, int &count) const
    {
        if (!p)
        {
            return;
        }
        if (!p->left && !p->right)
        {
            count++;
            return;
        }
        _count_leaves(p->left, count);
        _count_leaves(p->right, count);
    }

    int _heightForBalance(Node<T> *p, bool &valid) const
    {
        if (!p || !valid)
        {
            return 0;
        }
        int L = _heightForBalance(p->left, valid);
        int R = _heightForBalance(p->right, valid);
        if (abs(L - R) > 1)
        {
            valid = false;
        }
        return 1 + max(L, R);
    }

    // ── 2. Tree Construction ─────────────────

    void make_tree_dfs()
    {
        clear_tree();
        root = create_dfs();
    }

    void make_tree_bfs()
    {
        clear_tree();
        T x;
        cout << "Enter root: ";
        cin >> x;
        if (x == T{-1})
        {
            return;
        }
        root = new Node<T>(x);
        queue<Node<T> *> q;
        q.push(root);
        while (!q.empty())
        {
            Node<T> *p = q.front();
            q.pop();
            T l, r;
            cout << "Left child of " << p->data << ": ";
            cin >> l;
            if (l != T{-1})
            {
                p->left = new Node<T>(l);
                q.push(p->left);
            }
            cout << "Right child of " << p->data << ": ";
            cin >> r;
            if (r != T{-1})
            {
                p->right = new Node<T>(r);
                q.push(p->right);
            }
        }
    }

    // ── 3. Traversals ────────────────────────

    void _preorder(Node<T> *p) const
    {
        if (!p)
        {
            return;
        }
        cout << p->data << " ";
        _preorder(p->left);
        _preorder(p->right);
    }

    void _inorder(Node<T> *p) const // BUG FIX: was calling preorder
    {
        if (!p)
        {
            return;
        }
        _inorder(p->left);
        cout << p->data << " ";
        _inorder(p->right);
    }

    void _postorder(Node<T> *p) const // BUG FIX: was calling preorder
    {
        if (!p)
        {
            return;
        }
        _postorder(p->left);
        _postorder(p->right);
        cout << p->data << " ";
    }

    void levelorder() const
    {
        if (!root)
            return;
        queue<Node<T> *> q;
        q.push(root);
        while (!q.empty())
        {
            Node<T> *p = q.front();
            q.pop();
            cout << p->data << " ";
            if (p->left)
                q.push(p->left);
            if (p->right)
                q.push(p->right);
        }
        cout << "\n";
    }

    // ── 4. Properties ────────────────────────

    int get_height() const
    {
        return _get_height(root);
    }
    int countNodes() const
    {
        return _countNodes(root);
    }
    int count_leaves() const
    {
        int c = 0;
        _count_leaves(root, c);
        return c;
    }

    bool isBalanced() const
    {
        bool valid = true;
        _heightForBalance(root, valid);
        return valid;
    }

    bool is_bst() const
    {
        return isBSTHelper(root, numeric_limits<T>::lowest(), numeric_limits<T>::max());
    }

    // ── 5. Search & Navigation ───────────────

    bool search(const T &val) const
    {
        if (!root)
        {
            return false;
        }
        queue<Node<T> *> q;
        q.push(root);
        while (!q.empty())
        {
            Node<T> *p = q.front();
            q.pop();
            if (p->data == val)
            {
                return true;
            }
            if (p->left)
            {
                q.push(p->left);
            }
            if (p->right)
            {
                q.push(p->right);
            }
        }
        return false;
    }

    // Returns parent's data, or T{-1} if val is root / not found
    T find_parent(const T &val) const
    {
        if (!root || root->data == val)
        {
            return T{-1};
        }
        queue<Node<T> *> q;
        q.push(root);
        while (!q.empty())
        {
            Node<T> *p = q.front();
            q.pop();
            if ((p->left && p->left->data == val) || (p->right && p->right->data == val))
            {
                return p->data;
            }
            if (p->left)
            {
                q.push(p->left);
            }
            if (p->right)
            {
                q.push(p->right);
            }
        }
        return T{-1};
    }

    // ── 6. Insertion & Deletion ──────────────

    // Insert at first available null spot (Level-Order)
    void insert_node(const T &val)
    {
        if (!root)
        {
            root = new Node<T>(val);
            return;
        }
        queue<Node<T> *> q;
        q.push(root);
        while (!q.empty())
        {
            Node<T> *p = q.front();
            q.pop();
            if (!p->left)
            {
                p->left = new Node<T>(val);
                return;
            }
            else
                q.push(p->left);
            if (!p->right)
            {
                p->right = new Node<T>(val);
                return;
            }
            else
                q.push(p->right);
        }
    }

    // Swap target with deepest-rightmost node, then delete that node
    void delete_node(const T &val)
    {
        if (!root)
        {
            return;
        }
        if (!root->left && !root->right)
        {
            if (root->data == val)
            {
                delete root;
                root = nullptr;
            }
            return;
        }

        queue<Node<T> *> q;
        q.push(root);
        Node<T> *targetNode = nullptr, *lastNode = nullptr;
        while (!q.empty())
        {
            lastNode = q.front();
            q.pop();
            if (lastNode->data == val)
            {
                targetNode = lastNode;
            }
            if (lastNode->left)
            {
                q.push(lastNode->left);
            }
            if (lastNode->right)
            {
                q.push(lastNode->right);
            }
        }
        if (targetNode)
        {
            T lastVal = lastNode->data;
            delete_last_node();
            targetNode->data = lastVal;
        }
    }

    void delete_last_node()
    {
        if (!root)
        {
            return;
        }
        if (!root->left && !root->right)
        {
            delete root;
            root = nullptr;
            return;
        }

        queue<Node<T> *> q;
        q.push(root);
        Node<T> *last = nullptr, *parentOfLast = nullptr;
        while (!q.empty())
        {
            last = q.front();
            q.pop();
            if (last->left)
            {
                parentOfLast = last;
                q.push(last->left);
            }
            if (last->right)
            {
                parentOfLast = last;
                q.push(last->right);
            }
        }
        if (parentOfLast->right == last)
        {
            parentOfLast->right = nullptr;
        }
        else
        {
            parentOfLast->left = nullptr;
        }
        delete last;
    }

    // ── 7. Utility ───────────────────────────

    void clear_tree()
    {
        destroy(root);
        root = nullptr;
    }

    Node<T> *get_root() const { return root; }
    Node<T> *&set_root() { return root; }
};

/*
// ── Usage Example ────────────────────────────────────────────────────────────

int main()
{
    // Works with int (default)
    BinaryTree<int> tree = {1, 2, 3, 4, 5, -1, 6};

    cout << "Level-order : "; tree.levelorder();
    cout << "Height      : " << tree.get_height()   << "\n";
    cout << "Nodes       : " << tree.countNodes()   << "\n";
    cout << "Leaves      : " << tree.count_leaves() << "\n";
    cout << "Is BST?     : " << (tree.is_bst() ? "Yes" : "No") << "\n";
    cout << "Is Balanced?: " << (tree.isBalanced() ? "Yes" : "No") << "\n";

    tree.insert_node(10);
    cout << "After insert(10): "; tree.levelorder();

    // Works with double too
    BinaryTree<double> dtree = {1.1, 2.2, 3.3};
    cout << "Double tree level-order: "; dtree.levelorder();

    return 0;
}
*/

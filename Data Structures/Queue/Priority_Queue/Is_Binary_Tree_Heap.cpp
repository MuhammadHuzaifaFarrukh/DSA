#include <iostream>
#include <queue>
#include <stack>
#include <climits>
#include <string>

using namespace std;

class Node
{
public:
    int val;
    Node *left, *right;
    Node(int data = 0, Node *l = nullptr, Node *r = nullptr) : val(data), left(l), right(r) {}
};

class BinaryTree
{
private:
    Node *root;

public:
    BinaryTree() : root(nullptr) {}

    Node *create_binary_tree()
    {
        int x;
        cout << "Enter data (-1 for NULL): ";
        cin >> x;
        if (x == -1)
        {
            return nullptr;
        }
        Node *newNode = new Node(x);
        cout << "Going Left of " << x << " -> ";
        newNode->left = create_binary_tree();
        cout << "Going Right of " << x << " -> ";
        newNode->right = create_binary_tree();
        return newNode;
    }

    /*
    You are given the root of a binary tree, and the task is to determine whether it satisfies the properties of a max-heap.
    A binary tree is considered a max-heap if it satisfies the following conditions:
    Completeness: Every level of the tree, except possibly the last, is completely filled, and all nodes are as far left as possible.
    Max-Heap Property: The value of each node is greater than or equal to the values of its children.

    Input: root = [97, 46, 37, 12, 3, 7, 31, 6, 9]
    Output: true
    Explanation: The tree is complete and satisfies the max-heap property.

    Input: root = [97, 46, 37, 12, 3, 7, 31, N, N, 2, 4]
    Output: false
    Explanation: The tree is not complete and does not follow the Max-Heap Property, hence it is not a max-heap.
    */

    // 1) If we were given an array , then we would just check its Max-Heap property because vector elements are side by side and we would assume that we are filling them one by one.
    // Now that we are given a root , we need to check if its CBT or not first.
    // We count total nodes actual nodes in the tree.
    // Then we check the indexes of the tree that are of heap (2i+1 and 2i+2).
    // In a CBT , e.g if there are total 6 nodes lets say , then its vector form contains indices (0-5).
    // So if we find any index greater or equal to number of nodes , it means any 1 or more nodes are skipped and its not a CBT.
    // When we know that its a CBT, we check for its heap property.
    // First we check if node's left exists , if yes then we check whether parent is greater than its left child or not.
    // If yes we proceed further left , and check.
    // If no , then we stop immediately and return 0.
    // So once we have verified all left side of the root , we verify the right side of all the nodes.
    // We check if the node has a right child or not , if yes then we check the same things and return 1 after complete verification.
    // Time : O(n)
    // Space : O(h) or O(n)
    bool isHeap(Node *root)
    {
        int nodes = count(root);
        if (!CBT(root, nodes, 0))
        {
            return 0; // If its not a CBT.
        }

        if (!checkHeap(root))
        {
            return 0;
        }
        return 1;
    }

    int count(Node *root)
    {
        if (!root)
        {
            return 0;
        }
        return (1 + count(root->left) + count(root->right));
    }

    bool CBT(Node *root, int &nodes, int index)
    {
        if (!root)
        {
            return 1;
        }
        if (index >= nodes)
        {
            return 0;
        }
        return CBT(root->left, nodes, 2 * index + 1) && CBT(root->right, nodes, 2 * index + 2);
    }

    bool checkHeap(Node *root)
    {
        if (!root)
        {
            return 1;
        }
        if (root->left)
        {
            if (root->left->val > root->val)
            {
                return 0;
            }
            bool x = checkHeap(root->left);
            if (!x)
            {
                return 0;
            }
        }
        if (root->right)
        {
            if (root->right->val > root->val)
            {
                return 0;
            }
            bool x = checkHeap(root->right);
            if (!x)
            {
                return 0;
            }
            return x;
        }
        return 1;
    }

    // 2) We can do this by using level order traversal easily in a single pass.
    // We take a queue and push root node.
    // Then we have to use a boolean tracker.
    // If its a CBT , all the null values will appear at the end and we can set this boolean tracker to true.
    // The next time it comes to check , it won't find any valid node and it will keep on seeing null tracker as true until queue is emptied.
    // If its a CBT , there will be a value right after some null nodes , if this happens , we can immediately catch this ,as our null tracker is true.
    // If we find a valid node , and their left and right exist , then we compare with its left and right child for max heap.
    // Then we simply push them without any null check so that we can detect if any Non-Valid CBT.
    // Time : O(n)
    // Space : O(w) or O(n)
    bool isHeap2(Node *root)
    {
        if (!root)
        {
            return 1;
        }

        queue<Node *> q;
        q.push(root);

        bool nullSeen = 0;

        while (!q.empty())
        {
            Node *curr = q.front();
            q.pop();

            if (curr == nullptr)
            {
                nullSeen = 1;
            }
            else
            {
                // 1. CBT Check: If we see a valid node AFTER seeing a nullptr, it's NOT a CBT
                if (nullSeen)
                {
                    return 0;
                }

                // 2. Max-Heap Check: Left child must be <= parent
                if (curr->left)
                {
                    if (curr->left->val > curr->val)
                    {
                        return 0;
                    }
                }

                // 3. Max-Heap Check: Right child must be <= parent
                if (curr->right)
                {
                    if (curr->right->val > curr->val)
                    {
                        return 0;
                    }
                }

                // Push both children (even if nullptr) to track completeness
                q.push(curr->left);
                q.push(curr->right);
            }
        }

        return 1;
    }

    Node *get_root() const
    {
        return root;
    }
    Node *&get_root()
    {
        return root;
    }
    void destroy_tree(Node *p)
    {
        if (p != nullptr)
        {
            destroy_tree(p->left);  // Go Left
            destroy_tree(p->right); // Go Right
            delete p;               // Delete Current Node
        }
    }
    // Make destructor always using post order.
    // Using inorder or preorder is a bad choice as doing that , we would lose our left and right tree branches
    ~BinaryTree()
    {
        destroy_tree(root);
        root = nullptr; // Optional but good practice
    }
};

int main()
{
    BinaryTree myTree;
    myTree.get_root() = myTree.create_binary_tree();

    return 0;
}

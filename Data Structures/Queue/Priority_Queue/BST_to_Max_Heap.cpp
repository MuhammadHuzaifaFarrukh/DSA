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
    Given a Binary Search Tree, convert it into a Special Max Heap with the condition that all the values in the left subtree of a node should be less than all the values in the right subtree of the node.
    This condition is applied on all the nodes in the so converted Max Heap.

    Input: root[] = [4, 2, 6, 1, 3, 5, 7]
    Output: [7,3,6,1,2,4,5]

    Input: root[] = [5, 3, 8, 2, 4, 7, 9]
    Output: [9,4,8,2,3,5,7]
    */

    // We could have done using inorder and just build heap.
    // But building heap doesn't ensure that whether left subtree values will be smaller than right subtree values.
    // Here we are given that we have to keep all the left subtree values smaller than the right subtree values.
    // So we find out its inorder first and store it in a vector.
    // Then we use postorder to fill the values inside our tree using that vector.
    // It doesn't matter if its a CBT or not.
    // We just have to make it Max Heap according to values.
    // Using postorder helps us because we visit Left , then Right and then Node.
    // So , the first value in ascending sorted order is put at the left most node , then the next bigger value at the right child and the next bigger value at the parent node.
    // So using postorder , we can achieve this easily and maintain the max heap property also.
    // Time : O(n)
    // Space : O(h) or O(n)
    void convertToMaxHeap(Node *root)
    {
        vector<int> in;
        inorder(root, in);
        int index = 0;
        postorder(root, in, index);
    }

    void inorder(Node *root, vector<int> &ans)
    {
        if (!root)
        {
            return;
        }
        inorder(root->left, ans);
        ans.push_back(root->val);
        inorder(root->right, ans);
    }
    void postorder(Node *root, vector<int> &ans, int &index)
    {
        if (!root)
        {
            return;
        }
        postorder(root->left, ans, index);
        postorder(root->right, ans, index);
        root->val = ans[index];
        index++;
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

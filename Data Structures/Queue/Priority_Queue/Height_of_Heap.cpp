#include <iostream>
#include <queue>

using namespace std;

/*
Given a Binary Heap of size n in an array arr[]. Write a program to calculate the height of the Heap.
Note: Return 1 if the n is 1.

Input: n = 6, arr[] = [1, 3, 6, 5, 9, 8]
Output: 2

Input: n = 9, arr[] = [3, 6, 9, 2, 15, 10, 14, 5, 12]
Output: 3
*/

// 1) We simply have to calculate logn to the base 2.
// We can do that either using a loop or using cmath library.
// However the question says to return 1 for n=1.
// Time : O(logn)
// Space : O(1)
int height(priority_queue<int> &pq)
{
    int n = pq.size();
    int height = 0;
    // This works in O(log n)
    if (n == 1)
    {
        height = 1;
    }
    else
    {
        while (n > 1)
        {
            n = n / 2;
            height++;
        }
    }
    return height;
}

// 2) Check if PQ / Given vector is size 1 , then return 1 otherwise build a tree.
// Build a Tree using the given pq and then find the height of that tree.
// Time : O(n)
// Space : O(n)
struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int val, Node *left = nullptr, Node *right = nullptr) : data(val), left(left), right(right) {}
};

// Either use this to create CBT by extracting vector from pq.
Node *createCBT(priority_queue<int> &pq)
{
    if (pq.empty())
    {
        return nullptr;
    }
    vector<int> arr;
    while (!pq.empty())
    {
        arr.push_back(pq.top());
        pq.pop();
    }
    return buildCBTUsingDFS(arr, 0);
}
Node *buildCBTUsingDFS(vector<int> &arr, int index)
{
    if (index >= arr.size())
    {
        return nullptr;
    }

    // 1. Create the current node
    Node *root = new Node(arr[index]);

    // 2. Recursively build left and right subtrees
    root->left = buildCBTUsingDFS(arr, 2 * index + 1);
    root->right = buildCBTUsingDFS(arr, 2 * index + 2);

    return root;
}

// Either use this to create CBT by using Level Order Traversal.
Node *buildCBTFromLO(priority_queue<int> &pq)
{
    if (pq.empty())
    {
        return nullptr;
    }

    // Pop the highest priority element to serve as the root
    Node *root = new Node(pq.top());
    pq.pop();

    queue<Node *> q;
    q.push(root);

    while (!pq.empty())
    {
        Node *curr = q.front();
        q.pop();

        // 1. Attach Left Child
        if (!pq.empty())
        {
            curr->left = new Node(pq.top());
            pq.pop();
            q.push(curr->left);
        }

        // 2. Attach Right Child
        if (!pq.empty())
        {
            curr->right = new Node(pq.top());
            pq.pop();
            q.push(curr->right);
        }
    }

    return root;
}

int height2(Node *root)
{
    if (!root)
    {
        return -1;
    }
    int L = height2(root->left);
    int R = height2(root->right);
    return 1 + max(L, R);
}

int main()
{
    priority_queue<int> pq;
    pq.push(5);
    pq.push(6);
    pq.push(10);
    pq.push(12);
    pq.push(7);
    pq.push(19);
    pq.push(14);

    cout << "Height of Heap is : " << height(pq) << endl;
    return 0;
}
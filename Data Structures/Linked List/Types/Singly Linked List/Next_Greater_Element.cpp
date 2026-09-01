#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Node
{
public:
    int val;
    Node *next;
    Node(int val = 0, Node *temp = nullptr) : val(val), next(temp) {}
};

class List
{
    Node *head;

public:
    List()
    {
        head = nullptr;
    }
    void push_front_list(int val)
    {
        Node *newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    void push_back_list(int val)
    {
        Node *newNode = new Node(val);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            Node *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void pop_front_list()
    {
        if (!head)
            return;

        Node *temp = head;
        head = head->next;
        delete temp;
    }

    void pop_back_list()
    {
        if (!head)
            return;

        if (!head->next)
        {
            delete head;
            head = nullptr;
        }
        else
        {
            Node *temp = head;
            // Move to the second-to-last node
            while (temp->next->next != nullptr)
            {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
    }

    /*
    You are given the head of a linked list with n nodes.
    For each node in the list, find the value of the next greater node. That is, for each node, find the value of the first node that is next to it and has a strictly larger value than it.
    Return an integer array answer where answer[i] is the value of the next greater node of the ith node (1-indexed). If the ith node does not have a next greater node, set answer[i] = 0.

    Input: head = [2,1,5]
    Output: [5,5,0]

    Input: head = [2,7,4,3,5]
    Output: [7,0,5,5,0]

    */

    // 1) By copying values into a new vector and finding next greater element in the new vector.
    // Time : O(n)
    // Space : O(n)
    vector<int> nextLargerNodes(Node *head)
    {
        vector<int> nums;
        while (head)
        {
            nums.push_back(head->val);
            head = head->next;
        }
        vector<int> ans(nums.size(), 0);
        stack<int> st;
        for (int i = 0; i < nums.size(); i++)
        {
            while (!st.empty() && nums[st.top()] < nums[i])
            {
                ans[st.top()] = nums[i];
                st.pop();
            }
            st.push(i);
        }
        return ans;
    }

    // 2) By using Pair of Node and Virtual indices.
    // First we find the size of our total array by finding size of whole list.
    // We check until the linked list size.
    // If we want to do it using linked list , then we need a track of virtual indices.
    // For this , we can use a stack.
    // We also need to access that value which cannot be done in O(1) since its a linked list.
    // Hence we use stack<pair<Node *, int>>.
    // In this way we can just use nums[st.top()] as st.top().first->val and nums[i] as temp->val.
    // We can write ans[st.top()] as nums[st.top().second].
    // We keep st.push(i) as it is by keeping a new variable 'i' as an index tracker.
    // Time : O(n)
    // Space : O(n)
    vector<int> nextLargerNodes2(Node *head)
    {
        int size = 0;
        Node *temp = head;
        while (temp)
        {
            size++;
            temp = temp->next;
        }
        stack<pair<Node *, int>> st;
        vector<int> ans(size, 0);
        temp = head;
        int i = 0;
        while (temp)
        {
            while (!st.empty() && st.top().first->val < temp->val)
            {
                // ans[st.top()] = temp->val;
                ans[st.top().second] = temp->val;
                st.pop();
            }
            st.push({temp, i});
            i++;
            temp = temp->next;
        }
        return ans;
    }

    void print_list()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->val << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};
int main()
{

    return 0;
}
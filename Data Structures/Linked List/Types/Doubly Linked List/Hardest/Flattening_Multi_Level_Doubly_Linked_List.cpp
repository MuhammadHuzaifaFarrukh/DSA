#include <iostream>
using namespace std;

class Node
{
public:
    int val;
    Node *prev;
    Node *next;
    Node *child;
    Node(int v = 0, Node *p = nullptr, Node *n = nullptr, Node *c = nullptr) : val(v), prev(p), next(n), child(c) {}
};

class DList
{
private:
    Node *head;

public:
    DList() : head(nullptr) {}

    ~DList()
    {
        while (head)
        {
            pop_front_DList();
        }
    }

    void push_front_DList(int v)
    {
        Node *newNode = new Node(v, nullptr, head);
        if (head)
        {
            head->prev = newNode;
        }
        head = newNode;
    }

    void push_back_DList(int v)
    {
        Node *newNode = new Node(v);
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
            newNode->prev = temp;
        }
    }

    void pop_front_DList()
    {
        if (!head)
            return;

        Node *temp = head;
        head = head->next;
        if (head)
        {
            head->prev = nullptr;
        }
        delete temp;
    }

    void pop_back_DList()
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
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            // Now temp is the last node
            temp->prev->next = nullptr;
            delete temp;
        }
    }

    /*
    You are given a doubly linked list, which contains nodes that have a next pointer, a previous pointer, and an additional child pointer. This child pointer may or may not point to a separate doubly linked list, also containing these special nodes. These child lists may have one or more children of their own, and so on, to produce a multilevel data structure as shown in the example below.
    Given the head of the first level of the list, flatten the list so that all the nodes appear in a single-level, doubly linked list. Let curr be a node with a child list.
    The nodes in the child list should appear after curr and before curr.next in the flattened list.
    Return the head of the flattened list.
    The nodes in the list must have all of their child pointers set to null.

    Input: head = [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
    Output: [1,2,3,7,8,11,12,9,10,4,5,6]
    */

    // This question is almost same as flattening a binary tree to singly linked list.
    // Here we are give prev,next and child node.
    // We can consider the next node as the right child and child node as the left child from that similar BT to linked list problem.
    // Also we will use the same Morris Traversal but with some extra modifications due to doubly linked list.
    // We use a curr node that will traverse along the list and a temp pointer that holds the next pointer of current , if the child of current exists.
    // So first we have to check if current's child (left child) exists or not , if not then we move on to the current's next (right child).
    // If it exists , then we store the current's next (right child) into temp.
    // Then we place a pointer (tail) at the current's child (left child) and traverse to the end by going tail->next.
    // Then we attach this link , by joining the tail's next to the current's next (right child or temp ).
    // If the current's right child exists (temp exists) , then as a doubly linked list node , we join the node's previous pointer to the tail as well.
    // We remove the connection of current from its next (right child) and place that connection (current's next) to the current's child (left child).
    // As a doubly linked list node , we also join current's child's prev back to current.
    // Then we make the current's child (right child) to null to finish that connection and move on to the current's next for further processing.
    // We keep doing this until current becomes NULL.
    // This is the same as doing morris traversal for flattening a binary tree to list , here we just had to manage the connections of previous pointers as well and the names were different that's all.
    // Time : O(n)
    // Space : O(1)
    Node *flatten(Node *head)
    {
        Node *curr = head;
        Node *temp = nullptr;
        while (curr != nullptr)
        {
            if (!curr->child)
            {
                curr = curr->next;
            }
            else
            {
                Node *tail = curr->child;
                while (tail->next)
                {
                    tail = tail->next;
                }

                temp = curr->next;
                curr->next = curr->child; // original
                curr->child->prev = curr;
                tail->next = temp; // original
                if (temp)
                {
                    temp->prev = tail;
                }
                curr->child = nullptr;
                curr = curr->next;
            }
        }
        return head;
    }

    void print_DList()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->val << " <-> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

int main()
{
    cout << "Hello World " << endl;

    return 0;
}
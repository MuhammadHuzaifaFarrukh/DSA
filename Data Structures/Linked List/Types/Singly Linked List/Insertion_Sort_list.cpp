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
    int data;
    Node *next;
    Node(int data = 0, Node *temp = nullptr) : data(data), next(temp) {}
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

    void print_list()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    // We used a dummy node and added other nodes infront of it.
    // Time : O(n^2)
    // Space : O(1)
    Node *insertionSortList(Node *head)
    {
        if (!head->next)
        {
            return head;
        }
        Node *dummy = new Node(0);
        Node *curr = head;
        while (curr)
        {
            Node *future = curr->next;
            Node *prev = dummy;
            while (prev->next && prev->next->data < curr->data)
            {
                prev = prev->next;
            }
            curr->next = prev->next;
            prev->next = curr;
            curr = future;
        }
        Node *newHead = dummy->next;
        delete dummy;
        return newHead;
    }
};

int main()
{

    return 0;
}
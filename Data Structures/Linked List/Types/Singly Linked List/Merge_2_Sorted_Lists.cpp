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

    /*
    You are given the heads of two sorted linked lists list1 and list2.
    Merge the two lists into one sorted list. The list should be made by splicing together the nodes of the first two lists.
    Return the head of the merged linked list.
    */
    // Time : O(n)
    // Space : O(1)
    Node *mergeTwoLists(Node *another_head1, Node *another_head2)
    {
        Node *head = new Node(0);
        Node *curr = head;

        Node *head1 = another_head1;
        Node *head2 = another_head2;

        while (head1 && head2)
        {
            if (head1->data <= head2->data)
            {
                curr->next = head1;
                head1 = head1->next;
                curr = curr->next;
                curr->next = nullptr;
            }
            else
            {
                curr->next = head2;
                head2 = head2->next;
                curr = curr->next;
                curr->next = nullptr;
            }
        }
        if (head1)
        {
            curr->next = head1;
        }
        else
        {
            curr->next = head2;
        }
        curr = head;
        head = head->next;
        delete curr;
        return head;
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
};
int main()
{

    return 0;
}
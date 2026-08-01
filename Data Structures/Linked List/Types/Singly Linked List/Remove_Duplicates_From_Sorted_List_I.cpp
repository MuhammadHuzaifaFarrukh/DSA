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
    Given the head of a sorted linked list, delete all duplicates such that each element appears only once.
    Return the linked list sorted as well.
    */
    // We use a dummy node.
    // We keep one node (prev) at dummy node and one (temp) node at its next.
    // Now we check if temp and its next are equal or not.
    // If they are equal then we move temp skipping over all at the last temp node that it was equal.
    // Then we move prev's next node to be this temp node (not temp->next) cause we want it to be at most 1 instance of this element and then we confirm prev that we have the unique element so we move both temp and prev here.
    // If they aren't equal then we just know that temp is unique and so we join the prev next with this temp.
    // Then we move both nodes.
    // Time : O(n)
    // Space : O(1)
    Node *deleteDuplicates(Node *head)
    {
        if (!head)
        {
            return nullptr;
        }

        Node *dummy = new Node(0, head);

        Node *prev = dummy;
        Node *temp = head;
        while (temp != nullptr && temp->next != nullptr)
        {
            if (temp->next && temp->data == temp->next->data)
            {
                while (temp->next && temp->data == temp->next->data)
                {
                    temp = temp->next;
                }
                prev->next = temp;
                prev = prev->next;
                temp = temp->next;
            }
            else
            {
                prev->next = temp;
                temp = temp->next;
                prev = prev->next;
            }
        }

        Node *newhead = dummy->next;
        delete dummy;
        return newhead;
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
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>

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
    Given head which is a reference node to a singly-linked list. The value of each node in the linked list is either 0 or 1. The linked list holds the binary representation of a number.
    Return the decimal value of the number in the linked list.
    The most significant bit is at the head of the linked list.
    */

    // We solve it by reversing the list and then we just calculate the value iterating the list again.
    // Time : O(n)
    // Space : O(1)
    int getDecimalValue(Node *head)
    {
        head = reverse_list(head);
        Node *temp = head;
        int i = 0;
        int value = 0;
        while (temp)
        {
            value += temp->data * pow(2, i);
            temp = temp->next;
            i++;
        }
        return value;
    }

    Node *reverse_list(Node *head)
    {
        Node *curr = head;
        Node *prev = nullptr;
        Node *future = nullptr;
        while (curr != nullptr)
        {
            future = curr->next;
            curr->next = prev;
            prev = curr;
            curr = future;
        }

        head = prev;
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
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
    Given the head of a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list. Return the linked list sorted as well.
    */
    // We just use a dummy node.
    // Now we start with two nodes , one (prev) from dummy node and one (temp) from the next node.
    // Now we have to check if temp and its next node are equal or not.
    // If they equal then we keep skipping those duplicates by temp pointer.
    // After that , we just set 'prev's next' skipping over all the duplicates and also move temp to the next.
    // If they are not equal meaning we found unique element , then we just set prev next to this temp and also move both prev and temp one step next.
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
                prev->next = temp->next;
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
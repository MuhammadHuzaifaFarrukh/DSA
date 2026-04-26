#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
    int data;
    Node *next;

    Node(int val = 0, Node *ptr = nullptr) : data(val), next(ptr) {}
};

class LinkedList
{
    Node *head;
    Node *tail;

public:
    LinkedList() : head(nullptr) {}

    void insertAtHead(int val)
    {
        Node *newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        tail = newNode;
    }

    void pop_back_list()
    {
        if (head == nullptr)
        {
            cout << "List is empty " << endl;
        }
        else
        {
            Node *temp = head;
            while (temp->next != tail)
            {
                temp = temp->next;
            }
            temp->next = nullptr;
            delete tail;
            tail = temp;
        }
        return;
    }
    void display()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "NULL" << std::endl;
    }

    Node *getHead() { return head; }
    Node *&sethead()
    {
        return head;
    }
    ~LinkedList()
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
    // 1) Using An Array where we copy the unique ones only  and put our new elements in the list.
    // Time Complexity and Space Complexity : O(n)

    // 2) Using two pointer approach
    Node *deleteDuplicates(Node *head)
    {
        if (!head)
        {
            return head;
        }
        Node *temp = head->next;
        Node *prev = head;
        while (temp)
        {
            if (prev->data == temp->data)
            {
                // Check if we are about to delete the tail
                if (temp == tail)
                {
                    tail = prev; // Move tail back to the previous node
                }
                prev->next = temp->next;
                temp->next = nullptr;
                delete temp;
                temp = prev->next;
            }
            else
            {
                prev = prev->next;
                temp = temp->next;
            }
        }
        return head;
    }
};

int main()
{
    LinkedList l1;
    l1.insertAtHead(4);
    l1.insertAtHead(3);
    l1.insertAtHead(3);
    l1.insertAtHead(2);
    l1.insertAtHead(1);
    l1.insertAtHead(1);

    cout << "Before : " << endl;
    l1.display();
    LinkedList l2;
    l1.deleteDuplicates(l1.getHead());
    cout << "After : " << endl;
    l1.display();

    return 0;
}
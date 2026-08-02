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
    Given the head of a singly linked list, group all the nodes with odd indices together followed by the nodes with even indices, and return the reordered list.
    The first node is considered odd, and the second node is even, and so on.
    Note that the relative order inside both the even and odd groups should remain as it was in the input.
    */
    // We keep two nodes , oddlist which points to head and evenlist which points to the next element of the head.
    // Now we just skip and hop on one after other pointer.
    // We point oddlist's next to even's next and even's next to odd's next.
    // We keep moving both odd and even pointers until evenlist or its next is present.
    // Then at the end odd pointer and even pointer must be at the last of the lists.
    // We keep an evenhead pointer at the start to the head->next so we can join both lists easily.
    // Time : O(n)
    // Space : O(1)
    Node *oddEvenList(Node *head)
    {
        // if (!head)
        // {
        //     return nullptr;
        // }
        Node *evenList = head->next;
        Node *evenHead = head->next;
        Node *oddList = head;

        // We keep this evenlist so that if we find single node or odd number of nodes, we don't access it's next for the even pointer.
        // evenlist->next condition comes for the even number of nodes.
        while (evenList && evenList->next)
        {
            oddList->next = evenList->next;
            evenList->next = oddList->next;

            oddList = oddList->next;
            evenList = evenList->next;
        }
        oddList->next = evenHead;
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
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>

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
    int size = 0;
    Node *tail;

public:
    List()
    {
        head = tail = nullptr;
        size = 0;
    }

    // Delete the given node current without using head node such that this current can be any node except the last one.
    // This means we have atleast 2 nodes.
    Node *DeleteAnyNodeWithoutHead(Node *curr)
    {
        Node *temp = curr->next;

        // Check if the node we are deleting is the tail
        if (temp == tail)
        {
            tail = curr; // Move the tail back to the current node
        }

        curr->data = temp->data;
        curr->next = temp->next;

        delete temp;
        size--; // Remember to decrement the size as well
        return curr;
    }

    ~List()
    {
        clear_list();
    }
    void clear_list()
    {
        while (head)
            pop_front_list();
        head = tail = nullptr;
    }
    void pop_front_list()
    {
        if (!head)
            throw std::underflow_error("Underflow: List empty");
        Node *temp = head;
        head = head->next;
        if (!head)
            tail = nullptr;
        temp->next = nullptr;
        delete temp;
        size--;
    }
};
int main()
{

    return 0;
}
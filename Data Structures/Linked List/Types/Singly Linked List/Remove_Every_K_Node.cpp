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

    Node *Remove_Every_K_Node(Node *head, int k)
    {
        // head == nullptr will be checked inside.
        // k<=0 and k == 1 check is important
        if (k <= 0)
        {
            return head;
        }
        if (k == 1) // Empty all the list
        {
            return nullptr;
        }
        int count = 1;
        Node *temp = head;
        while (temp != nullptr && temp->next != nullptr)
        {
            if (count == k - 1)
            {
                Node *todelete = temp->next;
                if (todelete == this->tail)
                {
                    this->tail = temp; // Move tail back to the current node
                }
                temp->next = todelete->next;
                todelete->next = nullptr;
                delete todelete;
                count = 1;
            }
            count++;
            temp = temp->next;
        }
        return head;
    }
    // temp->next !=nullptr ensures that if we get a k to delete that is out of list then we can stop the loop.

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
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

    Node *removeNthFromEnd(Node *head, int n)
    {
        int count = 0;
        Node *temp = head;
        while (temp != nullptr)
        {
            count++;
            temp = temp->next;
        }

        if (n == count)
        {
            Node *newHead = head->next;
            delete head;
            if (newHead == nullptr)
            {
                this->tail = nullptr;
            }
            this->head = newHead;
            return newHead;
        }
        temp = head;
        for (int i = 0; i < count - n - 1; i++)
        {
            temp = temp->next;
        }

        Node *toDelete = temp->next;
        // Case 2: Removing the Tail (n = 1)
        if (toDelete == this->tail)
        {
            this->tail = temp; // Move tail back to the previous node
        }
        
        temp->next = temp->next->next;
        toDelete->next = nullptr;
        delete toDelete;
        return head;
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
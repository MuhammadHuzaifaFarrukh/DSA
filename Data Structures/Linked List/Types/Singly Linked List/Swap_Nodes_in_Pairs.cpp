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
    Node *tail;

public:
    List()
    {
        head = tail = nullptr;
    }

    Node *reverse_list(Node *head)
    {
        Node *newTail = head;

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

        this->head = prev;          // prev is the original tail/new head
        this->tail = newTail;       // newTail is the original head/new tail
        this->tail->next = nullptr; // Ensure the new tail points to null

        return this->head;
    }

    // We take a dummy node and we attach the reversed pair nodes on it.
    // Time : O(n) , Space : O(1).
    Node *swapPairs(Node *head)
    {
        if (!head || !head->next)
        {
            return head;
        }
        Node *dummy = new Node(0);
        Node *prev = dummy;
        Node *temp1 = head;
        Node *temp2 = head->next;

        Node *future1;
        Node *future2;

        while (temp1 && temp2)
        {
            Node *nextPair = temp2->next;
            temp1->next = temp2->next;
            temp2->next = temp1;
            prev->next = temp2;
            prev = temp1;

            // We check for the next pair if it exists.
            // If temp1 exists only then update temp2 otherwise set temp2 to null.
            temp1 = nextPair;
            if (temp1)
            {
                temp2 = temp1->next;
            }
            else
            {
                temp2 = nullptr;
            }
        }
        Node *newHead = dummy->next;
        delete dummy;
        return newHead;
    }

    void push_front_list(int val)
    {
        Node *newNode = nullptr;
        try
        {
            newNode = new Node(val);
        }
        catch (const std::bad_alloc &)
        {
            throw std::runtime_error("Out of memory: push_front failed.");
        }

        if (!head)
        {
            head = tail = newNode;
            newNode->next = nullptr;
        }
        else
        {
            newNode->next = head;
            head = newNode;
        }
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
    }
};
int main()
{

    return 0;
}
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

    // Pop Back using Recursion in a List
    // Update tail pointer (if you have and size)
    // Time Complexity : O(n) and Space Complexity : O(n)
    Node *DeleteTailRecursively(Node *curr)
    {
        if (curr == nullptr)
        {
            return nullptr;
        }

        if (curr->next == nullptr)
        {
            delete curr;
            tail = nullptr;
            // size--;
            return nullptr;
        }
        curr->next = DeleteTailRecursively(curr->next);
        if (curr->next == nullptr)
        {
            tail = curr;
        }
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
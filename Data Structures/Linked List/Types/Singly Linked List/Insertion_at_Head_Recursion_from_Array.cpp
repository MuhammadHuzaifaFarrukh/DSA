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
    
    // Create a Linked List from an Array by inserting each element at its head using Recursion :
    // Handle tail pointer (and size if you have optional).
    // Time Complexity : O(n) and Space Complexity : O(n)
    Node *insertAtheadfromArrayRecursively(int arr[], int ind, int size, Node *prev)
    {
        if (ind < 0 || ind > size)
        {
            throw std::underflow_error("Wrong Range");
        }
        if (ind == size)
        {
            return prev;
        }
        Node *temp = new Node(arr[ind]);
        temp->next = prev;
        size++;
        // If prev is nullptr, this is the very first node created.
        // In "Insert at Head" logic, the first node created becomes the tail.
        if (prev == nullptr)
        {
            this->tail = temp;
        }
        return insertAtheadfromArrayRecursively(arr, ind + 1, size, temp);
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
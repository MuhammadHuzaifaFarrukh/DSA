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

    // 1) Use a vector to store list data and then simply put values from vector into list according to 'k'.
    // Time Complexity and Space Complexity : O(n).

    // We cannot use indexing % method because there are no indexes in list.

    // 2) Rotation , where we use nodes to join nodes with each other.
    // We find node right before kth node and this becomes our last node.
    // Then the kth node is our head and the last node of this kth node list will be connected to our original head.
    // Time : O(n) , Space : O(1).

    Node *rotateRight(Node *head, int k)
    {
        if (head == nullptr || head->next == nullptr || k == 0)
            return head;

        int count = 1;
        Node *last = head;
        while (last->next != nullptr)
        {
            last = last->next;
            count++;
        }

        k = k % count;
        if (k == 0)
        {
            return head;
        }

        Node *temp = head;
        for (int i = 0; i < count - k - 1; i++)
        {
            temp = temp->next;
        }

        last->next = head;
        head = temp->next;
        temp->next = nullptr;

        this->tail = temp;      // Update tail pointer if your class uses it.
        return head;
    }

    // 3) We can use similar method of Triple Reverse on Linked List.
    // For that we need to find the kth node of the list in an iteration.
    // Then we can use triple reversing on it.
    // First reverse completely , then from 0 to k-1 , then k to n node.
    // Time Complexity : O(n) , Space Complexity : O(1).
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
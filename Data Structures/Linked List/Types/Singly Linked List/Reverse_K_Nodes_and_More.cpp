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
    // This problem asks to reverse the K-Nodes in K Groups , if nodes left are smaller than K , then reverse those also.

    // 1) Use a vector to store the elements
    // Keep reversing them by swapping / Two pointer method in k-groups.
    // Store the answer from vector to list.
    // Time : O(n) , Space : O(n)



    // 2) Doing in place
    // We use 4 pointers.
    // We keep track of previous nodes of each groups and next node of each group.
    // When we find the group , we reverse it.
    // Then we move the pointers position appropriately.
    // When we reverse a group our two pointers that we have are at last node of reversed , and one at right after the last node.
    // So we need 2 more pointers. One at previous of reverse group and one at first element of reverse group.
    // So we set these 2 extra pointers at the start , one by creating a dummy node and this keeps pointing right before at start of the list.
    // The other one keeps pointing at the first element of non-reversed list.
    // Then after reversed , it points to last element of reversed list.
    // Hence we need minimum of 4 pointers here.
    

    // We reverse the k nodes in k time.
    // We have total groups upto ceil(N/k) ~N/k so we can say our time is : k*N/k = N.
    // Time : O(n) and Space : O(1).

    Node *reverseKGroup(Node *head, int k)
    {
        Node *first = new Node(0);
        first->next = head;
        head = first;
        Node *second, *prev, *curr, *front;
        int x;
        while (first->next)     // This checks our end of list.
        {
            x = k;
            second = first->next;
            prev = first;
            curr = first->next;

            while (x && curr)   // This current handles if nodes are less than x.
            {
                front = curr->next;
                curr->next = prev;
                prev = curr;
                curr = front;
                x--;
            }
            first->next = prev;
            second->next = curr;
            first = second;
        }
        first = head;
        head = head->next;
        delete first;
        return head;
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
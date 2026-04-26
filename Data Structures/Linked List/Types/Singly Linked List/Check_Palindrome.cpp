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

    // 1) Put all the list elements inside vector and check the vector for palindrome.
    // Time : O(n) and Space : O(n).

    // 2) Reverse the linked list and then compare each node data side by side.
    // Time : O(n) and Space : O(n)

    
    // 3) Break list into two halves and reverse the 2nd half , then compare each one.
    // If No of Nodes are even then the halves are equal and we check till end.
    // If No of Nodes are odd then the 2nd half is +1 element so we check till end-1.
    // Time : O(n) and Space : O(1).
    bool isPalindrome(Node *head)
    {
        if (head->next == nullptr)
        {
            return 1;
        }
        if (head->next->next == nullptr)
        {
            if (head->next->data == head->data)
            {
                return 1;
            }
            return 0;
        }
        Node *temp = head;
        int count = 0;
        while (temp)
        {
            count++;
            temp = temp->next;
        }
        count /= 2;
        temp = head;

        while (count - 1 != 0)
        {
            temp = temp->next;
            count--;
        }

        Node *temp2 = temp->next;
        temp->next = nullptr;

        temp2 = reverse_list(temp2);
        temp = head;
        while (temp && temp2)
        {
            if (temp->data != temp2->data)
            {
                return 0;
            }
            temp = temp->next;
            temp2 = temp2->next;
        }
        return 1;
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

    Node *reverse_list(Node *head)
    {
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
        return prev;
    }
};
int main()
{

    return 0;
}